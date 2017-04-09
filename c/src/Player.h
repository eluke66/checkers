/*
 * Player.h
 *
 *  Created on: Apr 6, 2017
 *      Author: luke
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Move.h"
#include "Board.h"

typedef Move (*MoveSelector)(Moves moves, Board *board);

typedef struct {
	color_t color;
	MoveSelector selectMove;
} player_t;



#endif /* PLAYER_H_ */
