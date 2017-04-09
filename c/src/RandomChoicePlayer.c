#include "RandomChoicePlayer.h"
#include "Move.h"
#include "Board.h"
#include <stdlib.h>

// See http://stackoverflow.com/questions/2999075/generate-a-random-number-within-range/2999130#2999130
int rand_lim(int limit) {
/* return a random number between 0 and limit inclusive.
 */

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do {
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

Move selectRandomMove(Moves moves, Board *board) {
	int whichMove = rand_lim(moves.count-1);
	return moves.moves[whichMove];
}

MoveSelector randomChoiceSelector = &selectRandomMove;
