/*
 * ConsolePlayer.h
 *
 *  Created on: Mar 26, 2017
 *      Author: luke
 */

#ifndef CONSOLEPLAYER_H_
#define CONSOLEPLAYER_H_

#include "Player.h"
#include "CheckerTypes.h"

class ConsolePlayer: public Player {
public:
	ConsolePlayer();
	virtual ~ConsolePlayer();
	virtual MoveType selectMove(Moves &moves, Board &board) const;

};

#endif /* CONSOLEPLAYER_H_ */
