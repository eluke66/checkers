/*
 * Piece.c
 *
 *  Created on: Mar 29, 2017
 *      Author: luke
 */

#include "Piece.h"
#include "Board.h"
#include "MoveRules.h"

#include <stdio.h>
#include <stdlib.h>

#define LEFT -1
#define RIGHT 1

Moves singlePieceSimpleMoves(struct _Board *board, Coordinate coordinate, Piece *piece);
Moves singlePieceJumpMoves(struct _Board *board, Coordinate coordinate, Piece *piece);
Moves kingPieceSimpleMoves(struct _Board *board, Coordinate coordinate, Piece *piece);
Moves kingPieceJumpMoves(struct _Board *board, Coordinate coordinate, Piece *piece);

#define SINGLE_COORD_PRODUCER(piece) \
		(piece->direction == FORWARD ? forwardCoordinateProducer : backwardCoordinateProducer)

typedef struct _CoordinateSet {
	int numCoords;
	Coordinate coords[4];
} CoordinateSet;

typedef CoordinateSet (*CoordinateProducer)(Coordinate start, Piece* piece, Board* board);

CoordinateSet forwardCoordinateProducer(Coordinate start, Piece *piece, Board *board) {
	CoordinateSet coords;
	coords.numCoords = 2;
	coords.coords[0] = (Coordinate){.col = (start.col + RIGHT), .row=(start.row + FORWARD)};
	coords.coords[1] = (Coordinate){.col = (start.col + LEFT), .row=(start.row + FORWARD)};
	return coords;
}
CoordinateSet backwardCoordinateProducer(Coordinate start, Piece *piece, Board *board) {
	CoordinateSet coords;
	coords.numCoords = 2;
	coords.coords[0] = (Coordinate){.col = (start.col + RIGHT), .row=(start.row + BACKWARDS)};
	coords.coords[1] = (Coordinate){.col = (start.col + LEFT), .row=(start.row + BACKWARDS)};
	return coords;
}

CoordinateSet kingCoordinateProducer(Coordinate start, Piece *piece, Board *board) {
	CoordinateSet coords;
	coords.numCoords = 4;
	coords.coords[0] = (Coordinate){.col = (start.col + RIGHT), .row=(start.row + BACKWARDS)};
	coords.coords[1] = (Coordinate){.col = (start.col + LEFT), .row=(start.row + BACKWARDS)};
	coords.coords[2] = (Coordinate){.col = (start.col + RIGHT), .row=(start.row + FORWARD)};
	coords.coords[3] = (Coordinate){.col = (start.col + LEFT), .row=(start.row + FORWARD)};
	return coords;
}

void makeSinglePiece(Piece *piece, color_t color, int direction) {
	piece->color = color;
	piece->direction = direction;
	piece->canBeKinged = 1;
	piece->getJumpMoves = &singlePieceJumpMoves;
	piece->getSimpleMoves = &singlePieceSimpleMoves;
}

void makeKingPiece(Piece *piece, color_t color) {
	piece->color = color;
	piece->direction = 0;
	piece->canBeKinged = 0;
	piece->getJumpMoves = &kingPieceJumpMoves;
	piece->getSimpleMoves = &kingPieceSimpleMoves;
}

void addSimpleMovesForPiece(Coordinate start, Piece* piece, Board* board, CoordinateProducer coordProducer, Moves* moves) {
	CoordinateSet coordinates = coordProducer(start, piece, board);
	for (int cIndex = 0; cIndex < coordinates.numCoords; cIndex++) {
		Coordinate next = coordinates.coords[cIndex];
		if (isValidPosition(board, next) && !isPiece(getPieceAt(board, next))) {
			moves->moves[moves->count++] = addSimpleMove(board, piece, start, next);
		}
	}
}

void addSimpleMoveForPiece(Coordinate start, int columnIncrement, int rowIncrement, Piece* piece,
		Board* board, Moves* moves) {

	Coordinate next = COORD(start.row + rowIncrement, start.col + columnIncrement);
	if (isValidPosition(board, next) && !isPiece(getPieceAt(board, next))) {
		moves->moves[moves->count++] = addSimpleMove(board, piece, start, next);
	}
}


Move getJumpMove(Board* board, Piece *piece, Coordinate start, Coordinate next) {
	return addJumpMove(board, piece, start, next);
}

Move getMultiJumpMove(Board* board, Piece *piece, Coordinate start, Coordinate next, Move *previousMove) {
	return addMultiJumpMove(board, piece, start, next, previousMove);
}

void addJumpMoveForPiece(Coordinate start, int columnIncrement, int rowIncrement, Piece* piece,
		Board* board, Moves* moves) {

	// TODO - this is where the changes to our input parameter moves overwrites
	// the moves parameter in MoveRules.c
	Coordinate next = COORD(start.row + rowIncrement, start.col + columnIncrement);
	if (isValidPosition(board,next) && pieceIsJumpable(board,piece,next) && nextSpaceIsLandable(board,piece,start,next)) {
		Move m = getJumpMove(board, piece, start, next);
		moves->moves[moves->count++] = m; // ITS RIGHT HERE - IS COUNT WRONG?!!!
	}
}

void searchJumps(Moves *initialMoves, Board *board, Piece *piece, Moves *finalMoves, CoordinateProducer coordProducer) {
	for (int i = 0; i < initialMoves->count; i++) {
		Move *move = &(initialMoves->moves[i]);
		piece = getPiece(move->whichPiece);

		// Get the next jump moves.
		Moves nextMovesForThisMove;
		nextMovesForThisMove.count = 0;
		Coordinate landingSpot = move->to;

		// Let's assume we execute the move.
		int colorBefore = piece->color;
		move->execute(move);
		int colorAfter = piece->color;
		if (colorBefore != colorAfter) {
			printf("Color of piece does not match!\n");
			exit(-1);
		}
		CoordinateSet coordinates = coordProducer(move->to, piece, board);
		for (int cIndex = 0; cIndex < coordinates.numCoords; cIndex++) {
			Coordinate c = coordinates.coords[cIndex];
			if (isValidPosition(board,c) && pieceIsJumpable(board,piece,c) && nextSpaceIsLandable(board,piece,landingSpot,c)) { // Are c and landingSpot swapped?

				Move m = getMultiJumpMove(board, piece, landingSpot, c, move);

				nextMovesForThisMove.moves[nextMovesForThisMove.count++] = m;
			}
		}

		move->unExecute(move);

		// If there are any, then we replace this move with those moves AND THEIR CONTINUED MOVES
		if (nextMovesForThisMove.count> 0) {
			searchJumps(&nextMovesForThisMove, board, piece, finalMoves, coordProducer);
		}
		else {
			// Otherwise we don't have to jump more, and just add this move.
			finalMoves->moves[finalMoves->count++] = *move;
		}
	}
}

Moves singlePieceSimpleMoves(Board *board, Coordinate start, Piece *piece) {
	Moves moves;
	moves.count = 0;

	addSimpleMovesForPiece(start, piece, board, (piece->direction == FORWARD ? forwardCoordinateProducer : backwardCoordinateProducer), &moves);

	//addSimpleMoveForPiece(start, LEFT, piece->direction, piece, board, &moves);
	//addSimpleMoveForPiece(start, RIGHT, piece->direction, piece, board, &moves);

	return moves;
}

Moves singlePieceJumpMoves(Board *board, Coordinate start, Piece *piece) {
	Moves initialMoves;
	initialMoves.count = 0;

	addJumpMoveForPiece(start, LEFT, piece->direction, piece, board, &initialMoves);
	addJumpMoveForPiece(start, RIGHT, piece->direction, piece, board, &initialMoves);

	Moves finalMoves;
	finalMoves.count = 0;
	searchJumps(&initialMoves, board, piece, &finalMoves, SINGLE_COORD_PRODUCER(piece));

	return finalMoves;
}

Moves kingPieceSimpleMoves(Board *board, Coordinate start, Piece *piece) {
	Moves moves;
	moves.count = 0;

	addSimpleMoveForPiece(start, LEFT, FORWARD, piece, board, &moves);
	addSimpleMoveForPiece(start, RIGHT, FORWARD, piece, board, &moves);
	addSimpleMoveForPiece(start, LEFT, BACKWARDS, piece, board, &moves);
	addSimpleMoveForPiece(start, RIGHT, BACKWARDS, piece, board, &moves);

	return moves;
}

Moves kingPieceJumpMoves(Board *board, Coordinate start, Piece *piece) {
	Moves initialMoves;
	initialMoves.count = 0;

	addJumpMoveForPiece(start, LEFT, FORWARD, piece, board, &initialMoves);
	addJumpMoveForPiece(start, RIGHT, FORWARD, piece, board, &initialMoves);
	addJumpMoveForPiece(start, LEFT, BACKWARDS, piece, board, &initialMoves);
	addJumpMoveForPiece(start, RIGHT, BACKWARDS, piece, board, &initialMoves);

	Moves finalMoves;
	finalMoves.count = 0;
	searchJumps(&initialMoves, board, piece, &finalMoves, &kingCoordinateProducer);
	return finalMoves;
}

void printPiece(Piece *piece) {
	char * color = (piece->color==BLACK?"black":(piece->color==RED?"red":"???"));
	char * pieceType = (piece->canBeKinged?"piece":"king");
	char * movement = (piece->canBeKinged?(piece->direction == FORWARD?"moving forward":"moving backwards"):"");
	printf("%s %s %s\n",color,pieceType,movement);
}
