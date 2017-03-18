package com.eluke.checkers;

import java.util.Arrays;
import java.util.Collection;

public class KingPiece extends Piece {

	public KingPiece(final Piece piece) {
		super(piece.color());
	}

	public KingPiece(final Color color) {
		super(color);
	}

	@Override
	public Collection<Move> getSimpleMoves(final Board board, final Coordinate coordinate) {
		return MoveRules.getSimpleMoves(board, this, coordinate, this::getFollowingCoords);
	}

	@Override
	public Collection<Move> getJumpMoves(final Board board, final Coordinate coordinate) {
		return MoveRules.getJumpMoves(board, this, coordinate, this::getFollowingCoords);
	}

	@Override
	public boolean canBeKinged() {
		return false;
	}

	private Collection<Coordinate> getFollowingCoords(final Coordinate c) {
		return Arrays.asList(
				new Coordinate(c.getRow()+1, c.getCol()+1),
				new Coordinate(c.getRow()+1, c.getCol()-1),
				new Coordinate(c.getRow()-1, c.getCol()+1),
				new Coordinate(c.getRow()-1, c.getCol()-1));
	}

	@Override
	public String toString() {
		return this.color() + " King";
	}
}
