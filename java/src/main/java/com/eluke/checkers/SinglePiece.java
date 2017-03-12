package com.eluke.checkers;

import java.util.Arrays;
import java.util.Collection;

public class SinglePiece extends Piece {
	public static final int FORWARD = 1;
	public static final int REVERSE = -1;
	private final int forwardDirection;
	
	public SinglePiece(Color color, int direction) {
		super(color);
		this.forwardDirection = direction;
	}

	@Override
	public Collection<Move> getSimpleMoves(Board board, Coordinate coordinate) {
		return MoveRules.getSimpleMoves(board, this, coordinate, this::getFollowingCoords);
	}
	
	private Collection<Coordinate> getFollowingCoords(Coordinate c) {
		int nextRow = c.getRow()+forwardDirection;
		return Arrays.asList(
				new Coordinate(nextRow, c.getCol()+1),
				new Coordinate(nextRow, c.getCol()-1));
	}
	
	@Override
	public Collection<Move> getJumpMoves(Board board, Coordinate coordinate) {
		return MoveRules.getJumpMoves(board, this, coordinate, this::getFollowingCoords);
	}

	@Override
	public boolean canBeKinged() {
		return true;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + forwardDirection;
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		SinglePiece other = (SinglePiece) obj;
		if (forwardDirection != other.forwardDirection)
			return false;
		return true;
	}
}
