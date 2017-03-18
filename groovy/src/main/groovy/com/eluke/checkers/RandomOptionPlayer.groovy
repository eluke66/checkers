package com.eluke.checkers

class RandomOptionPlayer implements Player {

	@Override
	public Move selectMove(Collection<Move> moves, Board board) {
		return moves[ new Random().nextInt(moves.size()) ]
	}

}
