package com.eluke.checkers

class ConsoleObserver implements Observer {

	@Override
	public void update(Observable o, Object arg) {
		if (arg instanceof GameEvents.PlayerTurn) {
			GameEvents.PlayerTurn pt = (GameEvents.PlayerTurn)arg
			println pt
		}
		else if (arg instanceof GameEvents.GameFinished) {
			GameEvents.GameFinished gf = (GameEvents.GameFinished)arg
			println gf
		}
	}
}
