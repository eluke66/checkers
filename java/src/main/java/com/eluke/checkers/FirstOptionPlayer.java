package com.eluke.checkers;

import java.util.Collection;

class FirstOptionPlayer implements Player {

	public String toString() { return ""; }
	@Override
	public Move selectMove(Collection<Move> moves, Board board) {
		return moves.iterator().next();
	}

}