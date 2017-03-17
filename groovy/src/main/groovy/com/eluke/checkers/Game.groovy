package com.eluke.checkers

import java.util.Observable

class Game extends Observable {
	final Board board
	final Player[] players
	final MoveRules moveRules
	final Map<Player,Color> colorsPerPlayer

	public Game(Player player1, Player player2) {
		this(player1, player2,new MoveRules())
	}

	public Game(Player player1, Player player2, MoveRules moveRules) {
		board = new Board()
		players = [player1, player2]
		this.moveRules = moveRules
		colorsPerPlayer = new LinkedHashMap<>()
		colorsPerPlayer.put(player1, Color.Black)
		colorsPerPlayer.put(player2, Color.Red)
	}

	public Player play() {
		putPiecesOnTheBoard(board);

		int whichPlayer = 0;
		int whichTurn = 0;
		while (true) {
			Player currentPlayer = players[whichPlayer];
			Color color = colorsPerPlayer.get(currentPlayer);
			emit(new GameEvents.PlayerTurn(whichTurn, currentPlayer, board, color))
			Collection<Move> moves = moveRules.getMovesForColor(color, board)
			if (!playerHasValidMoves(moves)) {
				break;
			}
			Move move = currentPlayer.selectMove(moves, board);
			move.execute();

			whichPlayer = otherPlayer(whichPlayer);
			whichTurn++;
		}

		Player winningPlayer = players[otherPlayer(whichPlayer)];
		emit(new GameEvents.GameFinished(whichTurn, winningPlayer));
		
		return winningPlayer;
	}

	private void emit(Object object) {
		setChanged();
		notifyObservers(object);
	}
	private boolean playerHasValidMoves(Collection<Move> moves) {
		return !moves.isEmpty();
	}

	private int otherPlayer(int player) {
		return (player+1) % 2;
	}

	static void putPiecesOnTheBoard(Board board) {
		final int NUM_PIECES_PER_PLAYER = 12;

		int piecesPerRow = board.size()/2;
		int rows = NUM_PIECES_PER_PLAYER / piecesPerRow;
		if (piecesPerRow * rows != NUM_PIECES_PER_PLAYER) {
			throw new IllegalStateException("Cannot fit " + NUM_PIECES_PER_PLAYER + " onto a board of size " + board.size());
		}

		for (int row = 0; row < rows; row++ ) {
			for (int col = (row % 2 == 0)?0 : 1; col < board.size(); col+=2) {
				Piece piece = new SinglePiece(Color.Black, SinglePiece.FORWARD);
				board.placePieceAt(piece, new Coordinate(row,col));
			}
		}

		for (int row = 0; row < rows; row++ ) {
			int thisRow = board.size() - row - 1;
			for (int col = (thisRow % 2 == 0)?0 : 1; col < board.size(); col+=2) {
				Piece piece = new SinglePiece(Color.Red, SinglePiece.REVERSE);
				board.placePieceAt(piece, new Coordinate(thisRow, col));
			}
		}
	}
	
	static profile() {
		long totalTimeNs = 0;
		final int NUM_GAMES = 10000;
		for (int i = 0; i < NUM_GAMES; i++) {
			Game game = new Game(new RandomOptionPlayer(), new RandomOptionPlayer());
			ConsoleObserver o = new ConsoleObserver();
			//game.addObserver(o);

			try {
				long start = System.nanoTime();
				game.play();
				long end = System.nanoTime();
				totalTimeNs += (end-start);
			}
			catch (RuntimeException e) {
				e.printStackTrace();
				System.out.println("Board is now\n" + game.board);
				System.out.println(game.board.dump());
				throw e;
			}
			//if ((i+1) % (NUM_GAMES/10) == 0) { System.err.println(i+1); }
		}
		long timeInMs = (totalTimeNs / 1000000);
		println "Executed " + NUM_GAMES + " in " + timeInMs + " ms, or " + (timeInMs / (float)NUM_GAMES) + " ms/game"
	}

	static playConsole() {
		Game game = new Game(new ConsolePlayer(), new ConsolePlayer())
		game.addObserver(new ConsoleObserver())
		Player winner = game.play()
	}
	
	static main(args) {
		if (args.length == 0) {
			profile()
		}
		else {
			playConsole()
		}
	}

}
