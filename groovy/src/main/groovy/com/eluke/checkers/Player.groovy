package com.eluke.checkers

import java.util.Collection

interface Player {
	
	Move selectMove(Collection<Move> moves, Board board)
}
