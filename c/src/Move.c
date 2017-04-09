/*
 * Move.c
 *
 *  Created on: Mar 30, 2017
 *      Author: luke
 */

#include "Move.h"
#include "Piece.h"
#include "Board.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/////// PIECE RING BUFFER CACHE /////////////////
#define NUM_PIECES 2000
static const int NO_PIECE_INDEX = -1;
int currentPiece = 0;
Piece pieceBuffer[NUM_PIECES];

Piece *getPiece(int whichPiece) {
	return &pieceBuffer[whichPiece];
}

int installPiece(Piece *piece) {
	int returnValue = currentPiece;
	pieceBuffer[returnValue] = *piece;
	currentPiece = (currentPiece + 1) % NUM_PIECES;
	//printf("Installing piece of color %d for index %d, next index is %d\n", piece->color, returnValue, currentPiece);
	return returnValue;
}
/////////////////////////////////////////////////


typedef struct _JumpMoveData {
	Coordinate existingPieceLocation;
	int whichPiece;
} JumpMoveData;

typedef struct _MultiJumpMoveData {
	JumpMoveData jumpMoveData;
	Move *previousMove;
} MultiJumpMoveData;

void executeSimpleMove(struct _Move *move) {
	removePieceAt(move->board, move->from);
	moveAndKingPiece(getPiece(move->whichPiece), move->board, move->to);
}

void unExecuteSimpleMove(struct _Move *move) {
	removePieceAt(move->board, move->to);
	placePieceAt(move->board, getPiece(move->whichPiece), move->from);
}

void executeJumpMove(struct _Move *move) {
	JumpMoveData *jumpMoveData = (JumpMoveData *)(move->extraData);
	if (jumpMoveData->whichPiece == NO_PIECE_INDEX) {
		jumpMoveData->whichPiece = installPiece(getPieceAt(move->board, jumpMoveData->existingPieceLocation));
		moveAndKingPiece(getPiece(move->whichPiece), move->board, move->to);
		removePieceAt(move->board, move->from);
		removePieceAt(move->board, jumpMoveData->existingPieceLocation);
	}
	else {
		fprintf(stderr, "Trying to re-jump piece at index %d\n", jumpMoveData->whichPiece);
	}
}

void unExecuteJumpMove(struct _Move *move) {
	JumpMoveData *jumpMoveData = (JumpMoveData *)(move->extraData);
	if (jumpMoveData->whichPiece != NO_PIECE_INDEX) {
		removePieceAt(move->board, move->to);
		placePieceAt(move->board, getPiece(move->whichPiece), move->from);
		placePieceAt(move->board, getPiece(jumpMoveData->whichPiece), jumpMoveData->existingPieceLocation);
		jumpMoveData->whichPiece = NO_PIECE_INDEX;
	}
	else {
		fprintf(stderr, "Trying to un-rejump piece for move 0x%x", move);
	}
}

void executeMultiJumpMove(struct _Move *move) {
	MultiJumpMoveData *data = (MultiJumpMoveData *)(move->extraData);
	data->previousMove->execute(data->previousMove);
	executeJumpMove(move);
}

void unExecuteMultiJumpMove(struct _Move *move) {
	unExecuteJumpMove(move);
	MultiJumpMoveData *data = (MultiJumpMoveData *)(move->extraData);
	data->previousMove->unExecute(data->previousMove);
}


Move addSimpleMove(Board *board, Piece *piece, Coordinate from, Coordinate to) {
	Move move; memset(&move,0,sizeof(move));
	move.board = board;
	move.whichPiece = installPiece(piece);
	move.from = from;
	move.to = to;
	move.execute = &executeSimpleMove;
	move.unExecute = &unExecuteSimpleMove;
	move.extraData = NULL;
	return move;
}

Move addJumpMove(Board *board, Piece *piece, Coordinate from, Coordinate to) {
	Move move; memset(&move,0,sizeof(move));
	move.board = board;
	move.whichPiece = installPiece(piece);
	move.from = from;
	move.to = EXTENDING_COORDINATE(from, to);
	move.execute = &executeJumpMove;
	move.unExecute = &unExecuteJumpMove;
	JumpMoveData * data = (JumpMoveData *)malloc(sizeof(JumpMoveData));
	data->existingPieceLocation = to;
	data->whichPiece = NO_PIECE_INDEX;
	move.extraData = data;
	return move;
}

Move addMultiJumpMove(Board *board, Piece *piece, Coordinate from, Coordinate to, Move *previousMove) {
	Move move; memset(&move,0,sizeof(move));
	move.board = board;
	move.whichPiece = installPiece(piece);
	move.from = from;
	move.to = EXTENDING_COORDINATE(from, to);
	move.execute = &executeMultiJumpMove;
	move.unExecute = &unExecuteMultiJumpMove;

	MultiJumpMoveData * data = (MultiJumpMoveData *)malloc(sizeof(MultiJumpMoveData));
	data->jumpMoveData.existingPieceLocation = to;
	data->jumpMoveData.whichPiece = NO_PIECE_INDEX;
	data->previousMove = previousMove;
	move.extraData = data;

	// Ensure that the previous move ending point is the same as our starting point!
	if (previousMove->to.row != from.row || previousMove->to.col != from.col) {
		fprintf(stderr, "Move.c - mismatched from/to coords!\n");
		exit(-1);
	}
	return move;
}

void printMoves(Moves *moves) {
	for (int i = 0; i < moves->count; i++) {
		printf("%d: (0x%x) ", i, &moves->moves[i]); printMove(&moves->moves[i]);
	}
}

#define CNAME(piece) (piece->color==BLACK?"black":"red")
#define PTYPE(piece) (piece->canBeKinged?"piece":"king")

char moveInformation[1024];
int depth = 1;

char * printJump(Move *move, char *buffer) {
	int charsWritten;
	if (move->execute == &executeMultiJumpMove) {
		// Multi jump
		MultiJumpMoveData *data = (MultiJumpMoveData *)move->extraData;
		Move *previousMove = data->previousMove;
		depth++;
		buffer = printJump(previousMove, buffer);
		depth--;
		// Add a newline and N spaces
		buffer[0] = '\n'; buffer+=sizeof(char);
		memset(buffer, ' ', depth);
		buffer += depth*sizeof(char);
		// jumping red king from 1-2-3
		//   jumping red piece from 3-4-5
		//    ....
	}

	// Single jump
	JumpMoveData * data = (JumpMoveData *)move->extraData;
	Piece *pieceBeingJumped = getPiece(data->whichPiece);
	charsWritten =
			sprintf(buffer, "jumping a %s %s from (%d,%d)-(%d,%d)-(%d,%d)",
					CNAME(pieceBeingJumped), PTYPE(pieceBeingJumped),
					move->from.row,move->from.col,
					data->existingPieceLocation.row,  data->existingPieceLocation.col,
					move->to.row,move->to.col);

	return buffer + sizeof(char) * charsWritten;
}

void printMove(Move *move) {
	Piece *piece = getPiece(move->whichPiece);

	if (move->extraData != NULL) {
		memset(moveInformation, 0, 1024);
		printJump(move, moveInformation);
//		if (move->execute == &executeMultiJumpMove) {
//			// Multi jump
//			MultiJumpMoveData *data = (MultiJumpMoveData *)move->extraData;
//			Piece *pieceBeingJumped = getPiece(data->jumpMoveData->whichPiece);
//			Move *previousMove = data->previousMove;
//		}
//		else {
//			// Single jump
//			JumpMoveData * data = (JumpMoveData *)move->extraData;
//			Piece *pieceBeingJumped = getPiece(data->whichPiece);
//			sprintf(moveInformation, "jumping a %s %s from (%d,%d)-(%d,%d)-(%d,%d)",
//					CNAME(pieceBeingJumped), PTYPE(pieceBeingJumped),
//					data->existingPieceLocation.row,  data->existingPieceLocation.col,
//					move->from.row,move->from.col,move->to.row,move->to.col);
//		}
	}
	else {
		// Simple
		sprintf(moveInformation, "moving from (%d,%d) to (%d,%d)", move->from.row,move->from.col,move->to.row,move->to.col);
	}
	//char * moveType = move->extraData == NULL ? "Simple" : (sizeof(move->extraData) == sizeof(MultiJumpMoveData) ? "Multi jump" : "Jump");
	printf("%s %s %s\n", CNAME(piece), PTYPE(piece), moveInformation);
}

