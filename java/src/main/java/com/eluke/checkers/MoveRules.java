package com.eluke.checkers;

import java.util.Collection;
import java.util.LinkedList;
import java.util.List;
import java.util.function.Function;
import java.util.stream.Collectors;

import com.eluke.checkers.Board.PlacedPiece;

public class MoveRules {

	public static Collection<Move> getSimpleMoves(Board board, Piece piece, Coordinate coordinate, Function<Coordinate,Collection<Coordinate>> coordinateProducer) {
		return 
		coordinateProducer.apply(coordinate).stream()
			.filter(c -> board.isValidPosition(c))
			.filter(c-> !board.getPieceAt(c).isPresent())
			.map(c -> Move.simpleMove(board, piece, coordinate, c))
			.collect(Collectors.toList());
	}
	
	public static Collection<Move> getJumpMoves(Board board, Piece piece, Coordinate coordinate, Function<Coordinate,Collection<Coordinate>> coordinateProducer) {
		Collection<Move> initialMoves =  
		coordinateProducer.apply(coordinate).stream()
			.filter(c -> board.isValidPosition(c))
			.filter(c -> board.getPieceAt(c).isPresent() && board.getPieceAt(c).get().color() != piece.color())
			.filter(c -> !board.getPieceAt(Coordinate.extending(coordinate, c)).isPresent())
			.map(c -> Move.jumpMove(board, piece, coordinate, c))
			.collect(Collectors.toList());
		

		Collection<Move> finalMoves = new LinkedList<Move>();
		searchJumps(initialMoves, board, piece, finalMoves, coordinateProducer);
		return finalMoves;
	}
	
	private static void searchJumps(Collection<Move> moves, Board board, Piece piece, Collection<Move> finalMoves, Function<Coordinate,Collection<Coordinate>> coordinateProducer) {
		// For each move
		for (Move move : moves) {
			// Let's assume we execute the move.
			move.execute();
			
			// Get the next jump moves.
			Collection<Move> nextMovesForThisMove =
					coordinateProducer.apply(move.getNextPosition()).stream()
					.filter(c -> board.isValidPosition(c))
					.filter(c-> board.getPieceAt(c).isPresent())
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
	
	public Collection<Move> getMovesForColor(Color color, Board board) {

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
