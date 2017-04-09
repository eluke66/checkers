/*
 * TestUtils.h
 *
 *  Created on: Apr 1, 2017
 *      Author: luke
 */

#ifndef TESTUTILS_H_
#define TESTUTILS_H_

#include <stdio.h>

#define START_TESTS(name) \
		int globalFailures = 0; \
		int testsPassed = 0; \
		int totalTests = 0; \
		int testsSkipped = 0; \
		fprintf(stderr, "  Running %s Tests\n", #name);\
		fprintf(stderr, "  =========================\n");

#define END_TESTS \
		if (globalFailures > 0) { fprintf(stderr, "  Failed %d/%d tests\n", globalFailures, totalTests); } \
		else { fprintf(stderr, "  Passed %d/%d tests", testsPassed, totalTests); \
			if (testsSkipped > 0) { fprintf(stderr, " SKIPPING %d", testsSkipped); } \
			fprintf(stderr, "\n\n"); \
		} \
		return globalFailures;

#define TEST(name) \
		returnValue = 0; \
		fprintf(stderr, "\t%s...", #name ); totalTests++; \
		name(); \
		if (returnValue) { fprintf(stderr, "FAIL!\n"); globalFailures++; } else { fprintf(stderr, "OK!\n"); testsPassed++; }

#define SKIP_TEST(name) \
		fprintf(stderr, "\tSKIPPING %s...\n", #name ); testsSkipped++; totalTests++;

#define FAIL(format, ...) \
		fprintf(stderr, format "\n", __VA_ARGS__); \
		returnValue = 1; \
		return;

#define ASSERT_NO_PIECE(board,row,col) \
		if (isPiece(getPieceAt(&board,COORD((row),(col))))) { FAIL("Found unexpected piece at %d,%d",(row),(col)); }

#define ASSERT_PIECE(board,row,col) \
		if (!isPiece(getPieceAt(&board,COORD((row),(col))))) { FAIL("Didn't find expected piece at %d,%d",(row),(col)); }

#define ASSERT_NO_PIECES_FOR_COLOR(board,color) \
		if (getPiecesForColor(&board, (color)).count > 0) { FAIL("Found unexpected pieces for %s",(color)==BLACK?"black":"red"); }

#define ASSERT_EQ_INT(a,b) \
		if ( (a) != (b) ) { \
			FAIL("Expected %d but got %d (%s != %s)] ", (a), (b), #a, #b) \
		}

#define ASSERT_PRESENT(a) \
		if ((a) == NULL) { FAIL("Expected %s to be non-null but was 0x%p",#a, (a)); }

#define ASSERT_NULL(a) \
		if ((a) != NULL) { FAIL("Expected %s to be null but was 0x%p",#a, (a)); }

#define ASSERT_TRUE(a) \
		if (!(a)) { FAIL("Expected %s to be true but was %d",#a, (a)); }

#define ASSERT_FALSE(a) \
		if ((a)) { FAIL("Expected %s to be false but was %d",#a, (a)); }

#define EXECUTE_FIRST(moves) \
		moves.moves[0].execute(&(moves.moves[0]));

int returnValue;

#endif /* TESTUTILS_H_ */
