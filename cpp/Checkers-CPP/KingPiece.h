/*
 * KingPiece.h
 *
 *  Created on: Mar 25, 2017
 *      Author: luke
 */

#ifndef KINGPIECE_H_
#define KINGPIECE_H_

#include "Piece.h"

class KingPiece: public Piece {
public:
	KingPiece(const Piece *piece) : Piece(piece->getColor()) {}
	KingPiece(Color color) : Piece(color) {}
	virtual ~KingPiece() {}

	virtual bool canBeKinged() const { return false; }
	virtual std::list<Move *> getSimpleMoves(Board &board, const Coordinate &coordinate) const;
	virtual std::list<Move *> getJumpMoves(Board &board, const Coordinate &coordinate) const;
private:
	std::list<Coordinate> getCoordinates(const Coordinate &coordinate) const;
};

#endif /* KINGPIECE_H_ */
