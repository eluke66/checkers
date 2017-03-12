package com.eluke.checkers;

import java.util.Collection;

public interface Player {

	Move selectMove(Collection<Move> moves, Board board);

}
