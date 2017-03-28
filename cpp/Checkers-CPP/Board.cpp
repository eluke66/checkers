/*
 * Board.cpp
 *
 *  Created on: Mar 18, 2017
 *      Author: luke
 */

#include "Board.h"

#include <sstream>
#include <stdexcept>

#define ENSURE_PIECE_IS_NOT_NULL(piece) \
		if (piece == NULL) { \
			throw std::invalid_argument("Cannot use null piece "); \
		}

#define VALIDATE_POSITION(coordinate,op) \
		if (!isValidPosition(coordinate)) { \
			throw std::invalid_argument("Cannot #op piece at " + (std::string)coordinate + " as the location is invalid"); \
		}

const Piece *NO_PIECE = NULL;

Board::Board() : Board(BOARD_SIZE) {

}

Board::Board(int size) {
	board.resize(size, std::vector<const Piece *>(size));
}

Board::~Board() {
	for (unsigned row = 0; row < board.size(); row++) {
		for (unsigned col = 0; col < board.size(); col++) {
			if (board[row][col] != NO_PIECE) {
				delete board[row][col];
			}
		}
	}
}

const Piece* Board::getPieceAt(const Coordinate& coordinate) const {
	VALIDATE_POSITION(coordinate, "get");
	return board[coordinate.getRow()][coordinate.getCol()];
}

void Board::removePieceAt(const Coordinate& coordinate) {
	VALIDATE_POSITION(coordinate, "remove");
	board[coordinate.getRow()][coordinate.getCol()] = NULL;
}

void Board::placePieceAt(const Piece* piece, const Coordinate& coordinate) {
	VALIDATE_POSITION(coordinate, "place");
	board[coordinate.getRow()][coordinate.getCol()] = piece;
}

std::list<Board::PlacedPiece> Board::getPiecesForColor(const Color& color) const {
	std::list<Board::PlacedPiece> pieces;
	for (unsigned row = 0; row < board.size(); row++) {
		for (unsigned col = 0; col < board.size(); col++) {
			if ((board[row][col] != NO_PIECE) && (board[row][col]->getColor() == color) ) {
				pieces.push_back(Board::PlacedPiece(board[row][col], Coordinate(row,col)));
			}
		}
	}
	return pieces;
}

bool Board::isValidPosition(const Coordinate& coordinate) const {
	unsigned row = coordinate.getRow();
	unsigned column = coordinate.getCol();
	return 	row < board.size() &&
			column < board[0].size() &&
			isUsableSquare(row, column);
}

bool Board::isUsableSquare(int row, int col) const {
	return (isEven(row) && isEven(col)) || (!isEven(row) && !isEven(col));
}

int Board::size() const {
	return board.size();
}

bool Board::isFinalRowForPiece(const Piece* piece,
		const Coordinate& coordinate) const {
	ENSURE_PIECE_IS_NOT_NULL(piece);
	return
			(piece->getColor() == Color::Red && coordinate.getRow() == 0) ||
			(piece->getColor() == Color::Black && coordinate.getRow() == (board.size()-1));
}

std::string Board::toString() const {
	std::stringstream out;
	out << std::endl << "  ";
	for (unsigned col = 0; col < board[0].size(); col++) {
		out << col;
	}
	out << std::endl;
	for (unsigned row = 0; row < board.size(); row++) {
		out << row << " ";
		for (unsigned col = 0; col < board[0].size(); col++) {
			if (!isUsableSquare(row,col)) {
				out << "|";
			}
			else {
				const Piece *p = board[row][col];
				if (p == NO_PIECE) { out << '_'; }
				else if (p->getColor() == Color::Black) {
					if (p->canBeKinged()) { out << "b"; }
					else { out << "B"; }
				}
				else {
					if (p->canBeKinged()) { out << "r"; }
					else { out << "R"; }
				}
			}
		}
		out << std::endl;
	}
	return out.str();
}
