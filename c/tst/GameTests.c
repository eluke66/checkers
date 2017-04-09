/*
 * GameTests.c
 *
 *  Created on: Apr 1, 2017
 *      Author: luke
 */

#include <stdio.h>
#include "Game.h"
#include "Board.h"
#include "TestUtils.h"

void eachPlayerStartsWith12Pieces() {
	Board board;
	putPiecesOnTheBoard(&board);

	PieceList piecesForBlack = getPiecesForColor(&board, BLACK);
	ASSERT_EQ_INT(12, piecesForBlack.count);

	PieceList piecesForRed = getPiecesForColor(&board, RED);
	ASSERT_EQ_INT(12, piecesForRed.count);
}

void closestLeftSquareToEachPlayerStartsWithAPiece() {
	Board board;
	putPiecesOnTheBoard(&board);

	ASSERT_PRESENT(getPieceAt(&board,COORD(0,0)));
	ASSERT_PRESENT(getPieceAt(&board,COORD(BOARD_SIZE-1,BOARD_SIZE-1)));
}

void boardIs8x8() {
	ASSERT_EQ_INT(8, BOARD_SIZE);
}

int firstPlayer=-1;

Move blackMovesFirst_selectMove1(Moves moves, Board *board) {
	if (firstPlayer == -1) {firstPlayer = 1;}
	return moves.moves[0];
}
Move blackMovesFirst_selectMove2(Moves moves, Board *board) {
	if (firstPlayer == -1) {firstPlayer = 2;}
	return moves.moves[0];
}

void blackMovesFirst() {
	firstPlayer=-1;
	player_t player1 = (player_t){BLACK, &blackMovesFirst_selectMove1};
	player_t player2 = (player_t){BLACK, &blackMovesFirst_selectMove2};
	play(player1, player2);

	ASSERT_EQ_INT(1, firstPlayer);
}

int playerMoves=-1;

Move redMovesAfterBlack_selectMove1(Moves moves, Board *board) {
	if (playerMoves == -1) {playerMoves = 1;}
	else if (playerMoves == 1) { playerMoves = -2; }
	return moves.moves[0];
}
Move redMovesAfterBlack_selectMove2(Moves moves, Board *board) {
	if (playerMoves == 1) {playerMoves = 2;}
	return moves.moves[0];
}

void redMovesAfterBlack() {
	playerMoves=-1;
	player_t player1 = (player_t){BLACK, &redMovesAfterBlack_selectMove1};
	player_t player2 = (player_t){BLACK, &redMovesAfterBlack_selectMove2};
	play(player1, player2);

	ASSERT_EQ_INT(2, playerMoves);
}

int runGameTests() {
	START_TESTS(Game);
	TEST(eachPlayerStartsWith12Pieces);
	TEST(closestLeftSquareToEachPlayerStartsWithAPiece);
	TEST(boardIs8x8);

	TEST(blackMovesFirst);
	TEST(redMovesAfterBlack);
	END_TESTS;
}
