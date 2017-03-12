package com.eluke.checkers;

import java.util.Collection;
import java.util.LinkedHashMap;
import java.util.Map;

public class Game {
	final Board board;
	private final Player[] players;
	private final MoveRules moveRules;
	private final Map<Player,Color> colorsPerPlayer;
	
	public Game(Player player1, Player player2) {
		this(player1, player2,new MoveRules());
	}
	
	public Game(Player player1, Player player2, MoveRules moveRules) {
		board = new Board();
		players = new Player[]{player1, player2};
		this.moveRules = moveRules;
		colorsPerPlayer = new LinkedHashMap<>();
		colorsPerPlayer.put(player1, Color.Black);
		colorsPerPlayer.put(player2, Color.Red);
	}
	
	public Player play() {
		putPiecesOnTheBoard(board);
		
		int whichPlayer = 0;
		int whichTurn = 0;
		while (true) {
			Player currentPlayer = players[whichPlayer];
			Color color = colorsPerPlayer.get(currentPlayer);
			Collection<Move> moves = moveRules.getMovesForColor(color, board);
			if (!playerHasValidMoves(moves)) {
				break;
			}
			Move move = currentPlayer.selectMove(moves, board);
			move.execute();
			
			whichPlayer = otherPlayer(whichPlayer);
			whichTurn++;
		}
		
		Player winningPlayer = players[otherPlayer(whichPlayer)];
		playerWins(winningPlayer, whichTurn);
		return winningPlayer;
	}
	
	private void playerWins(Player player, int whichTurn) {
		System.err.println("Player " + player + " wins on turn " + whichTurn);
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

	public static void main(String[] args) {
		new Game(null, null).play();
	}

}
