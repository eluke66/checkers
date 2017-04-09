/*
 * Board.c
 *
 *  Created on: Mar 30, 2017
 *      Author: luke
 */

#include <stdio.h>
#include "Board.h"
#define NO_PIECE -1

#define VALIDATE_POSITION(coordinate,op) \
		if (!isValidPosition(board, coordinate)) { \
			fprintf(stderr, "Cannot %s piece at %d,%d as the location is invalid",#op,coordinate.row, coordinate.col); \
			return NULL; \
		}

#define MAKE_NO_PIECE(row, col) \
		board->pieces[row][col].color = NO_PIECE

int isFinalRowForPiece(Piece *piece, Coordinate dest) {
	return (piece->color == RED && dest.row == 0) || (piece->color == BLACK && dest.row == (BOARD_SIZE-1));
}

void moveAndKingPiece(Piece *piece, Board *board, Coordinate dest) {
	//printf("Board.c: moving piece to %d,%d: ", dest.row, dest.col); printPiece(piece);
	if (isFinalRowForPiece(piece, dest) && piece->canBeKinged) {
		makeKingPiece(getPieceAt(board, dest), piece->color);
	}
	else {
		placePieceAt(board, piece, dest);
	}
}
void removePieceAt(Board *board, Coordinate coordinate) {
	//printf("Board.c: Removing piece 0x%x from %d,%d\n", &(board->pieces[coordinate.row][coordinate.col]), coordinate.row, coordinate.col);
	MAKE_NO_PIECE(coordinate.row,coordinate.col);
}

void placePieceAt(Board *board, Piece *piece, Coordinate coordinate) {
	//printf("Board.c: Placing piece %d on %d,%d\n", piece->color, coordinate.row, coordinate.col);
	board->pieces[coordinate.row][coordinate.col] = *piece;
	//printPiece(piece);
}

PieceList getPiecesForColor(Board *board, color_t color) {
	PieceList pieces;
	pieces.count = 0;
	for (unsigned row = 0; row < BOARD_SIZE; row++) {
		for (unsigned col = 0; col < BOARD_SIZE; col++) {
			Piece piece = board->pieces[row][col];
			if (piece.color == color) {
				if (pieces.count == 12) {
					fprintf(stderr, "WTF WE HAVE 13 pieces on the board!!!!\n");
					printBoard(board);
				}
				pieces.pieces[pieces.count].coordinate = (Coordinate){.row=row, .col=col};
				pieces.pieces[pieces.count++].piece = piece;
			}
		}
	}
	return pieces;
}


void initialize(Board *board) {
	for (unsigned row = 0; row < BOARD_SIZE; row++) {
		for (unsigned col = 0; col < BOARD_SIZE; col++) {
			MAKE_NO_PIECE(row,col);
		}
	}
}

int isPiece(Piece *piece) {
	return piece->color != NO_PIECE;
}

int isEven(unsigned i) {
	return i % 2 == 0;
}

int isUsableSquare(unsigned row, unsigned col) {
	return (isEven(row) && isEven(col)) || (!isEven(row) && !isEven(col));
}

int isValidPosition(Board *board, Coordinate c) {
	return 	c.row >= 0 &&
			c.row < BOARD_SIZE &&
			c.col >= 0 &&
			c.col < BOARD_SIZE &&
			isUsableSquare(c.row, c.col);
}

void printPiece(Piece *piece);
int pieceIsJumpable(Board *board, Piece *piece, Coordinate coordinate) {
	Piece *otherPiece = getPieceAt(board, coordinate);
	//printf("Board.c::PIJ Piece is "); printPiece(piece);
	//printf("\tOther piece is "); printPiece(otherPiece);
	//printf("\tAnd isPiece is %d and colorTest is %d\n", isPiece(otherPiece), otherPiece->color != piece->color);
	//printf("\tat %d,%d\n",coordinate.row, coordinate.col);
	return isPiece(otherPiece) && otherPiece->color != piece->color;
}

int nextSpaceIsLandable(Board *board, Piece *piece, Coordinate from, Coordinate to) {
	Coordinate landingSpot = EXTENDING_COORDINATE(from, to);
	return isValidPosition(board, landingSpot) && !isPiece(getPieceAt(board, landingSpot));
}

Piece *getPieceAt(Board *board, Coordinate coordinate) {
	VALIDATE_POSITION(coordinate, "get");
	return &(board->pieces[coordinate.row][coordinate.col]);
}

void printBoard(Board *board) {
	printf("\n  ");
	for (unsigned col = 0; col < BOARD_SIZE; col++) {
		printf("%d", col);
	}
	printf("\n");
	for (unsigned row = 0; row < BOARD_SIZE; row++) {
		printf("%d ", row);
		for (unsigned col = 0; col < BOARD_SIZE; col++) {
			if (!isUsableSquare(row,col)) {
				printf("|");
			}
			else {
				Piece *p = &(board->pieces[row][col]);
				if (!isPiece(p)) { printf("_"); }
				else if (p->color == BLACK) {
					if (p->canBeKinged) { printf("b"); }
					else { printf("B"); }
				}
				else if (p->color == RED) {
					if (p->canBeKinged) { printf("r"); }
					else { printf("R"); }
				}
				else { printf("?"); }
			}
		}
		printf("\n");
	}
}
