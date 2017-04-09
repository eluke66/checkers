/*
 * SinglePieceTests.c
 *
 *  Created on: Apr 2, 2017
 *      Author: luke
 */

#include "TestUtils.h"
#include "Types.h"
#include "Board.h"

#define INIT_BOARD_WITH_BLACK_AT(r,c) \
	Board board; \
	initialize(&board); \
	Coordinate blackLocation = COORD((r), (c)); \
	Piece *blackPiece = getPieceAt(&board, blackLocation);\
	makeSinglePiece(blackPiece, BLACK, FORWARD);

#define RED_PIECE_AT(r,c) \
	makeSinglePiece(getPieceAt(&board, COORD((r),(c))),RED, BACKWARDS);


void BlackHasTwoForwardMoves() {
	INIT_BOARD_WITH_BLACK_AT(0,2);

	Moves moves = blackPiece->getSimpleMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(2, moves.count);
	for (int i = 0; i < moves.count; i++) {
			Move move = moves.moves[i];
			ASSERT_TRUE( \
					EQUAL_COORDS(move.to, COORD(1,1)) || \
					EQUAL_COORDS(move.to, COORD(1,3)))

		}
}

void RedHasTwoForwardMoves() {
	Board board;
	initialize(&board);
	Coordinate redLocation = COORD(4, 2);

	Piece *piece = getPieceAt(&board, redLocation);
	makeSinglePiece(piece, RED, BACKWARDS);

	Moves moves = piece->getSimpleMoves(&board, redLocation, piece);
	ASSERT_EQ_INT(2, moves.count);
	for (int i = 0; i < moves.count; i++) {
			Move move = moves.moves[i];
			ASSERT_TRUE( \
					EQUAL_COORDS(move.to, COORD(3,1)) || \
					EQUAL_COORDS(move.to, COORD(3,3)))

		}
}

void SPCannotJumpWhenBlocked() {
	INIT_BOARD_WITH_BLACK_AT(0,0);
	RED_PIECE_AT(1,1);
	RED_PIECE_AT(2,2);

	Moves moves = blackPiece->getJumpMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(0, moves.count);
}

void CannotJumpOwnMan() {
	INIT_BOARD_WITH_BLACK_AT(0,0);
	makeSinglePiece(getPieceAt(&board, COORD(1,1)),BLACK, FORWARD);

	Moves moves = blackPiece->getJumpMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(0, moves.count);
}

void CannotMoveOffTheBoardOrWhenBlocked() {
	INIT_BOARD_WITH_BLACK_AT(0,0);
	RED_PIECE_AT(1,1);

	Moves moves = blackPiece->getSimpleMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(0, moves.count);
}

void CanJumpMoreThanOnceAndThosePiecesAreRemoved() {
	INIT_BOARD_WITH_BLACK_AT(0,0);
	RED_PIECE_AT(1,1);
	RED_PIECE_AT(3,3);

	Moves moves = blackPiece->getJumpMoves(&board, blackLocation, blackPiece);

	EXECUTE_FIRST(moves);

	ASSERT_NO_PIECES_FOR_COLOR(board,RED);
	ASSERT_NO_PIECE(board,1,1);
	ASSERT_NO_PIECE(board,0,0);

	blackPiece = getPieceAt(&board, COORD(4,4));
	ASSERT_EQ_INT(BLACK, blackPiece->color);
}

void CanHaveTwoForwardSingleJumps() {
	INIT_BOARD_WITH_BLACK_AT(0,2);
	RED_PIECE_AT(1,1);
	RED_PIECE_AT(1,3);

	Moves moves = blackPiece->getJumpMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(2, moves.count);

	for (int i = 0; i < moves.count; i++) {
				Move move = moves.moves[i];
				ASSERT_TRUE( \
						EQUAL_COORDS(move.to, COORD(2,0)) || \
						EQUAL_COORDS(move.to, COORD(2,4)))

			}
}

void CanHaveMultipleForwardMultiJumps() {
	INIT_BOARD_WITH_BLACK_AT(0,2);
	RED_PIECE_AT(1,1);
	RED_PIECE_AT(1,3);
	RED_PIECE_AT(3,5);

	Moves moves = blackPiece->getJumpMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(2, moves.count);

	for (int i = 0; i < moves.count; i++) {
				Move move = moves.moves[i];
				ASSERT_TRUE( \
						EQUAL_COORDS(move.to, COORD(2,0)) || \
						EQUAL_COORDS(move.to, COORD(4,6)))

			}
}

void WhenJumpsIntoTheBackRowItIsKinged() {
	INIT_BOARD_WITH_BLACK_AT(BOARD_SIZE-3,1);
	RED_PIECE_AT(BOARD_SIZE-2,2);

	Moves moves = blackPiece->getJumpMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(1, moves.count);

	EXECUTE_FIRST(moves);

	blackPiece = getPieceAt(&board, COORD(BOARD_SIZE-1,3));
	ASSERT_EQ_INT(BLACK, blackPiece->color);
	ASSERT_FALSE(blackPiece->canBeKinged);
}

void CanJumpOnceAndThatPieceIsRemoved() {
	INIT_BOARD_WITH_BLACK_AT(0,0);
	RED_PIECE_AT(1,1);

	Moves moves = blackPiece->getJumpMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(1, moves.count);

	EXECUTE_FIRST(moves);

	ASSERT_NO_PIECES_FOR_COLOR(board,RED);
	ASSERT_NO_PIECE(board,1,1);
	ASSERT_NO_PIECE(board,0,0);

	blackPiece = getPieceAt(&board, COORD(2,2));
	ASSERT_EQ_INT(BLACK, blackPiece->color);
}

void WhenMoveIntoTheBackRowItIsKinged() {
	INIT_BOARD_WITH_BLACK_AT(BOARD_SIZE-2,0);

	Moves moves = blackPiece->getSimpleMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(1, moves.count);

	EXECUTE_FIRST(moves);

	blackPiece = getPieceAt(&board, COORD(BOARD_SIZE-1,1));
	ASSERT_EQ_INT(BLACK, blackPiece->color);
	ASSERT_FALSE(blackPiece->canBeKinged);
}

int runSinglePieceTests() {
	START_TESTS(SinglePieces);

	TEST(BlackHasTwoForwardMoves);
	TEST(RedHasTwoForwardMoves);
	TEST(SPCannotJumpWhenBlocked);
	TEST(CannotJumpOwnMan);
	TEST(CannotMoveOffTheBoardOrWhenBlocked);
	TEST(CanJumpMoreThanOnceAndThosePiecesAreRemoved);
	TEST(CanHaveTwoForwardSingleJumps);
	TEST(CanHaveMultipleForwardMultiJumps);
	TEST(WhenJumpsIntoTheBackRowItIsKinged);
	TEST(CanJumpOnceAndThatPieceIsRemoved);
	TEST(WhenMoveIntoTheBackRowItIsKinged);

	END_TESTS;
}

