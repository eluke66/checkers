/*
 ============================================================================
 Name        : Checkers-C.c
 Author      : Eric Luke
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Game.h"
#include "RandomChoicePlayer.h"
#include "ConsolePlayer.h"

void profile(int numGames) {
	srand(100);
	struct timespec start,end;
	long totalTimeNs = 0;
	long NANO = 1000000000;
	player_t player1 = (player_t) {.color=BLACK, .selectMove=randomChoiceSelector};
	player_t player2 = (player_t) {.color=RED, .selectMove=randomChoiceSelector};

	for (int i = 0; i < numGames; i++) {
		clock_gettime(CLOCK_REALTIME, &start);
		play(player1, player2, &noopEvent);
		clock_gettime(CLOCK_REALTIME, &end);
		totalTimeNs += (end.tv_sec*NANO + end.tv_nsec) - (start.tv_sec*NANO + start.tv_nsec);

	}
	long timeInMs = (totalTimeNs / 1000000);
	printf("Executed %d games in %ld ms, or %.2f ms/game\n",numGames,timeInMs,(float)timeInMs/(float)numGames);
}

void playGame() {
	player_t player1 = (player_t) {.color=BLACK, .selectMove=consoleSelector};
	player_t player2 = (player_t) {.color=RED, .selectMove=consoleSelector};
	play(player1, player2, consoleEventReporter);
}

int main(int argc, char ** argv) {
	if (argc > 1) {
		profile(atoi(argv[1]));
	}
	else {
		playGame();
	}
}
