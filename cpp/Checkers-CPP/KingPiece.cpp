/*
 * KingPiece.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: luke
 */

#include <functional>
#include "KingPiece.h"
#include "Coordinate.h"
#include "MoveRules.h"

std::list<Move*> KingPiece::getSimpleMoves(Board& board,
		const Coordinate& coordinate) const {

	return MoveRules::getSimpleMoves(board, this, coordinate, std::mem_fn (&KingPiece::getCoordinates));
}

std::list<Move*> KingPiece::getJumpMoves(Board& board,
		const Coordinate& coordinate) const {
	return MoveRules::getJumpMoves(board, this, coordinate, std::mem_fn (&KingPiece::getCoordinates));
}


std::list<Coordinate> KingPiece::getCoordinates(
		const Coordinate& coordinate) const {
	std::list<Coordinate> coords;

	int row = coordinate.getRow();
	coords.push_back(Coordinate(row+1, coordinate.getCol()+1));
	coords.push_back(Coordinate(row+1, coordinate.getCol()-1));
	coords.push_back(Coordinate(row-1, coordinate.getCol()+1));
	coords.push_back(Coordinate(row-1, coordinate.getCol()-1));
	return coords;
}
