package com.eluke.checkers

import groovy.transform.Immutable

@Immutable
class KingPiece implements Piece {
	final Color color

	@Override
	public Collection<Move> getSimpleMoves(Board board, Coordinate coordinate) {
		return MoveRules.getSimpleMoves(board, this, coordinate, this.getFollowingCoords)
	}

	@Override
	public Collection<Move> getJumpMoves(Board board, Coordinate coordinate) {
		return MoveRules.getJumpMoves(board, this, coordinate, this.getFollowingCoords)
	}

	@Override
	public boolean canBeKinged() {
		return false
	}

	final Closure getFollowingCoords = { c->
		[ new Coordinate(c.getRow()+1, c.getCol()+1),
		  new Coordinate(c.getRow()+1, c.getCol()-1),
		  new Coordinate(c.getRow()-1, c.getCol()+1),
	      new Coordinate(c.getRow()-1, c.getCol()-1) ]
	}
}
