package com.eluke.checkers

import groovy.transform.Canonical

abstract class GameEvents {

	@Canonical
	static class PlayerTurn {
		final int turn
		final Player player
		final Board board
		final Color color
	}

	@Canonical
	static class GameFinished {
		final int turn
		final Player winner
	}
}
