/*
 * SinglePiece.cpp
 *
 *  Created on: Mar 22, 2017
 *      Author: luke
 */

#include <functional>
#include "Coordinate.h"
#include "SinglePiece.h"
#include "MoveRules.h"
#include "Move.h"

SinglePiece::SinglePiece(Color color, int direction) : Piece(color), direction(direction) {
}

SinglePiece::~SinglePiece() {
}

std::list<Move *> SinglePiece::getSimpleMoves(Board& board,
		const Coordinate& coordinate) const {

	return MoveRules::getSimpleMoves(board, this, coordinate, std::mem_fn (&SinglePiece::getCoordinates));
}

std::list<Move *> SinglePiece::getJumpMoves(Board& board,
		const Coordinate& coordinate) const {
	return MoveRules::getJumpMoves(board, this, coordinate, std::mem_fn (&SinglePiece::getCoordinates));
}

std::list<Coordinate> SinglePiece::getCoordinates(
		const Coordinate& coordinate) const {
	std::list<Coordinate> coords;

	int nextRow = coordinate.getRow()+direction;
	coords.push_back(Coordinate(nextRow, coordinate.getCol()+1));
	coords.push_back(Coordinate(nextRow, coordinate.getCol()-1));
	return coords;
}

