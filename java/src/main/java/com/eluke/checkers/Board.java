package com.eluke.checkers;

import java.util.Collection;
import java.util.LinkedList;
import java.util.Optional;


public class Board {
	static class PlacedPiece {
		private final Piece piece;
		private final Coordinate coordinate;

		public PlacedPiece(final Piece piece, final Coordinate coordinate) {
			this.piece = piece;
			this.coordinate = coordinate;
		}

		public Collection<Move> getSimpleMoves(final Board board) {
			return piece.getSimpleMoves(board, getCoordinate());
		}

		public Collection<Move> getJumpMoves(final Board board) {
			return piece.getJumpMoves(board, getCoordinate());
		}

		public Coordinate getCoordinate() {
			return coordinate;
		}

		public Piece getPiece() {
			return piece;
		}
	}

	private static final int BOARD_SIZE = 8;
	private Piece board[][];

	public Board() {
		this(BOARD_SIZE);
	}

	public Board(final int size) {
		board = new Piece[size][];
		for (int i = 0; i < size; i++) {
			board[i] = new Piece[size];
		}
	}

	public Optional<Piece> getPieceAt(final Coordinate coordinate) {
		if (!isValidPosition(coordinate)) {
			throw new RuntimeException("Cannot get piece at " + coordinate + " as the location is invalid");
		}
		return Optional.ofNullable(board[coordinate.getRow()][coordinate.getCol()]);
	}

	public Optional<Piece> safeGetPieceAt(final Coordinate coordinate) {
		if (!isValidPosition(coordinate)) {
			return Optional.empty();
		}
		return Optional.ofNullable(board[coordinate.getRow()][coordinate.getCol()]);
	}

	public void removePieceAt(final Coordinate coordinate) {
		if (!isValidPosition(coordinate)) {
			throw new RuntimeException("Cannot remove piece at " + coordinate + " as the location is invalid");
		}
		board[coordinate.getRow()][coordinate.getCol()] = null;
	}

	public void placePieceAt(final Piece piece, final Coordinate coordinate) {
		if (!isValidPosition(coordinate)) {
			throw new RuntimeException("Cannot place piece at " + coordinate + " as the location is invalid");
		}

		board[coordinate.getRow()][coordinate.getCol()] = piece;
	}

	public Collection<PlacedPiece> getPiecesForColor(final Color color) {
		Collection<PlacedPiece> pieces = new LinkedList<>();
		for (int row = 0; row < board.length; row++) {
			for (int col = 0; col < board[0].length; col++) {
				if (board[row][col] != null && board[row][col].color().equals(color)) {
					pieces.add(new PlacedPiece(board[row][col], new Coordinate(row,col)));
				}
			}
		}
		return pieces;
	}
	/*   0 1 2 3
	 *   R B R B   row 3
	 *   B R B R   row 2
	 *   R B R B   row 1
	 *   B R B R   row 0
	 */
	public boolean isValidPosition(final Coordinate coordinate) {
		int row = coordinate.getRow();
		int column = coordinate.getCol();
		return
				row >= 0 &&
				column >= 0 &&
				row < board.length &&
				column < board[0].length &&
				isUsableSquare(row, column);
	}

	private final boolean isUsableSquare(final int row, final int col) {
		return (isEven(row) && isEven(col)) || (!isEven(row) && !isEven(col));
	}
	public int size() { return board.length; }

	private static boolean isEven(final int rowCol) {
		return rowCol % 2 == 0;
	}

	public boolean isFinalRowForPiece(final Piece piece, final Coordinate coordinate) {
		return
				(piece.color() == Color.Red && coordinate.getRow() == 0) ||
				(piece.color() == Color.Black && coordinate.getRow() == board.length-1);
	}

	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append("  ");
		for (int col = 0; col < board[0].length; col++) {
			builder.append(col);
		}
		builder.append("\n");
		for (int row = 0; row < board.length; row++) {
			builder.append(row).append(" ");
			for (int col = 0; col < board[0].length; col++) {
				if (!isUsableSquare(row,col)) {
					builder.append('|');
				}
				else {
					Piece p = board[row][col];
					if (p == null) { builder.append('_'); }
					else if (p.color() == Color.Black) {
						if (p.canBeKinged()) builder.append('b');
						else builder.append("B");
					}
					else {
						if (p.canBeKinged()) builder.append('r');
						else builder.append("R");
					}
				}
			}
			builder.append('\n');
		}
		return builder.toString();
	}

	public String dump() {
		StringBuilder builder = new StringBuilder();
		getPiecesForColor(Color.Black).stream()
			.forEach(pp -> builder.append("board.placePieceAt(").append(dumpPiece(pp, Color.Black)).append(");\n"));
		getPiecesForColor(Color.Red).stream()
		.forEach(pp -> builder.append("board.placePieceAt(").append(dumpPiece(pp, Color.Red)).append(");\n"));
		return builder.toString();
	}

	private String dumpPiece(final PlacedPiece piece, final Color color) {
		if (piece.getPiece() instanceof SinglePiece) {
			SinglePiece sp = (SinglePiece)piece.getPiece();

			return sp.color() + "Piece(), new Coordinate" + piece.getCoordinate();
		}
		else {
			KingPiece kp = (KingPiece)piece.getPiece();
			return "new KingPiece(Color." + kp.color() + "), new Coordinate" + piece.getCoordinate();
		}
	}
}
