/*
 * Player.h
 *
 *  Created on: Mar 26, 2017
 *      Author: luke
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <list>
class Move;
class Board;

class Player {
public:
	virtual Move * selectMove(std::list<Move *> &moves, Board &board) const = 0;
};


#endif /* PLAYER_H_ */
