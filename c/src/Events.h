/*
 * Events.h
 *
 *  Created on: Apr 8, 2017
 *      Author: luke
 */

#ifndef EVENTS_H_
#define EVENTS_H_

#include "Player.h"
#include "Types.h"
#include "Board.h"

typedef enum {turn,game} EventType;

typedef struct {
	EventType type;
	int turn;
	player_t player;
	Board *board;
	color_t color;
} Event;
typedef void (*EventReceiver)(Event e);

extern Event playerTurn(int whichTurn, player_t currentPlayer, Board *board, color_t color);
extern Event gameFinished(int whichTurn, player_t winner);
extern void noopEvent(Event e);

#endif /* EVENTS_H_ */
