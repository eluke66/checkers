/*
 * RandomChoicePlayer.h
 *
 *  Created on: Mar 26, 2017
 *      Author: luke
 */

#ifndef RANDOMCHOICEPLAYER_H_
#define RANDOMCHOICEPLAYER_H_

#include "Player.h"

class RandomChoicePlayer: public Player {
public:
	RandomChoicePlayer();
	virtual ~RandomChoicePlayer();
	virtual MoveType selectMove(Moves &moves, Board &board) const;
};

#endif /* RANDOMCHOICEPLAYER_H_ */
