/*
 * Board.h
 *
 *  Created on: Mar 30, 2017
 *      Author: luke
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "Piece.h"
#include "Types.h"

#define BOARD_SIZE 8
typedef struct _Board {
	Piece pieces[BOARD_SIZE][BOARD_SIZE];
} Board;

typedef struct {
	Piece piece;
	Coordinate coordinate;
} PlacedPiece;

typedef struct {
	PlacedPiece pieces[12];
	int count;
} PieceList;

extern void initialize(Board *board);
extern int isPiece(Piece *piece);
extern PieceList getPiecesForColor(Board *board, color_t color);
extern int isValidPosition(Board *board, Coordinate coordinate);
extern Piece *getPieceAt(Board *board, Coordinate coordinate);
extern void removePieceAt(Board *board, Coordinate coordinate);
extern void placePieceAt(Board *board, Piece *piece, Coordinate coordinate);
extern void moveAndKingPiece(Piece *piece, Board *board, Coordinate coordinate);
extern int pieceIsJumpable(Board *board, Piece *piece, Coordinate location);
extern int nextSpaceIsLandable(Board *board, Piece *piece, Coordinate location, Coordinate next);
extern void printBoard(Board *board);
#endif /* BOARD_H_ */
