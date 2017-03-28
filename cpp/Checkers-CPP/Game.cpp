#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "Move.h"
#include "SinglePiece.h"

Game::Game(const Player* player1, const Player* player2,
		MoveRules& moveRules) : moveRules(moveRules){
	board = Board();
	players.resize(2);
	players[0] = player1;
	players[1] = player2;
	colorsPerPlayer[player1] = Color::Black;
	colorsPerPlayer[player2] = Color::Red;
}
void freeMoves(Moves moves) {
	Moves::iterator it;
	for (it = moves.begin(); it != moves.end(); it++) {
		delete *it;
	}
}
const Player* Game::play() {
	putPiecesOnTheBoard(board);

	int whichPlayer = 0;
	int whichTurn = 0;

	while (true) {
		const Player* currentPlayer = players[whichPlayer];
		Color color = colorsPerPlayer[currentPlayer];

		turnSignal(PlayerTurn(whichTurn, currentPlayer, board, color));

		Moves moves = moveRules.getMovesForColor(color, board);
		if (!playerHasValidMoves(moves)) {
			break;
		}
		MoveType move = currentPlayer->selectMove(moves, board);
		move->execute();

		freeMoves(moves);
		whichPlayer = otherPlayer(whichPlayer);
		whichTurn++;
	}

	const Player *winningPlayer = players[otherPlayer(whichPlayer)];
	endSignal(GameFinished(whichTurn, winningPlayer));

	return winningPlayer;
}

void Game::putPiecesOnTheBoard(Board& board) {
	const int NUM_PIECES_PER_PLAYER = 12;

	int piecesPerRow = board.size()/2;
	int rows = NUM_PIECES_PER_PLAYER / piecesPerRow;
	if (piecesPerRow * rows != NUM_PIECES_PER_PLAYER) {
		throw new std::runtime_error("Cannot fit 12 pieces onto a board");
	}

	for (int row = 0; row < rows; row++ ) {
		for (int col = (row % 2 == 0)?0 : 1; col < board.size(); col+=2) {
			Piece *piece = new SinglePiece(Color::Black, SinglePiece::FORWARD);
			board.placePieceAt(piece, Coordinate(row,col));
		}
	}

	for (int row = 0; row < rows; row++ ) {
		int thisRow = board.size() - row - 1;
		for (int col = (thisRow % 2 == 0)?0 : 1; col < board.size(); col+=2) {
			Piece *piece = new SinglePiece(Color::Red, SinglePiece::REVERSE);
			board.placePieceAt(piece, Coordinate(thisRow, col));
		}
	}
}
