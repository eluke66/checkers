/*
 * Tests.c
 *
 *  Created on: Apr 1, 2017
 *      Author: luke
 */

#include <stdio.h>

int runGameTests();
int runKingPieceTests();
int runSinglePieceTests();
int runMoveRulesTests();

int main(int argc, char **argv) {
	int failures = 0;
	fprintf(stderr, "Running Tests\n");
	failures += runGameTests();
	failures += runKingPieceTests();
	failures += runSinglePieceTests();
	failures += runMoveRulesTests();
	fprintf(stderr, "Total failures: %d\n", failures);
	return failures;
}

