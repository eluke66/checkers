package com.eluke.checkers

import java.util.Collection

class RandomOptionPlayer implements Player {

	@Override
	public Move selectMove(Collection<Move> moves, Board board) {
		return moves[ new Random().nextInt(moves.size()) ]
//		return moves.stream()
//				.skip((int) (moves.size() * Math.random()))
//				.findFirst().get();
	}

}
