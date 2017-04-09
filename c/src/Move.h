/*
 * Move.h
 *
 *  Created on: Mar 29, 2017
 *      Author: luke
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "Types.h"

struct Piece;

typedef struct _Move {
	void *board;
	//struct Piece *piece;
	int whichPiece;
	Coordinate from;
	Coordinate to;
	void *extraData;
	void (*execute)(struct _Move *move);
	void (*unExecute)(struct _Move *move);
} Move;

#define MAX_MOVES 100
typedef struct {
	Move moves[MAX_MOVES];
	unsigned char count;
} Moves;

extern struct Piece *getPiece(int whichPiece);
extern void printMoves(Moves *moves);
extern void printMove(Move *move);
#endif /* MOVE_H_ */
