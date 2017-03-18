package com.eluke.checkers;

public class GameEvents {

	static class PlayerTurn {
		public final int turn;
		public final Player player;
		public final Board board;
		public final Color color;

		public PlayerTurn(final int turn, final Player player, final Board board, final Color color) {
			this.turn = turn;
			this.player = player;
			this.board = board;
			this.color = color;
		}

	}

	static class GameFinished {
		public final int turn;
		public final Player winner;

		public GameFinished(final int turn, final Player winner) {
			this.turn = turn;
			this.winner = winner;
		}

	}

}
