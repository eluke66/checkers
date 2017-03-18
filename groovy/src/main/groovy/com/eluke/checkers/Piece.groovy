package com.eluke.checkers

interface Piece {

	public Collection<Move> getSimpleMoves(Board board, Coordinate coordinate)

	public Collection<Move> getJumpMoves(Board board, Coordinate coordinate)

	public boolean canBeKinged()
}
