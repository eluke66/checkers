/*
 * SinglePiece.h
 *
 *  Created on: Mar 22, 2017
 *      Author: luke
 */

#ifndef SINGLEPIECE_H_
#define SINGLEPIECE_H_

#include "Piece.h"

class SinglePiece : public Piece {
public:
	static const int FORWARD = 1;
	static const int REVERSE = -1;
	SinglePiece(Color color, int direction);
	virtual ~SinglePiece();


	bool canBeKinged() const { return true; }
	std::list<Move *> getSimpleMoves(Board &board, const Coordinate &coordinate) const;
	std::list<Move *> getJumpMoves(Board &board, const Coordinate &coordinate) const;

private:
	const int direction;

	std::list<Coordinate> getCoordinates(const Coordinate &coordinate) const;
};

#endif /* SINGLEPIECE_H_ */
