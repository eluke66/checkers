package com.eluke.checkers

import com.eluke.checkers.Board.PlacedPiece

class MoveRules {

	public static Collection<Move> getSimpleMoves(Board board, Piece piece, Coordinate coordinate, Closure coordinateProducer) {
		return coordinateProducer.call(coordinate)
			.findAll { c -> board.isValidPosition(c) }
			.findAll { c -> !board.getPieceAt(c).isPresent() }
			.collect { c -> Move.simpleMove(board, piece, coordinate, c) }
	}

	public static Collection<Move> getJumpMoves(Board board, Piece piece, Coordinate coordinate, Closure coordinateProducer) {
		def initialMoves = coordinateProducer.call(coordinate)
		.findAll { c-> board.isValidPosition(c) }
		.findAll { c-> isValidCoordinate(board,c) }
		.findAll { c-> pieceIsJumpable(board, piece, c) }
		.findAll { c-> nextSpaceIsLandable(board, piece, coordinate, c) }
		.collect { c-> Move.jumpMove(board, piece, coordinate, c) }

		def finalMoves = []
		searchJumps(initialMoves, board, piece, finalMoves, coordinateProducer)
		return finalMoves
	}

	private static boolean isValidCoordinate(Board board, Coordinate coordinate) {
		return board.isValidPosition(coordinate)
	}
	private static boolean pieceIsJumpable(Board board, Piece piece, Coordinate coordinate ) {
		return board.getPieceAt(coordinate).isPresent() && board.getPieceAt(coordinate).get().color != piece.color
	}
	private static boolean nextSpaceIsLandable(Board board, Piece piece, Coordinate origin, Coordinate coordinate ) {
		Coordinate landingSpot = Coordinate.extending(origin, coordinate)
		return isValidCoordinate(board, landingSpot) && !board.getPieceAt(landingSpot).isPresent()
	}

	private static void searchJumps(List moves, Board board, Piece piece, List finalMoves, Closure coordinateProducer) {
		moves.each { move ->
			move.execute()

			def coordinate = move.getNextPosition()
			def nextMovesForThisMove =
				coordinateProducer.call(coordinate)
				.findAll { c-> isValidCoordinate(board,c) }
				.findAll { c-> pieceIsJumpable(board, piece, c) }
				.findAll { c-> nextSpaceIsLandable(board, piece, coordinate, c) }
				.collect { c-> Move.multiJumpMove(board, piece, coordinate, c, move) }

			move.unExecute()

			if (!nextMovesForThisMove.isEmpty()) {
				searchJumps(nextMovesForThisMove, board, piece, finalMoves, coordinateProducer)
			}
			else {
				// Otherwise we don't have to jump more, and just add this move.
				finalMoves.add(move)
			}
		}
	}

	public Collection<Move> getMovesForColor(Color color, Board board) {

		// For each piece the player owns:
		Collection<PlacedPiece> pieces = board.getPiecesForColor(color)

		def moves = pieces.collect { p-> p.getJumpMoves(board, p.coordinate) }.flatten()

		if (!moves.isEmpty()) {
			return moves
		}

		return pieces.collect { p-> p.getSimpleMoves(board, p.coordinate) }.flatten()
	}

}
