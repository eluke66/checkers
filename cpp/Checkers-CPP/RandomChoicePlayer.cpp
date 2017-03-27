/*
 * RandomChoicePlayer.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: luke
 */

#include "RandomChoicePlayer.h"
#include "Move.h"
#include "Board.h"

RandomChoicePlayer::RandomChoicePlayer() {
	// TODO Auto-generated constructor stub

}

RandomChoicePlayer::~RandomChoicePlayer() {
	// TODO Auto-generated destructor stub
}

Move* RandomChoicePlayer::selectMove(std::list<Move*>& moves,
		Board& board) const {
	std::list<Move*>::const_iterator it = moves.begin();
	const unsigned long n = std::distance(moves.begin(), moves.end());
	const unsigned long divisor = (RAND_MAX + 1) / n;

	unsigned long k;
	do { k = std::rand() / divisor; } while (k >= n);

	std::advance(it, k);
	return *it;
}
