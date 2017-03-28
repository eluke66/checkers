/*
 * Move.h
 *
 *  Created on: Mar 23, 2017
 *      Author: luke
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "Coordinate.h"
#include "CheckerTypes.h"

class Piece;
class Board;

class Move {
public:
	Move(Board &board, const Piece *piece, const Coordinate &from, const Coordinate &to) :
		board(board), piece(piece), from(from), to(to) {}
	virtual ~Move() {}

	static Move* simpleMove(Board &board, const Piece *piece, const Coordinate &from, const Coordinate &to);
	static Move* jumpMove(Board &board, const Piece *piece, const Coordinate &from, const Coordinate &to);
	static Move* multiJumpMove(Board &board, const Piece *piece, const Coordinate &from, const Coordinate &to, Move* previousMove);

	virtual void execute() = 0;
	virtual void unExecute() = 0;

	const Coordinate& getFrom() const {
		return from;
	}

	const Coordinate& getTo() const {
		return to;
	}
	virtual std::string toString() const = 0;

protected:
	Board &board;
	const Piece *piece;
	const Coordinate from;
	const Coordinate to;

	void moveAndKingPiece(const Piece *piece, Board &board, const Coordinate &to);
};

class SimpleMove : public Move {
public:
	SimpleMove(Board &board, const Piece *piece, const Coordinate &from, const Coordinate &to) :
		Move(board,piece,from,to) {}

	virtual void execute();
	virtual void unExecute();
	virtual std::string toString() const;
};

class JumpMove : public Move {
public:
	JumpMove(Board &board, const Piece *piece, const Coordinate &from, const Coordinate &to, const Coordinate& existingPieceLocation) :
		Move(board,piece,from,to), existingPieceLocation(existingPieceLocation), removedPiece(nullptr) {}

	virtual void execute();
	virtual void unExecute();
	virtual std::string toString() const;
private:
	const Coordinate existingPieceLocation;
	const Piece *removedPiece;
};

class MultiJumpMove : public JumpMove {
public:
	MultiJumpMove(Board &board, const Piece *piece, const Coordinate &from, const Coordinate &to, const Coordinate& existingPieceLocation, MoveType previousMove) :
		JumpMove(board,piece,from,to,existingPieceLocation), previousMove(previousMove) {}

	virtual void execute();
	virtual void unExecute();
	virtual std::string toString() const;
private:
	MoveType previousMove;
};
#endif /* MOVE_H_ */
