/*
 * KingPieceTests.c
 *
 *  Created on: Apr 2, 2017
 *      Author: luke
 */

#include "TestUtils.h"
#include "Types.h"
#include "Board.h"

void KingsCanMoveForwardAndBackwards() {
	Board board;
	initialize(&board);
	Coordinate blackLocation = COORD(2, 2);

	Piece *piece = getPieceAt(&board, blackLocation);
	makeKingPiece(piece, BLACK);

	Moves moves = piece->getSimpleMoves(&board, blackLocation, piece);

	ASSERT_EQ_INT(4, moves.count);
	for (int i = 0; i < moves.count; i++) {
		Move move = moves.moves[i];
		ASSERT_TRUE( \
				EQUAL_COORDS(move.to, COORD(1,1)) || \
				EQUAL_COORDS(move.to, COORD(1,3)) || \
				EQUAL_COORDS(move.to, COORD(3,1)) || \
				EQUAL_COORDS(move.to, COORD(3,3)))

	}
}

void CannotJumpWhenBlocked() {
	Board board;
	initialize(&board);
	Coordinate blackLocation = COORD(0,0);

	Piece *blackPiece = getPieceAt(&board, blackLocation);
	makeKingPiece(blackPiece, BLACK);
	makeKingPiece(getPieceAt(&board, COORD(1,1)),RED);
	makeKingPiece(getPieceAt(&board, COORD(2,2)),RED);

	Moves moves = blackPiece->getJumpMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(0, moves.count);
}

void CanJumpForwardOnce() {
	Board board;
	initialize(&board);
	Coordinate blackLocation = COORD(0,0);

	Piece *blackPiece = getPieceAt(&board, blackLocation);
	makeKingPiece(blackPiece, BLACK);
	makeKingPiece(getPieceAt(&board, COORD(1,1)),RED);

	Moves moves = blackPiece->getJumpMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(1, moves.count);
	EXECUTE_FIRST(moves);

	ASSERT_NO_PIECES_FOR_COLOR(board,RED);
	ASSERT_NO_PIECE(board,1,1);
	ASSERT_NO_PIECE(board,0,0);

	blackPiece = getPieceAt(&board, COORD(2,2));
	ASSERT_EQ_INT(BLACK, blackPiece->color);
}

void CanJumpBackwardsOnce() {
	Board board;
	initialize(&board);
	Coordinate blackLocation = COORD(2,2);

	Piece *blackPiece = getPieceAt(&board, blackLocation);
	makeKingPiece(blackPiece, BLACK);
	makeKingPiece(getPieceAt(&board, COORD(1,1)),RED);

	Moves moves = blackPiece->getJumpMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(1, moves.count);
	EXECUTE_FIRST(moves);

	ASSERT_NO_PIECES_FOR_COLOR(board,RED);
	ASSERT_NO_PIECE(board,1,1);
	ASSERT_NO_PIECE(board,2,2);

	blackPiece = getPieceAt(&board, COORD(0,0));
	ASSERT_EQ_INT(BLACK, blackPiece->color);
}

void CanJumpForwardThenBackwards() {
	Board board;
	initialize(&board);
	Coordinate blackLocation = COORD(2,0);

	Piece *blackPiece = getPieceAt(&board, blackLocation);
	makeKingPiece(blackPiece, BLACK);
	makeKingPiece(getPieceAt(&board, COORD(1,1)),RED);
	makeKingPiece(getPieceAt(&board, COORD(1,3)),RED);

	Moves moves = blackPiece->getJumpMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(1, moves.count);
	EXECUTE_FIRST(moves);

	ASSERT_NO_PIECES_FOR_COLOR(board,RED);
	ASSERT_NO_PIECE(board,1,1);
	ASSERT_NO_PIECE(board,1,3);
	ASSERT_NO_PIECE(board,2,0);

	blackPiece = getPieceAt(&board, COORD(2,4));
	ASSERT_EQ_INT(BLACK, blackPiece->color);
}

void CanJumpBackwardsThenForwards() {
	Board board;
	initialize(&board);
	Coordinate blackLocation = COORD(2,4);

	Piece *blackPiece = getPieceAt(&board, blackLocation);
	makeKingPiece(blackPiece, BLACK);
	makeKingPiece(getPieceAt(&board, COORD(1,1)),RED);
	makeKingPiece(getPieceAt(&board, COORD(1,3)),RED);

	Moves moves = blackPiece->getJumpMoves(&board, blackLocation, blackPiece);
	ASSERT_EQ_INT(1, moves.count);
	EXECUTE_FIRST(moves);

	ASSERT_NO_PIECES_FOR_COLOR(board,RED);
	ASSERT_NO_PIECE(board,1,1);
	ASSERT_NO_PIECE(board,1,3);
	ASSERT_NO_PIECE(board,2,4);

	blackPiece = getPieceAt(&board, COORD(2,0));
	ASSERT_EQ_INT(BLACK, blackPiece->color);
}

int runKingPieceTests() {
	START_TESTS(KingPieces);
	TEST(KingsCanMoveForwardAndBackwards);
	TEST(CannotJumpWhenBlocked);
	TEST(CanJumpForwardOnce);
	TEST(CanJumpBackwardsOnce);
	TEST(CanJumpForwardThenBackwards);
	TEST(CanJumpBackwardsThenForwards);
	END_TESTS;
}

