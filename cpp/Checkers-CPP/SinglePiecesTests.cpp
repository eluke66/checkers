/*
 * SinglePiecesTests.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: luke
 */

#include "Tests.h"
#include "SinglePiece.h"

class SinglePieces : public ::testing::Test {
protected:
	virtual void SetUp() {
		blackPiece = new SinglePiece(Color::Black, SinglePiece::FORWARD);
	}

	SinglePiece * redPiece() {
		return new SinglePiece(Color::Red, SinglePiece::REVERSE);
	}
	Board board;
	SinglePiece *blackPiece;
};

TEST_F(SinglePieces, HaveTwoForwardMoves) {
	Coordinate blackLocation(0, 2);
	board.placePieceAt(blackPiece, blackLocation);
	Moves moves = blackPiece->getSimpleMoves(board, blackLocation);
	ASSERT_EQ(2, moves.size());

	for (Moves::iterator it = moves.begin(); it != moves.end(); ++it) {
		MoveType move = *it;
		ASSERT_EQ(1, move->getTo().getRow());
		ASSERT_TRUE(move->getTo().getCol() == 1 || move->getTo().getCol() == 3);
		ASSERT_EQ(blackLocation, move->getFrom());
	}

	SinglePiece *red = redPiece();
	Coordinate redLocation(4, 2);
	board.placePieceAt(red, redLocation);
	moves = red->getSimpleMoves(board, redLocation);
	ASSERT_EQ(2, moves.size());

	for (Moves::iterator it = moves.begin(); it != moves.end(); ++it) {
		MoveType move = *it;
		ASSERT_EQ(3, move->getTo().getRow());
		ASSERT_TRUE(move->getTo().getCol() == 1 || move->getTo().getCol() == 3);
		ASSERT_EQ(redLocation, move->getFrom());
	}

}

TEST_F(SinglePieces, CannotJumpWhenBlocked) {
	Coordinate blackLocation(0,0);
	board.placePieceAt(blackPiece, blackLocation);
	board.placePieceAt(redPiece(), Coordinate(1,1));
	board.placePieceAt(redPiece(), Coordinate(2,2));

	Moves moves = blackPiece->getJumpMoves(board, blackLocation);
	ASSERT_EMPTY(moves);
}

TEST_F(SinglePieces, CannotJumpOwnMan) {
	Coordinate blackLocation(0,0);
	board.placePieceAt(blackPiece, blackLocation);
	board.placePieceAt(new SinglePiece(Color::Black, SinglePiece::FORWARD), Coordinate(1,1));

	Moves moves = blackPiece->getJumpMoves(board, blackLocation);
	ASSERT_EMPTY(moves);
}


TEST_F(SinglePieces, CannotJumpOffTheBoardOrWhenBlocked) {
	Coordinate blackLocation(0,0);
	board.placePieceAt(blackPiece, blackLocation);
	board.placePieceAt(redPiece(), Coordinate(1,1));

	Moves moves = blackPiece->getSimpleMoves(board, blackLocation);
	ASSERT_EMPTY(moves);

}

TEST_F(SinglePieces, CanJumpMoreThanOnceAndThosePiecesAreRemoved) {
	Piece *red1 = redPiece();
	Piece *red2 = redPiece();
	Coordinate blackLocation(0,0);
	board.placePieceAt(blackPiece, blackLocation);
	board.placePieceAt(red1, Coordinate(1,1));
	board.placePieceAt(red2, Coordinate(3,3));

	Moves moves = blackPiece->getJumpMoves(board, blackLocation);
	ASSERT_EQ(1, moves.size());

	EXECUTE_FIRST_MOVE(moves);

	ASSERT_EMPTY(board.getPiecesForColor(Color::Red));
	ASSERT_NULL(board.getPieceAt(Coordinate(1,1)));
	ASSERT_NULL(board.getPieceAt(blackLocation));

	const Piece *piece = board.getPieceAt(Coordinate(4,4));
	ASSERT_PRESENT(piece);
	ASSERT_EQ(Color::Black, piece->getColor());
}

TEST_F(SinglePieces, CanHaveTwoForwardSingleJumps) {
	Piece *red1 = redPiece();
	Piece *red2 = redPiece();
	Coordinate blackLocation(0,2);
	board.placePieceAt(blackPiece, blackLocation);
	board.placePieceAt(red1, Coordinate(1,1));
	board.placePieceAt(red2, Coordinate(1,3));

	Moves moves = blackPiece->getJumpMoves(board, blackLocation);
	ASSERT_EQ(2, moves.size());

	for (Moves::iterator it = moves.begin(); it != moves.end(); ++it) {
		MoveType move = *it;
		ASSERT_EQ(2, move->getTo().getRow());
		ASSERT_TRUE(move->getTo().getCol() == 0 || move->getTo().getCol() == 4);
		ASSERT_EQ(blackLocation, move->getFrom());
	}
}

TEST_F(SinglePieces, CanHaveMultipleForwardMultiJumps) {
	Piece *redPiece1 = redPiece();
	Piece *redPiece2 = redPiece();
	Piece *redPiece3 = redPiece();
	Coordinate blackLocation(0,2);
	board.placePieceAt(blackPiece, blackLocation);
	board.placePieceAt(redPiece1, Coordinate(1,1));
	board.placePieceAt(redPiece2, Coordinate(1,3));
	board.placePieceAt(redPiece3, Coordinate(3,5));

	Moves moves = blackPiece->getJumpMoves(board, blackLocation);
	ASSERT_EQ(2, moves.size());

	for (Moves::iterator it = moves.begin(); it != moves.end(); ++it) {
		MoveType move = *it;
		ASSERT_TRUE(move->getTo() == Coordinate(2,0) || move->getTo() == Coordinate(4,6));
	}
}

TEST_F(SinglePieces, WhenJumpsIntoTheBackRowItIsKinged) {
	Coordinate blackLocation(board.size()-3, 1);
	board.placePieceAt(blackPiece, blackLocation);
	board.placePieceAt(redPiece(), Coordinate(board.size()-2,2));

	Moves moves = blackPiece->getJumpMoves(board, blackLocation);
	ASSERT_EQ(1, moves.size());

	EXECUTE_FIRST_MOVE(moves);

	const Piece *piece = board.getPieceAt(Coordinate(board.size()-1, 3));
	ASSERT_PRESENT(piece);
	ASSERT_EQ(Color::Black, piece->getColor());
	ASSERT_FALSE(piece->canBeKinged());
}

TEST_F(SinglePieces, CanJumpOnceAndThatPieceIsRemoved) {
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


TEST_F(SinglePieces, WhenMoveIntoTheBackRowItIsKinged) {
	Coordinate blackLocation(board.size()-2, 0);
	board.placePieceAt(blackPiece, blackLocation);
	Moves moves = blackPiece->getSimpleMoves(board, blackLocation);
	ASSERT_EQ(1, moves.size());

	EXECUTE_FIRST_MOVE(moves);

	const Piece *piece = board.getPieceAt(Coordinate(board.size()-1, 1));
	ASSERT_PRESENT(piece);
	ASSERT_EQ(Color::Black, piece->getColor());
	ASSERT_FALSE(piece->canBeKinged());
}


