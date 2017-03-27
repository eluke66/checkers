/*
 * KingPiecesTests.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: luke
 */

#include "Tests.h"
#include "MoveRules.h"
#include "SinglePiece.h"

class MoveRulesTests : public ::testing::Test {
protected:
	Piece * redPiece() {
		return new SinglePiece(Color::Red, SinglePiece::REVERSE);
	}
	Piece * blackPiece() {
		return new SinglePiece(Color::Black, SinglePiece::FORWARD);
	}
	Board board;
	MoveRules rules;
};

TEST_F(MoveRulesTests, ifCapturingMovesAreAvailableTheyMustBePickedForSimple) {
	board.placePieceAt(blackPiece(), Coordinate(0,2));
	board.placePieceAt(redPiece(), Coordinate(1,1));
	std::list<Move *> moves = rules.getMovesForColor(Color::Black, board);
	ASSERT_EQ(1, moves.size());

	Move *move = *(moves.begin());
	move->execute();

	ASSERT_EMPTY(board.getPiecesForColor(Color::Red));
}

TEST_F(MoveRulesTests, ifCapturingMovesAreAvailableTheyMustBePickedForMultiJumps) {
	board.placePieceAt(blackPiece(), Coordinate(0,2));
	board.placePieceAt(redPiece(), Coordinate(1,3));
	board.placePieceAt(redPiece(), Coordinate(3,5));

	std::list<Move *> moves = rules.getMovesForColor(Color::Black, board);
	ASSERT_EQ(1, moves.size());

	Move *move = *(moves.begin());
	move->execute();

	ASSERT_EMPTY(board.getPiecesForColor(Color::Red));

	const Piece *piece = board.getPieceAt(Coordinate(4,6));
	ASSERT_PRESENT(piece);
	ASSERT_EQ(Color::Black, piece->getColor());
}

