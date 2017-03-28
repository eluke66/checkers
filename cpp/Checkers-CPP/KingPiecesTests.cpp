/*
 * KingPiecesTests.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: luke
 */

#include "Tests.h"
#include "KingPiece.h"

class KingPieces : public ::testing::Test {
protected:
	virtual void SetUp() {
		blackPiece = new KingPiece(Color::Black);
	}

	KingPiece * redPiece() {
		return new KingPiece(Color::Red);
	}
	Board board;
	KingPiece *blackPiece;
};

TEST_F(KingPieces, KingsCanMoveForwardAndBackwards) {
	Coordinate blackLocation(2, 2);
	board.placePieceAt(blackPiece, blackLocation);
	Moves moves = blackPiece->getSimpleMoves(board, blackLocation);
	ASSERT_EQ(4, moves.size());

	for (Moves::iterator it = moves.begin(); it != moves.end(); ++it) {
		MoveType move = *it;
		Coordinate dest = move->getTo();
		ASSERT_TRUE(dest == Coordinate(1,1) || dest == Coordinate(1,3) || dest == Coordinate(3,1) || dest == Coordinate(3,3));
	}
}


TEST_F(KingPieces, CannotJumpWhenBlocked) {
	Coordinate blackLocation(0,0);
	board.placePieceAt(blackPiece, blackLocation);
	board.placePieceAt(redPiece(), Coordinate(1,1));
	board.placePieceAt(redPiece(), Coordinate(2,2));

	Moves moves = blackPiece->getJumpMoves(board, blackLocation);
	ASSERT_EMPTY(moves);
}

TEST_F(KingPieces, CanJumpForwardOnce) {
	Coordinate blackLocation(0,0);
	board.placePieceAt(blackPiece, blackLocation);
	board.placePieceAt(redPiece(), Coordinate(1,1));

	Moves moves = blackPiece->getJumpMoves(board, blackLocation);
	ASSERT_EQ(1, moves.size());

	EXECUTE_FIRST_MOVE(moves);

	ASSERT_EMPTY(board.getPiecesForColor(Color::Red));
	ASSERT_NULL(board.getPieceAt(Coordinate(1,1)));
	ASSERT_NULL(board.getPieceAt(blackLocation));

	const Piece *piece = board.getPieceAt(Coordinate(2,2));
	ASSERT_PRESENT(piece);
	ASSERT_EQ(Color::Black, piece->getColor());
}

TEST_F(KingPieces, CanJumpBackwardsOnce) {
	Coordinate blackLocation(2,2);
	board.placePieceAt(blackPiece, blackLocation);
	board.placePieceAt(redPiece(), Coordinate(1,1));

	Moves moves = blackPiece->getJumpMoves(board, blackLocation);
	ASSERT_EQ(1, moves.size());

	EXECUTE_FIRST_MOVE(moves);

	ASSERT_EMPTY(board.getPiecesForColor(Color::Red));
	ASSERT_NULL(board.getPieceAt(Coordinate(1,1)));
	ASSERT_NULL(board.getPieceAt(blackLocation));

	const Piece *piece = board.getPieceAt(Coordinate(0,0));
	ASSERT_PRESENT(piece);
	ASSERT_EQ(Color::Black, piece->getColor());
}

TEST_F(KingPieces, CanJumpForwardThenBackwards) {
	Coordinate blackLocation(2,0);
	board.placePieceAt(blackPiece, blackLocation);
	board.placePieceAt(redPiece(), Coordinate(1,1));
	board.placePieceAt(redPiece(), Coordinate(1,3));

	Moves moves = blackPiece->getJumpMoves(board, blackLocation);
	ASSERT_EQ(1, moves.size());

	EXECUTE_FIRST_MOVE(moves);

	ASSERT_EMPTY(board.getPiecesForColor(Color::Red));
	ASSERT_NULL(board.getPieceAt(Coordinate(1,1)));
	ASSERT_NULL(board.getPieceAt(blackLocation));

	const Piece *piece = board.getPieceAt(Coordinate(2,4));
	ASSERT_PRESENT(piece);
	ASSERT_EQ(Color::Black, piece->getColor());
}


TEST_F(KingPieces, CanJumpBackwardsThenForwards) {
	Coordinate blackLocation(2,4);
	board.placePieceAt(blackPiece, blackLocation);
	board.placePieceAt(redPiece(), Coordinate(1,1));
	board.placePieceAt(redPiece(), Coordinate(1,3));

	Moves moves = blackPiece->getJumpMoves(board, blackLocation);
	ASSERT_EQ(1, moves.size());

	EXECUTE_FIRST_MOVE(moves);

	ASSERT_EMPTY(board.getPiecesForColor(Color::Red));
	ASSERT_NULL(board.getPieceAt(Coordinate(1,1)));
	ASSERT_NULL(board.getPieceAt(blackLocation));

	const Piece *piece = board.getPieceAt(Coordinate(2,0));
	ASSERT_PRESENT(piece);
	ASSERT_EQ(Color::Black, piece->getColor());
}
