/*
 * Player.h
 *
 *  Created on: Mar 26, 2017
 *      Author: luke
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "CheckerTypes.h"
class Board;

class Player {
public:
	virtual ~Player() {}
	virtual MoveType selectMove(Moves &moves, Board &board) const = 0;
};


#endif /* PLAYER_H_ */
