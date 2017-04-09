/*
 * Game.h
 *
 *  Created on: Mar 29, 2017
 *      Author: luke
 */

#ifndef GAME_H_
#define GAME_H_

#include "Piece.h"
#include "Move.h"
#include "Board.h"
#include "Player.h"
#include "Events.h"


extern player_t play(player_t player1, player_t player2, EventReceiver eventReceiver);


extern void putPiecesOnTheBoard(Board *board);

#endif /* GAME_H_ */
