package com.eluke.checkers;

import java.util.Collection;

class FirstOptionPlayer implements Player {

	@Override
	public String toString() { return ""; }
	@Override
	public Move selectMove(final Collection<Move> moves, final Board board) {
		return moves.iterator().next();
	}

}