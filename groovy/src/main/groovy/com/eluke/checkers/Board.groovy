package com.eluke.checkers

import groovy.transform.Canonical

public class Board {
	private static final int BOARD_SIZE = 8
	private Piece[][] board

	@Canonical
	static class PlacedPiece {
		@Delegate Piece piece
		Coordinate coordinate
	}

	public Board() {
		this(BOARD_SIZE)
	}

	public Board(int size) {
		board = new Piece[size][]
		size.times { i -> board[i] = new Piece[size] }
	}

	public Optional<Piece> getPieceAt(Coordinate coordinate) {
		if (!isValidPosition(coordinate)) {
			throw new RuntimeException("Cannot get piece at $coordinate as the location is invalid")
		}
		return Optional.ofNullable(board[coordinate.getRow()][coordinate.getCol()])
	}

	public Optional<Piece> safeGetPieceAt(Coordinate coordinate) {
		if (!isValidPosition(coordinate)) {
			return Optional.empty()
		}
		return Optional.ofNullable(board[coordinate.getRow()][coordinate.getCol()])
	}

	public void removePieceAt(Coordinate coordinate) {
		if (!isValidPosition(coordinate)) {
			throw new RuntimeException("Cannot remove piece at $coordinate as the location is invalid")
		}
		board[coordinate.getRow()][coordinate.getCol()] = null
	}

	public void placePieceAt(Piece piece, Coordinate coordinate) {
		if (!isValidPosition(coordinate)) {
			throw new RuntimeException("Cannot place piece at $coordinate as the location is invalid")
		}
		board[coordinate.getRow()][coordinate.getCol()] = piece
	}

	public Collection<PlacedPiece> getPiecesForColor(Color color) {
		int size = board.length
		def pieces = []
		size.times { row ->
			size.times { col ->
				if (board[row][col] != null && board[row][col].color == color) {
					pieces.add(new PlacedPiece(piece:board[row][col], coordinate:new Coordinate(row,col)))
				}
			}
		}
		return pieces
	}

	public boolean isValidPosition(Coordinate coordinate) {
		int row = coordinate.getRow()
		int column = coordinate.getCol()
		return row >= 0 && column >= 0 && row < board.length &&column < board[0].length && isUsableSquare(row, column)
	}

	private final boolean isUsableSquare(final int row, final int col) {
		return (isEven(row) && isEven(col)) || (!isEven(row) && !isEven(col))
	}
	public int size() { return board.length }

	private static boolean isEven(int rowCol) {
		return rowCol % 2 == 0
	}

	public boolean isFinalRowForPiece(Piece piece, Coordinate coordinate) {

		return	(piece.color == Color.Red && coordinate.getRow() == 0) ||
				(piece.color == Color.Black && coordinate.getRow() == board.length-1)
	}

	public String toString() {
		int size = board.length
		StringBuilder builder = new StringBuilder()
		builder.append("  ")
		size.times { col ->
			builder.append(col)
		}
		builder.append("\n")
		size.times { row ->
			builder.append(row).append(" ")
			size.times { col ->
				if (!isUsableSquare(row,col)) {
					builder.append('|')
				}
				else {
					Piece p = board[row][col]
					if (p == null) { builder.append('_') }
					else if (p.color == Color.Black) {
						if (p.canBeKinged()) builder.append('b')
						else builder.append("B")
					}
					else {
						if (p.canBeKinged()) builder.append('r')
						else builder.append("R")
					}
				}
			}
			builder.append('\n')
		}
		return builder.toString()
	}

}
