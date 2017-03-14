package com.eluke.checkers;

import java.util.Observable;
import java.util.Observer;

class ConsoleObserver implements Observer {

	@Override
	public void update(Observable o, Object arg) {
		if (arg instanceof GameEvents.PlayerTurn) {
			GameEvents.PlayerTurn pt = (GameEvents.PlayerTurn)arg;
			System.out.println("Turn " + pt.turn + ", Player " + pt.player + " (" + pt.color +")");
			System.out.println(pt.board);
		}
		else if (arg instanceof GameEvents.GameFinished) {
			GameEvents.GameFinished gf = (GameEvents.GameFinished)arg;
			System.out.println("Player " + gf.winner + " wins on turn " + gf.turn);
		}
	}

}