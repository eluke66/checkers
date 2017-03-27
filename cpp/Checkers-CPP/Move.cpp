#include <exception>
#include "Move.h"
#include "Board.h"
#include "KingPiece.h"


void
Move::moveAndKingPiece(const Piece *piece, Board &board, const Coordinate &to) {
	board.placePieceAt(piece, to);
	if (board.isFinalRowForPiece(piece, to) && piece->canBeKinged()) {
		board.placePieceAt(new KingPiece(piece), to);
	}
}

Move* Move::simpleMove(Board &board, const Piece *piece, const Coordinate &from, const Coordinate &to) {
	return new SimpleMove(board, piece, from, to);
}

Move* Move::jumpMove(Board& board, const Piece* piece, const Coordinate& from,
		const Coordinate& to) {
	return new JumpMove(board, piece, from, Coordinate::extending(from, to), to);
}

Move* Move::multiJumpMove(Board& board, const Piece* piece,
		const Coordinate& from, const Coordinate& to,
		Move* previousMove) {
	return new MultiJumpMove(board, piece, from, Coordinate::extending(from, to), to, previousMove);
}

void SimpleMove::execute() {
	board.removePieceAt(from);
	moveAndKingPiece(piece, board, to);
}

void SimpleMove::unExecute() {
	board.removePieceAt(to);
	board.placePieceAt(piece, from);
}

void JumpMove::execute() {
	if (removedPiece == nullptr) {
		removedPiece = board.getPieceAt(existingPieceLocation);
		board.removePieceAt(from);
		moveAndKingPiece(piece, board, to);
		board.removePieceAt(existingPieceLocation);
	}
	else {
		throw std::runtime_error("Trying to re-execute jump move");
	}
}

void JumpMove::unExecute() {
	if (removedPiece != nullptr) {
		board.removePieceAt(to);
		board.placePieceAt(piece, from);
		board.placePieceAt(removedPiece, existingPieceLocation);
		removedPiece = nullptr;
	}
	else {
		throw std::runtime_error("Trying to unExecute a not-yet-executed jump move");
	}
}

void MultiJumpMove::execute() {
	previousMove->execute();
	JumpMove::execute();
}

void MultiJumpMove::unExecute() {
	JumpMove::unExecute();
	previousMove->unExecute();
}

std::string SimpleMove::toString() const {
	std::stringstream out;
	out << piece->getColor() << " from " << (std::string)from << "->" << (std::string)to;
	return out.str();
}

std::string JumpMove::toString() const {
	std::stringstream out;
	out << piece->getColor() << " jumping from " << (std::string)from << "->" << (std::string)to;
	return out.str();
}

std::string MultiJumpMove::toString() const {
	std::stringstream out;
	out << piece->getColor() << " jumping from " << (std::string)from << "->" << (std::string)to;
	out << "  " << previousMove->toString();
	return out.str();
}
