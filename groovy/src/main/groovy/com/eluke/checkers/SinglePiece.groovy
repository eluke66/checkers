package com.eluke.checkers

import groovy.transform.Immutable

@Immutable
class SinglePiece implements Piece {
	final Color color;
	static final int FORWARD = 1
	static final int REVERSE = -1 
	final int forwardDirection
	
	@Override
	public Collection<Move> getSimpleMoves(Board board, Coordinate coordinate) {
		return MoveRules.getSimpleMoves(board, this, coordinate, getFollowingCoords.curry(forwardDirection))
	}
	
	@Override
	public Collection<Move> getJumpMoves(Board board, Coordinate coordinate) {
		return MoveRules.getJumpMoves(board, this, coordinate, getFollowingCoords.curry(forwardDirection))
	}

	static def getFollowingCoords = { int forwardDirection, Coordinate c -> 
		int nextRow = c.getRow()+forwardDirection
		return [new Coordinate(nextRow, c.getCol()+1), new Coordinate(nextRow, c.getCol()-1)]
	}
	
	@Override
	public boolean canBeKinged() {
		return true;
	}

}
