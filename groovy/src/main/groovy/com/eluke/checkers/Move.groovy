package com.eluke.checkers

import com.eluke.checkers.Move.JumpMove
import com.eluke.checkers.Move.MultiJumpMove

import groovy.transform.Canonical
import groovy.transform.Immutable
import groovy.transform.ToString

@Canonical @ToString(includePackage=false,excludes="board",includeNames=true)
abstract class Move {
	Piece piece;
	Board board;
	Coordinate from;
	Coordinate to;

	public static Move simpleMove(Board board, Piece piece, Coordinate from, Coordinate to) {
		Move m = new SimpleMove(piece:piece, board:board, from:from, to:to)
		return m
	}
	
	public static Move jumpMove(Board board, Piece piece, Coordinate from, Coordinate to) {
		return new JumpMove(piece, board, from, Coordinate.extending(from, to), to);
	}

	public static Move multiJumpMove(Board board, Piece piece, Coordinate from, Coordinate to, Move previousMove) {
		return new MultiJumpMove(piece, board, from, Coordinate.extending(from, to), to, previousMove);
	}
	
	private static void moveAndKingPiece(Piece piece, Board board, Coordinate to) {
		board.placePieceAt(piece, to);
		if (board.isFinalRowForPiece(piece, to) && piece.canBeKinged()) {
			board.placePieceAt(new KingPiece(color:piece.color), to);
		}
	}

	public Coordinate getNextPosition() {
		return to;
	}
	
	public abstract void execute();
	public abstract void unExecute();
	
	@Canonical @ToString(includePackage=false,includeSuper=true)
	private static class SimpleMove extends Move {
		
		public void execute() {
			board.removePieceAt(from);
			moveAndKingPiece(piece, board, to);
		}

		@Override
		public void unExecute() {
			board.removePieceAt(to);
			board.placePieceAt(piece, from);
		}
		
	}
	@ToString(includePackage=false,includeSuper=true,includeNames=true)
	private static class MultiJumpMove extends JumpMove {
		private final Move previousMove;

		public MultiJumpMove(Piece piece,Board board, Coordinate from, Coordinate to, Coordinate existingPiece, Move previousMove) {
			super(piece, board, from, to, existingPiece)
			this.previousMove = previousMove
		}
		public void execute() {
			previousMove.execute();
			super.execute();
		}
		
		public void unExecute() {
			super.unExecute();
			previousMove.unExecute();
		}
	}
	
	@Canonical @ToString(includePackage=false,includeSuper=true,includeNames=true,ignoreNulls=true)
	private static class JumpMove extends Move {
		final Coordinate existingPieceLocation;
		Piece removedPiece = null;
		
		public JumpMove(Piece piece, Board board, Coordinate from, Coordinate to, Coordinate existingPiece) {
			super(piece, board, from, to);
			this.existingPieceLocation = existingPiece;
		}

		public void execute() {
			if (removedPiece == null) {
				removedPiece = board.getPieceAt(existingPieceLocation).get();
				board.removePieceAt(from);
				moveAndKingPiece(piece, board, to);
				board.removePieceAt(existingPieceLocation);
			}
			else {
				throw new IllegalStateException("Trying to re-execute jump move " + this);
			}
		}

		@Override
		public void unExecute() {
			if (removedPiece != null) {
				board.removePieceAt(to);
				board.placePieceAt(piece, from);
				board.placePieceAt(removedPiece, existingPieceLocation);
				removedPiece = null;
			}
			else {
				throw new IllegalStateException("Trying to unExecute a not-yet-executed jump move " + this);
			}
		}
	}
}
