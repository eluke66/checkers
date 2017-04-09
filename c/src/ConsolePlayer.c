/*
 * ConsolePlayer.c
 *
 *  Created on: Apr 9, 2017
 *      Author: luke
 */

#include "ConsolePlayer.h"
#include <stdio.h>

Move selectMoveViaConsole(Moves moves, Board *board) {
	printBoard(board);

	for (int i = 0; i < moves.count; i++) {
		printf("%d: ", i); printMove(&moves.moves[i]);
	}

	while (1) {
		int choice;

		int argsMatched = scanf("%d", &choice);
		if (argsMatched == 0 || choice < 0 || choice >= moves.count) {
			printf("Invalid choice %d - try again\n", choice);
		}
		else {
			return moves.moves[choice];
		}
	}
}

#define TO_COLOR(c) (c==BLACK?"black":(c==RED?"red":"???"))

void consoleEvent(Event e) {
	if (e.type == turn) {
		printf("Turn %d: Player 0x%p (%s)\n", e.turn, &e.player, TO_COLOR(e.color));
	}
	else if (e.type == game) {
		printf("Game ended on turn %d, won by %s\n", e.turn, TO_COLOR(e.player.color));
	}
	else {
		printf("ERROR: Unknown event type %d\n", e.type);
	}
}

MoveSelector consoleSelector = &selectMoveViaConsole;
EventReceiver consoleEventReporter = &consoleEvent;


