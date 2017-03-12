package com.eluke.checkers;

import java.util.Arrays;
import java.util.Collection;

public class KingPiece extends Piece {

	public KingPiece(Piece piece) {
		super(piece.color());
	}
	
	public KingPiece(Color color) {
		super(color);
	}

	@Override
	public Collection<Move> getSimpleMoves(Board board, Coordinate coordinate) {
		return MoveRules.getSimpleMoves(board, this, coordinate, this::getFollowingCoords);
	}

	@Override
	public Collection<Move> getJumpMoves(Board board, Coordinate coordinate) {
		return MoveRules.getJumpMoves(board, this, coordinate, this::getFollowingCoords);
	}

	@Override
	public boolean canBeKinged() {
		return false;
	}

	private Collection<Coordinate> getFollowingCoords(Coordinate c) {
		return Arrays.asList(
				new Coordinate(c.getRow()+1, c.getCol()+1),
				new Coordinate(c.getRow()+1, c.getCol()-1),
				new Coordinate(c.getRow()-1, c.getCol()+1),
				new Coordinate(c.getRow()-1, c.getCol()-1));
	}
}
