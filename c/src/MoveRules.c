/*
 * MoveRules.c
 *
 *  Created on: Apr 5, 2017
 *      Author: luke
 */

#include "Board.h"
#include "Move.h"
#include "MoveRules.h"
#include <stdlib.h>
#include <stdio.h>

void addMoves(Moves *from, Moves *to) {
	for (int i = 0; i < from->count; i++) {
		to->moves[i+to->count] = from->moves[i];
	}
	to->count += from->count;
}

Moves getMovesForColor(color_t color, Board *board) {
	PieceList pieces = getPiecesForColor(board, color);

	// Do jumps if available

	// TODO: This moves variable here gets overwritten in game 119 move 18/19.
	Moves moves; moves.count = 0;
	for (int i = 0; i < pieces.count; i++) {
		PlacedPiece placedPiece = pieces.pieces[i];

		Moves jumps = placedPiece.piece.getJumpMoves(board, placedPiece.coordinate, &placedPiece.piece);

		addMoves(&jumps, &moves);

	}

	if (moves.count > 0) {
		return moves;
	}

	// Otherwise do simple moves.
	Moves simpleMoves; simpleMoves.count = 0;
	for (int i = 0; i < pieces.count; i++) {
		PlacedPiece placedPiece = pieces.pieces[i];
		Moves simple = placedPiece.piece.getSimpleMoves(board, placedPiece.coordinate, &placedPiece.piece);
		addMoves(&simple, &simpleMoves);
	}
	return simpleMoves;
}
