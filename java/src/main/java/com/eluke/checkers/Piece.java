package com.eluke.checkers;

import java.util.Collection;

public abstract class Piece {
	private final Color color;

	public Piece(final Color color) {
		this.color = color;
	}

	public Color color() {
		return this.color;
	}

	public abstract Collection<Move> getSimpleMoves(Board board, Coordinate coordinate);

	public abstract Collection<Move> getJumpMoves(Board board, Coordinate coordinate);

	public abstract boolean canBeKinged();

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((color == null) ? 0 : color.hashCode());
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
		Piece other = (Piece) obj;
		if (color != other.color)
			return false;
		return true;
	}
}
