package com.eluke.checkers;

import java.util.Collection;
import java.util.LinkedList;
import java.util.List;
import java.util.function.Function;
import java.util.stream.Collectors;

import com.eluke.checkers.Board.PlacedPiece;

public class MoveRules {

	public static Collection<Move> getSimpleMoves(final Board board, final Piece piece, final Coordinate coordinate, final Function<Coordinate,Collection<Coordinate>> coordinateProducer) {
		return
				coordinateProducer.apply(coordinate).stream()
				.filter(c -> board.isValidPosition(c))
				.filter(c-> !board.getPieceAt(c).isPresent())
				.map(c -> Move.simpleMove(board, piece, coordinate, c))
				.collect(Collectors.toList());
	}

	public static Collection<Move> getJumpMoves(final Board board, final Piece piece, final Coordinate coordinate, final Function<Coordinate,Collection<Coordinate>> coordinateProducer) {
		Collection<Move> initialMoves =
				coordinateProducer.apply(coordinate).stream()
				.filter(c-> isValidCoordinate(board,c))
				.filter(c-> pieceIsJumpable(board, piece, c))
				.filter(c-> nextSpaceIsLandable(board, piece, coordinate, c))
				.map(c -> Move.jumpMove(board, piece, coordinate, c))
				.collect(Collectors.toList());


		Collection<Move> finalMoves = new LinkedList<>();
		searchJumps(initialMoves, board, piece, finalMoves, coordinateProducer);
		return finalMoves;
	}

	private static boolean isValidCoordinate(final Board board, final Coordinate coordinate) {
		return board.isValidPosition(coordinate);
	}
	private static boolean pieceIsJumpable(final Board board, final Piece piece, final Coordinate coordinate ) {
		return board.getPieceAt(coordinate).isPresent() && board.getPieceAt(coordinate).get().color() != piece.color();
	}
	private static boolean nextSpaceIsLandable(final Board board, final Piece piece, final Coordinate origin, final Coordinate coordinate ) {
		Coordinate landingSpot = Coordinate.extending(origin, coordinate);
		return isValidCoordinate(board, landingSpot) && !board.getPieceAt(landingSpot).isPresent();
	}

	private static void searchJumps(final Collection<Move> moves, final Board board, final Piece piece, final Collection<Move> finalMoves, final Function<Coordinate,Collection<Coordinate>> coordinateProducer) {
		// For each move
		for (Move move : moves) {
			// Let's assume we execute the move.
			move.execute();

			// Get the next jump moves.
			Collection<Move> nextMovesForThisMove =
					coordinateProducer.apply(move.getNextPosition()).stream()
					.filter(c-> isValidCoordinate(board,c))
					.filter(c-> pieceIsJumpable(board, piece, c))
					.filter(c-> nextSpaceIsLandable(board, piece, move.getNextPosition(), c))
					.map(c -> Move.multiJumpMove(board, piece, move.getNextPosition(), c, move))
					.collect(Collectors.toList());

			// And undo the move
			move.unExecute();

			// If there are any, then we replace this move with those moves AND THEIR CONTINUED MOVES
			if (!nextMovesForThisMove.isEmpty()) {
				searchJumps(nextMovesForThisMove, board, piece, finalMoves, coordinateProducer);
			}
			else {
				// Otherwise we don't have to jump more, and just add this move.
				finalMoves.add(move);
			}
		}
	}

	public Collection<Move> getMovesForColor(final Color color, final Board board) {

		// For each piece the player owns:
		Collection<PlacedPiece> pieces = board.getPiecesForColor(color);

		// Do jumps if available
		List<Move> moves =
				pieces.stream()
				.map(p -> p.getJumpMoves(board))
				.flatMap(m->m.stream())
				.collect(Collectors.toList());

		if (!moves.isEmpty()) {
			return moves;
		}

		// Otherwise do simple moves.
		return
				pieces.stream()
				.map(p -> p.getSimpleMoves(board))
				.flatMap(m->m.stream())
				.collect(Collectors.toList());
	}
}
