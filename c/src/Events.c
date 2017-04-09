/*
 * Events.c
 *
 *  Created on: Apr 9, 2017
 *      Author: luke
 */

#include "Events.h"

Event playerTurn(int whichTurn, player_t currentPlayer, Board *board, color_t color) {
	return (Event){.type=turn, .turn=whichTurn, .player=currentPlayer, .board=board, .color=color };
}
Event gameFinished(int whichTurn, player_t winner) {
	return (Event){.type=game, .turn=whichTurn, .player=winner};
}

void noopEvent(Event e) {}

