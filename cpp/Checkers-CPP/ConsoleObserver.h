/*
 * ConsoleObserver.h
 *
 *  Created on: Mar 26, 2017
 *      Author: luke
 */

#ifndef CONSOLEOBSERVER_H_
#define CONSOLEOBSERVER_H_

#include "GameEvent.h"
#include <iostream>

class ConsoleObserver {
public:

	static void turn(PlayerTurn event) {
		std::cout << "Turn " << event.turn << ": Player " << event.player << " (" << event.color << ")" << std::endl;
	}
	static void end(GameFinished event) {
		std::cout << "Game ended on turn " << event.turn << ", won by player " << event.winner << std::endl;
	}
};

#endif /* CONSOLEOBSERVER_H_ */
