/*
 * MoveRules.h
 *
 *  Created on: Mar 22, 2017
 *      Author: luke
 */

#ifndef MOVERULES_H_
#define MOVERULES_H_

#include <list>
#include <boost/iterator/filter_iterator.hpp>
#include "Color.h"
#include "CheckerTypes.h"

class Board;
class Coordinate;
class Piece;
class Move;

class MoveRules {
public:
	MoveRules();
	virtual ~MoveRules();

	template<typename CoordinateProducer, typename PieceType>
	static Moves getSimpleMoves(Board &board, const PieceType*piece, const Coordinate &coordinate, CoordinateProducer coordProducer);


	template<typename CoordinateProducer, typename PieceType>
	static Moves getJumpMoves(Board &board, const PieceType *piece, const Coordinate &coordinate, CoordinateProducer coordProducer);

	virtual Moves getMovesForColor(Color color, Board &board);
private:
	static Moves getSimpleMovesForCoordinates(Board& board, const Piece* piece, const Coordinate& coordinate, std::list<Coordinate> Coordinates);
	static bool pieceIsJumpable(Board &board, const Piece *piece, const Coordinate &coordinate );
	static bool nextSpaceIsLandable(Board &board, const Piece *piece, const Coordinate &from, const Coordinate &to );
	static bool isValidPosition(Board &board, const Coordinate &coordinate );
	static MoveType getJumpMove(Board &board, const Piece *piece, const Coordinate &from, const Coordinate &to );
	static MoveType getMultiJumpMove(Board &board, const Piece *piece, const Coordinate &from, const Coordinate &to, MoveType previousMove);
	static Coordinate getLandingSpot(MoveType move);

	template<typename CoordinateProducer, typename PieceType>
	static void searchJumps(Moves& moves, Board &board, const PieceType *piece, Moves&finalMoves, CoordinateProducer coordProducer);
};

class MoveExecutor {
public:
	MoveExecutor(MoveType move);
	~MoveExecutor();
private:
	MoveType move;
};

template<typename CoordinateProducer, typename PieceType>
inline Moves MoveRules::getSimpleMoves(Board& board,
		const PieceType* piece, const Coordinate& coordinate,
		CoordinateProducer coordProducer) {
	return getSimpleMovesForCoordinates(board,piece,coordinate,coordProducer(piece, coordinate));
}

template<typename CoordinateProducer, typename PieceType>
inline Moves MoveRules::getJumpMoves(Board& board,
		const PieceType* piece, const Coordinate& coordinate,
		CoordinateProducer coordProducer) {

	std::list<Coordinate> coordinates = coordProducer(piece, coordinate);
	Moves initialMoves;
	std::list<Coordinate>::const_iterator iterator;
	for (iterator = coordinates.begin(); iterator != coordinates.end(); ++iterator) {
		Coordinate c = *iterator;
		if (isValidPosition(board,c) && pieceIsJumpable(board,piece,c) && nextSpaceIsLandable(board,piece,coordinate,c)) {
			initialMoves.push_back(getJumpMove(board, piece, coordinate, c));
		}
	}

	Moves finalMoves;
	searchJumps(initialMoves, board, piece, finalMoves, coordProducer);
	return finalMoves;
}

template<typename CoordinateProducer, typename PieceType>
inline void MoveRules::searchJumps(Moves& moves, Board& board,
		const PieceType* piece, Moves& finalMoves,
		CoordinateProducer coordProducer) {
	// For each move
	Moves::const_iterator iterator;
	for (iterator = moves.begin(); iterator != moves.end(); ++iterator) {
		MoveType move = *iterator;

		// Get the next jump moves.
		Moves nextMovesForThisMove;
		Coordinate landingSpot = getLandingSpot(move);

		// Let's assume we execute the move.
		{
			MoveExecutor withMove(move);

			std::list<Coordinate> coordinates = coordProducer(piece, landingSpot);
			std::list<Coordinate>::const_iterator citerator;
			for (citerator = coordinates.begin(); citerator != coordinates.end(); ++citerator) {
				Coordinate c = *citerator;

				if (isValidPosition(board,c) && pieceIsJumpable(board,piece,c) && nextSpaceIsLandable(board,piece,landingSpot,c)) {
					nextMovesForThisMove.push_back(getMultiJumpMove(board,piece,landingSpot,c,move));

				}
			}
		}

		// If there are any, then we replace this move with those moves AND THEIR CONTINUED MOVES
		if (nextMovesForThisMove.size() > 0) {
			searchJumps(nextMovesForThisMove, board, piece, finalMoves, coordProducer);
		}
		else {
			// Otherwise we don't have to jump more, and just add this move.
			finalMoves.push_back(move);
		}
	}
}

#endif /* MOVERULES_H_ */
