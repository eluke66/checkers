#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Board.h"
#include "Game.h"
#include "ConsolePlayer.h"
#include "RandomChoicePlayer.h"
#include "ConsoleObserver.h"

void profile() {
	timespec start,end;
	long totalTimeNs = 0;
	long NANO = 1000000000;
	int NUM_GAMES = 400000;
	for (int i = 0; i < NUM_GAMES; i++) {
		Game game (new RandomChoicePlayer(), new RandomChoicePlayer());
		clock_gettime(CLOCK_REALTIME, &start);
		game.play();
		clock_gettime(CLOCK_REALTIME, &end);
		totalTimeNs += (end.tv_sec*NANO + end.tv_nsec) - (start.tv_sec*NANO + start.tv_nsec);

	}
	long timeInMs = (totalTimeNs / 1000000);
	printf("Executed %d games in %d ms, or %.2f ms/game\n", NUM_GAMES, timeInMs, (float)timeInMs/(float)NUM_GAMES );
}

void console() {
	Game game(new ConsolePlayer(), new ConsolePlayer());
	//ConsoleObserver o;
	//game.observe(boost::bind(&ConsoleObserver::turn, o), boost::bind(&ConsoleObserver::end, o));

	std::cout << "Playing!" << std::endl;
	const Player *winner = game.play();
	std::cout << "Winner is " << winner << std::endl;
}
int main(void) {
	profile();
	return EXIT_SUCCESS;
}
