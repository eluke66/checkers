/*
 * Board.h
 *
 *  Created on: Mar 18, 2017
 *      Author: luke
 */

#include <list>
#include <string>
#include <vector>
#include <memory>

#include "Color.h"
#include "Piece.h"
#include "Coordinate.h"
#include "CheckerTypes.h"

#ifndef BOARD_H_
#define BOARD_H_

class Move;

class Board {
public:
	Board();
	Board(int size);
	virtual ~Board();

	class PlacedPiece {
	public:
		PlacedPiece(const Piece *piece, const Coordinate &coordinate) :
			piece(piece), coordinate(coordinate) {
		}
		PlacedPiece(const PlacedPiece &other) :
			piece(other.piece), coordinate(other.coordinate) {
		}

		Moves getSimpleMoves(Board &board) {
			return piece->getSimpleMoves(board, coordinate);
		}

		Moves getJumpMoves(Board &board) {
			return piece->getJumpMoves(board, coordinate);
		}

		Coordinate const & getCoordinate() const {
			return coordinate;
		}

		Piece const *getPiece() const{
			return piece;
		}
	private:
		const Piece *piece;
		const Coordinate coordinate;
	};
	const Piece* getPieceAt(const Coordinate &coordinate) const;
	void removePieceAt(const Coordinate &coordinate);
	void placePieceAt(const Piece *piece, const Coordinate &coordinate);
	std::list<Board::PlacedPiece> getPiecesForColor(const Color &color) const;
	bool isValidPosition(const Coordinate &coordinate) const;
	int size() const;
	bool isFinalRowForPiece(const Piece *piece, const Coordinate &coordinate) const;

	std::string toString() const;

private:
	std::vector<std::vector<const Piece*>> board;
	static const int BOARD_SIZE = 8;

	bool isUsableSquare(int row, int col) const;
	static bool isEven(int val) { return val % 2 == 0; }
};

#endif /* BOARD_H_ */
