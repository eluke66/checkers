/*
 * KingPiecesTests.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: luke
 */

#include "Tests.h"
#define private public
#include "Game.h"
#undef private
#include "MoveRules.h"
#include "SinglePiece.h"
#include "Player.h"

class GameTests : public ::testing::Test {
protected:
	Piece * redPiece() {
		return new SinglePiece(Color::Red, SinglePiece::REVERSE);
	}
	Piece * blackPiece() {
		return new SinglePiece(Color::Black, SinglePiece::FORWARD);
	}
	Board board;
};

TEST_F(GameTests, eachPlayerStartsWith12Pieces) {
	Game::putPiecesOnTheBoard(board);

	auto piecesForBlack = board.getPiecesForColor(Color::Black);
	ASSERT_EQ(12, piecesForBlack.size());

	auto piecesForRed = board.getPiecesForColor(Color::Red);
	ASSERT_EQ(12, piecesForBlack.size());
}

TEST_F(GameTests, closestLeftSquareToEachPlayerStartsWithAPiece) {
	Game::putPiecesOnTheBoard(board);

	ASSERT_PRESENT(board.getPieceAt(Coordinate(0,0)));
	ASSERT_PRESENT(board.getPieceAt(Coordinate(board.size()-1,board.size()-1)));
}

TEST_F(GameTests, boardIs8x8) {
	ASSERT_EQ(8, board.size());
}

class StubPlayer : public Player {
public:
	StubPlayer(Move * moveToSelect) : move(moveToSelect) {}
	virtual Move * selectMove(std::list<Move *> &moves, Board &board) const {
		return move;
	}
private:
	Move * move;
};

class StubMoveRules1 : public MoveRules {
public:
	bool isOkay = false;

	std::list<Move*> getMovesForColor(Color color, Board& board) {
		if (color == Color::Black) { isOkay = true; }
		return std::list<Move *>();
	}
};

TEST_F(GameTests, blackMovesFirst) {
	StubPlayer * player1 = new StubPlayer(nullptr);
	StubPlayer * player2 = new StubPlayer(nullptr);
	StubMoveRules1 * moveRules = new StubMoveRules1();
	Game game(player1, player2, *moveRules);

	game.play();

	ASSERT_TRUE(moveRules->isOkay);
}

class StubMoveRules2: public MoveRules {
public:
	StubMoveRules2(Move *move) : move(move) {}
	int calls = 0;

	std::list<Move*> getMovesForColor(Color color, Board& board) {
		calls++;
		std::list<Move *> returnValue;
		if (color == Color::Black) {
			returnValue.push_back(move);
		}
		return returnValue;
	}
private:
	Move * move;
};

TEST_F(GameTests, redMovesAfterBlack) {
	Move * move = Move::simpleMove(board, new SinglePiece(Color::Black, SinglePiece::FORWARD), Coordinate(2,0), Coordinate(3,1));
	StubPlayer * player1 = new StubPlayer(move);
	StubPlayer * player2 = new StubPlayer(nullptr);
	StubMoveRules2 * moveRules = new StubMoveRules2(move);
	Game game(player1, player2, *moveRules);

	const Player *winner = game.play();

	ASSERT_EQ(2, moveRules->calls);
	ASSERT_EQ(player1, winner);
}

TEST_F(GameTests, whenAPlayerCannotMoveThenOtherPlayerWins) {
	StubPlayer * player1 = new StubPlayer(nullptr);
	StubPlayer * player2 = new StubPlayer(nullptr);
	StubMoveRules1 * moveRules = new StubMoveRules1();
	Game game(player1, player2, *moveRules);

	const Player *winner = game.play();

	ASSERT_EQ(player2, winner);
}
