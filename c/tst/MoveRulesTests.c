/*
 * MoveRulesTests.c
 *
 *  Created on: Apr 5, 2017
 *      Author: luke
 */

#include "TestUtils.h"
#include "Types.h"
#include "Board.h"
#include "Piece.h"
#include "MoveRules.h"

#define INIT_BOARD_WITH_BLACK_AT(r,c) \
		Board board; \
		initialize(&board); \
		Coordinate blackLocation = COORD((r), (c)); \
		Piece *blackPiece = getPieceAt(&board, blackLocation);\
		makeSinglePiece(blackPiece, BLACK, FORWARD);

#define RED_PIECE_AT(r,c) \
		makeSinglePiece(getPieceAt(&board, COORD((r),(c))),RED, BACKWARDS);

void ifCapturingMovesAreAvailableTheyMustBePickedForSimple() {
	INIT_BOARD_WITH_BLACK_AT(0,2);
	RED_PIECE_AT(1,1);

	Moves moves = getMovesForColor(BLACK, &board);
	ASSERT_EQ_INT(1, moves.count);

	EXECUTE_FIRST(moves);

	ASSERT_NO_PIECES_FOR_COLOR(board,RED);
}
void ifCapturingMovesAreAvailableTheyMustBePickedForMultiJumps() {
	INIT_BOARD_WITH_BLACK_AT(0,2);
	RED_PIECE_AT(1,3);
	RED_PIECE_AT(3,5);

	Moves moves = getMovesForColor(BLACK, &board);
	ASSERT_EQ_INT(1, moves.count);

	EXECUTE_FIRST(moves);

	ASSERT_NO_PIECES_FOR_COLOR(board,RED);


	blackPiece = getPieceAt(&board, COORD(4,6));
	ASSERT_EQ_INT(BLACK, blackPiece->color);
}

int runMoveRulesTests() {
	START_TESTS(MoveRules);
	TEST(ifCapturingMovesAreAvailableTheyMustBePickedForSimple);
	TEST(ifCapturingMovesAreAvailableTheyMustBePickedForMultiJumps);

	END_TESTS;
}

