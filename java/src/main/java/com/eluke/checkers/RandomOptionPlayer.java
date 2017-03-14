package com.eluke.checkers;

import java.util.Collection;

class RandomOptionPlayer implements Player {

	public String toString() { return ""; }

	@Override
	public Move selectMove(Collection<Move> moves, Board board) {
		return moves.stream()
				.skip((int) (moves.size() * Math.random()))
				.findFirst().get();
	}

}