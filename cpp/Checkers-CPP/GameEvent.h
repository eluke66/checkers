#ifndef _GAME_EVENT_H_
#define _GAME_EVENT_H_

#include "Color.h"
class Player;
class Board;

class PlayerTurn {
public:
	const int turn;
	const Player *player;
	const Board &board;
	const Color color;

	PlayerTurn(int turn, const Player *player, const Board &board, Color &color) : turn(turn), player(player), board(board), color(color) {}
};

class GameFinished {
public:
	const int turn;
	const Player *winner;

	GameFinished(int turn, const Player *winner) : turn(turn), winner(winner) {}
};
#endif
