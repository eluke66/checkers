package com.eluke.checkers;

import java.util.Collection;

class RandomOptionPlayer implements Player {
	@Override
	public String toString() { return ""; }

	@Override
	public Move selectMove(final Collection<Move> moves, final Board board) {
		return moves.stream()
				.skip((int) (moves.size() * Math.random()))
				.findFirst().get();
	}

}