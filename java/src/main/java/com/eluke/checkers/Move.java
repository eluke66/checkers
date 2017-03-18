package com.eluke.checkers;

public abstract class Move {
	protected final Piece piece;
	protected final Board board;
	protected final Coordinate from;
	protected final Coordinate to;

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((from == null) ? 0 : from.hashCode());
		result = prime * result + ((piece == null) ? 0 : piece.hashCode());
		result = prime * result + ((to == null) ? 0 : to.hashCode());
		return result;
	}

	@Override
	public boolean equals(final Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Move other = (Move) obj;
		if (from == null) {
			if (other.from != null)
				return false;
		} else if (!from.equals(other.from))
			return false;
		if (piece == null) {
			if (other.piece != null)
				return false;
		} else if (!piece.equals(other.piece))
			return false;
		if (to == null) {
			if (other.to != null)
				return false;
		} else if (!to.equals(other.to))
			return false;
		return true;
	}

	public Move(final Piece piece, final Board board, final Coordinate from, final Coordinate to) {
		this.piece = piece;
		this.board = board;
		this.from = from;
		this.to = to;
	}

	public static Move simpleMove(final Board board, final Piece piece, final Coordinate from, final Coordinate to) {
		return new SimpleMove(piece, board, from, to);
	}

	public static Move jumpMove(final Board board, final Piece piece, final Coordinate from, final Coordinate to) {
		return new JumpMove(piece, board, from, Coordinate.extending(from, to), to);
	}

	public static Move multiJumpMove(final Board board, final Piece piece, final Coordinate from, final Coordinate to, final Move previousMove) {
		return new MultiJumpMove(piece, board, from, Coordinate.extending(from, to), to, previousMove);
	}

	private static void moveAndKingPiece(final Piece piece, final Board board, final Coordinate to) {
		board.placePieceAt(piece, to);
		if (board.isFinalRowForPiece(piece, to) && piece.canBeKinged()) {
			board.placePieceAt(new KingPiece(piece), to);
		}
	}

	public Coordinate getNextPosition() {
		return to;
	}

	@Override
	public String toString() {
		return "Move [piece=" + piece + ", from=" + from + ", to=" + to + "]";
	}

	public abstract void execute();
	public abstract void unExecute();

	private static class SimpleMove extends Move {
		public SimpleMove(final Piece piece, final Board board, final Coordinate from, final Coordinate to) {
			super(piece, board, from, to);
		}

		@Override
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

	private static class MultiJumpMove extends JumpMove {
		private final Move previousMove;

		public MultiJumpMove(final Piece piece, final Board board, final Coordinate from, final Coordinate to, final Coordinate existingPiece,
				final Move previousMove) {
			super(piece, board, from, to, existingPiece);
			this.previousMove = previousMove;
		}

		@Override
		public void execute() {
			previousMove.execute();
			super.execute();
		}

		@Override
		public void unExecute() {
			super.unExecute();
			previousMove.unExecute();
		}

		@Override
		public int hashCode() {
			final int prime = 31;
			int result = super.hashCode();
			result = prime * result + ((previousMove == null) ? 0 : previousMove.hashCode());
			return result;
		}

		@Override
		public boolean equals(final Object obj) {
			if (this == obj)
				return true;
			if (!super.equals(obj))
				return false;
			if (getClass() != obj.getClass())
				return false;
			MultiJumpMove other = (MultiJumpMove) obj;
			if (previousMove == null) {
				if (other.previousMove != null)
					return false;
			} else if (!previousMove.equals(other.previousMove))
				return false;
			return true;
		}

		@Override
		public String toString() {
			return "MultiJumpMove [previousMove=" + previousMove + " this move=" + super.toString();
		}
	}

	private static class JumpMove extends Move {
		private final Coordinate existingPieceLocation;
		private Piece removedPiece = null;

		public JumpMove(final Piece piece, final Board board, final Coordinate from, final Coordinate to, final Coordinate existingPiece) {
			super(piece, board, from, to);
			this.existingPieceLocation = existingPiece;
		}

		@Override
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
		public String toString() {
			return "JumpMove [existingPieceLocation=" + existingPieceLocation + ", removedPiece=" + removedPiece + ", piece=" + piece
					+ ", from=" + from + ", to=" + to + "]";
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

		@Override
		public int hashCode() {
			final int prime = 31;
			int result = super.hashCode();
			result = prime * result + ((existingPieceLocation == null) ? 0 : existingPieceLocation.hashCode());
			result = prime * result + ((removedPiece == null) ? 0 : removedPiece.hashCode());
			return result;
		}

		@Override
		public boolean equals(final Object obj) {
			if (this == obj)
				return true;
			if (!super.equals(obj))
				return false;
			if (getClass() != obj.getClass())
				return false;
			JumpMove other = (JumpMove) obj;
			if (existingPieceLocation == null) {
				if (other.existingPieceLocation != null)
					return false;
			} else if (!existingPieceLocation.equals(other.existingPieceLocation))
				return false;
			if (removedPiece == null) {
				if (other.removedPiece != null)
					return false;
			} else if (!removedPiece.equals(other.removedPiece))
				return false;
			return true;
		}
	}

}
