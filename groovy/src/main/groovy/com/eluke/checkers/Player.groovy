package com.eluke.checkers

interface Player {

	Move selectMove(Collection<Move> moves, Board board)
}
