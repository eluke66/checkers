/*
 * Piece.h
 *
 *  Created on: Mar 21, 2017
 *      Author: luke
 */

#ifndef PIECE_H_
#define PIECE_H_

#include <list>

#include "Color.h"
#include "CheckerTypes.h"

class Board;
class Coordinate;

class Piece {
public:
	Piece(Color color) : color(color) {}
	virtual ~Piece() {}
	Color getColor() const { return color; }

	virtual bool canBeKinged() const = 0;

	virtual Moves getSimpleMoves(Board &board, const Coordinate &coordinate) const = 0;
	virtual Moves getJumpMoves(Board &board, const Coordinate &coordinate) const = 0;

	class CoordinateProducer {
	public:
		virtual std::list<Coordinate> makeCoordinates(const Coordinate &coordinate) = 0;
	};
private:
	Color color;
};


#endif /* PIECE_H_ */
