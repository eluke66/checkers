/*
 * Piece.h
 *
 *  Created on: Mar 29, 2017
 *      Author: luke
 */

#ifndef PIECE_H_
#define PIECE_H_

#include "Types.h"
#include "Move.h"

#define FORWARD 1
#define BACKWARDS -1

struct _Board;
typedef struct Piece Piece;

typedef Moves (*MoveProducer)(struct _Board *board, Coordinate coordinate, Piece *piece);

struct Piece {
	color_t      color;
	int          canBeKinged;
	int          direction;
	MoveProducer getJumpMoves;
	MoveProducer getSimpleMoves;
};

extern void makeSinglePiece(Piece *piece, color_t color, int direction);
extern void makeKingPiece(Piece *piece, color_t color);
extern void printPiece(Piece *piece);

#endif /* PIECE_H_ */
