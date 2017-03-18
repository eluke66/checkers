package com.eluke.checkers

import spock.lang.Specification

class GameTests extends Specification {

	def "each player starts with 12 pieces"() {
		setup:
		Board board = new Board()

		when:
		Game.putPiecesOnTheBoard(board)

		then:
		board.getPiecesForColor(Color.Black).size() == 12
		board.getPiecesForColor(Color.Red).size() == 12
	}

	def "closest left square to each player starts with a piece"() {
		setup:
		Board board = new Board()

		when:
		Game.putPiecesOnTheBoard(board)
		def black = board.getPieceAt(new Coordinate(0,0))
		def red = board.getPieceAt(new Coordinate(board.size()-1,board.size()-1))

		then:
		assert black.isPresent()
		assert black.get().color == Color.Black
		assert red.isPresent()
		assert red.get().color == Color.Red
	}

	def "board must be 8x8"() {
		setup:
		Board board = new Board()

		expect:
		board.size() == 8
	}

	def "black player moves first"() {
		setup:
		Player player1 = Mock(Player.class)
		Player player2 = Mock(Player.class)
		MoveRules rules = Mock(MoveRules.class)
		Game game = new Game(player1, player2, rules)

		when:
		game.play()

		then:
		1 * rules.getMovesForColor(Color.Black, _) >> []
	}

	def "red player moves after black"() {
		setup:
		Player player1 = Stub(Player.class)
		Player player2 = Mock(Player.class)
		MoveRules rules = Mock(MoveRules.class)
		Game game = new Game(player1, player2, rules)
		Move move = Move.simpleMove(game.board, new SinglePiece(color: Color.Black, forwardDirection: SinglePiece.FORWARD), new Coordinate(2,0), new Coordinate(3,1))

		when:
		game.play()

		then:
		2 * rules.getMovesForColor(_, _) >>> [[move], []]
		player1.selectMove([move],_) >> move
	}

	def "when a player cannot move then the other player wins"() {
		setup:
		Player player1 = Mock(Player.class)
		Player player2 = Mock(Player.class)
		MoveRules rules = Stub(MoveRules.class) {
			getMovesForColor(Color.Black, _) >> []
		}
		Game game = new Game(player1, player2, rules)

		expect:
		player2 == game.play()
	}
}
