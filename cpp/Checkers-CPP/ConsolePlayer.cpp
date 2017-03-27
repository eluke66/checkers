/*
 * ConsolePlayer.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: luke
 */

#include "ConsolePlayer.h"
#include "Board.h"
#include "Move.h"
#include <iostream>
#include <vector>

ConsolePlayer::ConsolePlayer() {
	// TODO Auto-generated constructor stub

}

ConsolePlayer::~ConsolePlayer() {
	// TODO Auto-generated destructor stub
}

Move* ConsolePlayer::selectMove(std::list<Move*>& moves, Board& board) const {
	std::cout << "Board is " << board.toString() << std::endl;

	std::vector<Move *> moveVector;
	moveVector.insert(moveVector.begin(), moves.begin(), moves.end());

	for (unsigned i = 0; i < moveVector.size(); i++) {
		std::cout << i << ": " << moveVector[i]->toString() << std::endl;
	}
	unsigned choice;
	while (true) {
		std::cout << std::endl << "Enter a choice: " << std::flush;
		std::cin >> choice;
		if (choice < 0 || choice >= moveVector.size() ) {
			std::cout << "Invalid choice " << choice << std::endl;
		}
		else {
			break;
		}
	}

	return moveVector[choice];
}
