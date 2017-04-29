/*
 * MoveRules.cpp
 *
 *  Created on: Mar 22, 2017
 *      Author: luke
 */

#include "MoveRules.h"

#include <stddef.h>

#include "Board.h"
#include "Color.h"
#include "Coordinate.h"
#include "Move.h"
#include "Piece.h"

MoveRules::MoveRules() {

}

MoveRules::~MoveRules() {
}

Moves MoveRules::getSimpleMovesForCoordinates(Board& board,
		const Piece* piece, const Coordinate& coordinate,
		std::list<Coordinate> coordinates) {

	Moves moves;
	std::list<Coordinate>::const_iterator iterator;
	for (iterator = coordinates.begin(); iterator != coordinates.end(); ++iterator) {
		Coordinate c = *iterator;
		if (board.isValidPosition(c) && board.getPieceAt(c) == NULL) {
			moves.push_back(MoveType(new SimpleMove(board, piece, coordinate, c)));
		}
	}

	return moves;
}

bool MoveRules::pieceIsJumpable(Board& board, const Piece* piece,
		const Coordinate& coordinate) {
	return board.getPieceAt(coordinate) != nullptr && board.getPieceAt(coordinate)->getColor() != piece->getColor();
}

bool MoveRules::nextSpaceIsLandable(Board& board, const Piece* piece,
		const Coordinate& from, const Coordinate& to) {
	Coordinate landingSpot = Coordinate::extending(from, to);
	return isValidPosition(board, landingSpot) && board.getPieceAt(landingSpot) == nullptr;
}

bool MoveRules::isValidPosition(Board& board, const Coordinate& coordinate) {
	return board.isValidPosition(coordinate);
}

MoveType MoveRules::getJumpMove(Board& board, const Piece* piece,
		const Coordinate& from, const Coordinate& to) {
	return Move::jumpMove(board, piece, from, to);
}

MoveType MoveRules::getMultiJumpMove(Board& board, const Piece* piece,
		const Coordinate& from, const Coordinate& to, MoveType previousMove) {
	return Move::multiJumpMove(board,piece,from,to,previousMove);
}

MoveExecutor::MoveExecutor(MoveType move) : move(move) {
	move->execute();
}

MoveExecutor::~MoveExecutor() {
	move->unExecute();
}

Coordinate MoveRules::getLandingSpot(MoveType move) {
	return move->getTo();
}

Moves MoveRules::getMovesForColor(Color color, Board& board) {
	// For each piece the player owns:
	std::list<Board::PlacedPiece> pieces = board.getPiecesForColor(color);
	// Do jumps if available
	Moves moves;
	for (std::list<Board::PlacedPiece>::const_iterator it = pieces.begin(); it != pieces.end(); it++) {
		Board::PlacedPiece piece= *it;
		Moves jumps = piece.getJumpMoves(board);
		moves.insert(moves.begin(), jumps.begin(), jumps.end());
	}

	if (moves.size() > 0) {
		return moves;
	}

	// Otherwise do simple moves.
	for (std::list<Board::PlacedPiece>::const_iterator it = pieces.begin(); it != pieces.end(); it++) {
		Board::PlacedPiece piece= *it;
		Moves simpleMoves = piece.getSimpleMoves(board);
		if (simpleMoves.size() > 0) {
			moves.insert(moves.begin(), simpleMoves.begin(), simpleMoves.end());
		}
	}
	return moves;
}
