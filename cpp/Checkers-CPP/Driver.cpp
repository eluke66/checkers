#include <iostream>
#include <string>

#include "Board.h"
#include "Game.h"
#include "ConsolePlayer.h"
#include "RandomChoicePlayer.h"
#include "ConsoleObserver.h"

void profile(int numGames) {
	timespec start,end;
	long totalTimeNs = 0;
	long NANO = 1000000000;
	for (int i = 0; i < numGames; i++) {
		Game game (new RandomChoicePlayer(), new RandomChoicePlayer());
		clock_gettime(CLOCK_REALTIME, &start);
		game.play();
		clock_gettime(CLOCK_REALTIME, &end);
		totalTimeNs += (end.tv_sec*NANO + end.tv_nsec) - (start.tv_sec*NANO + start.tv_nsec);

	}
	long timeInMs = (totalTimeNs / 1000000);
	std::cout << "Executed " << numGames << " in " << timeInMs << " ms, or " << (float)timeInMs/(float)numGames << " ms/game" << std::endl;
}

void console() {
	Game game(new ConsolePlayer(), new ConsolePlayer());
	game.observe(&ConsoleObserver::turn, &ConsoleObserver::end);

	std::cout << "Playing!" << std::endl;
	const Player *winner = game.play();
	std::cout << "Winner is " << winner << std::endl;
}
int main(int argc, char ** argv) {
	if (argc > 1) {
		profile(std::stoi(argv[1]));
	}
	else {
		console();
	}
	return EXIT_SUCCESS;
}
