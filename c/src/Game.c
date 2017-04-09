/*
 * Game.c
 *
 *  Created on: Mar 29, 2017
 *      Author: luke
 */

#include "Game.h"
#include "Piece.h"
#include "MoveRules.h"

#include <stdio.h>
void putPiecesOnTheBoard(Board *board);
int playerHasValidMoves(Moves moves);
int otherPlayer(int whichPlayer);

player_t play(player_t player1, player_t player2) {
	Board board;
	putPiecesOnTheBoard(&board);

	player_t players[2] = {player1, player2};

	int whichPlayer = 0;
	int whichTurn = 0;
	whichTurn = 0;
	while (1) {
		player_t currentPlayer = players[whichPlayer];
		color_t color = currentPlayer.color;

		//turnSignal(PlayerTurn(whichTurn, currentPlayer, board, color));

		Moves moves = getMovesForColor(color, &board);
		if (!playerHasValidMoves(moves)) {
			break;
		}
		Move move = currentPlayer.selectMove(moves, &board);

		move.execute(&move);

		whichPlayer = otherPlayer(whichPlayer);
		whichTurn++;
	}

	player_t winningPlayer = players[otherPlayer(whichPlayer)];
	//endSignal(GameFinished(whichTurn, winningPlayer));
	return winningPlayer;
}

void putPiecesOnTheBoard(Board *board) {
	initialize(board);
	const int NUM_PIECES_PER_PLAYER = 12;

	int piecesPerRow = BOARD_SIZE/2;
	int rows = NUM_PIECES_PER_PLAYER / piecesPerRow;

	for (unsigned row = 0; row < rows; row++ ) {
		for (unsigned col = (row % 2 == 0)?0 : 1; col < BOARD_SIZE; col+=2) {
			makeSinglePiece(&board->pieces[row][col], BLACK, FORWARD);
		}
	}

	for (int row = 0; row < rows; row++ ) {
		int thisRow = BOARD_SIZE - row - 1;
		for (int col = (thisRow % 2 == 0)?0 : 1; col < BOARD_SIZE; col+=2) {
			makeSinglePiece(&board->pieces[thisRow][col], RED, BACKWARDS);
		}
	}
}

int playerHasValidMoves(Moves moves) {
	return moves.count > 0;
}

int otherPlayer(int player) {
	return (player+1) % 2;
}
