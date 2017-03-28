/*
 * Game.h
 *
 *  Created on: Mar 26, 2017
 *      Author: luke
 */

#ifndef GAME_H_
#define GAME_H_

#include <map>
#include <vector>
#include <boost/signals2/signal.hpp>

#include "Color.h"
#include "MoveRules.h"
#include "GameEvent.h"
class Player;

class Game {
public:
	Game(const Player *player1, const Player *player2) : Game(player1, player2, *(new MoveRules())) {}

	Game(const Player *player1, const Player *player2, MoveRules &moveRules);

	const Player* play();

	typedef boost::signals2::signal<void (PlayerTurn)>  turn_signal_t;
	typedef boost::signals2::signal<void (GameFinished)>  end_signal_t;
	void observe(const turn_signal_t::slot_type &turnFunction, const end_signal_t::slot_type gameEndFunction) {
		turnSignal.connect(turnFunction);
		endSignal.connect(gameEndFunction);
	}
private:
	Board board;
	std::vector<const Player *> players;
	MoveRules &moveRules;
	std::map<const Player *,Color> colorsPerPlayer;
	turn_signal_t turnSignal;
	end_signal_t endSignal;

	static void putPiecesOnTheBoard(Board &board);
	bool playerHasValidMoves(const Moves& moves) {
		return moves.size() > 0;
	}

	int otherPlayer(int player) {
		return (player+1) % 2;
	}
};

#endif /* GAME_H_ */
