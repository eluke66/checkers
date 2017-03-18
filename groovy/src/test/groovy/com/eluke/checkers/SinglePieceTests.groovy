package com.eluke.checkers

import spock.lang.Specification

class SinglePieceTests extends Specification {
	Board board
	static Piece blackPiece

	def setupSpec() {
		blackPiece = new SinglePiece(color: Color.Black, forwardDirection: SinglePiece.FORWARD)
		TestHelpers.setupBoard({ new SinglePiece(color: Color.Red, forwardDirection: SinglePiece.REVERSE)}, blackPiece)
	}

	def setup() {
		board = new Board()
	}

	def "single pieces cannot jump when blocked" () {
		setup:
		Coordinate blackLocation = new Coordinate(0, 0)
		board.blackPieceAt blackLocation
		board.redPieceAt 1,1
		board.redPieceAt 2,2

		expect:
		blackPiece.getJumpMoves(board, blackLocation) == []
	}

	def "single pieces cannot jump their own man"() {
		setup:
		Coordinate blackLocation = new Coordinate(0, 0)
		board.blackPieceAt blackLocation
		board.blackPieceAt new Coordinate(1,1)

		expect:
		blackPiece.getJumpMoves(board, blackLocation) == []
	}


	def "single black pieces have two forward moves"() {
		setup:
		Coordinate blackLocation = new Coordinate(0, 2)
		board.blackPieceAt blackLocation

		expect:
		blackPiece.getSimpleMoves(board, blackLocation) == [Move.simpleMove(board, blackPiece, blackLocation, new Coordinate(1,1)), Move.simpleMove(board, blackPiece, blackLocation, new Coordinate(1,3))]
	}

	def "single red pieces have two forward moves"() {
		setup:
		Coordinate redLocation = new Coordinate(4, 2)
		def redPiece = board.redPieceAt 4,2

		expect:
		redPiece.getSimpleMoves(board, redLocation) == [Move.simpleMove(board, redPiece, redLocation, new Coordinate(3,1)), Move.simpleMove(board, redPiece, redLocation, new Coordinate(3,3))]
	}

	def "single pieces cannot jump off the board or when blocked"() {
		setup:
		Coordinate blackLocation = new Coordinate(0, 0)
		board.blackPieceAt blackLocation
		board.redPieceAt 1,1

		expect:
		blackPiece.getSimpleMoves(board, blackLocation) == []
	}

	def "single pieces can jump once and that piece is removed"() {
		setup:
		Coordinate blackLocation = new Coordinate(0, 0)
		board.blackPieceAt blackLocation
		board.redPieceAt 1,1

		when:
		def moves = blackPiece.getJumpMoves(board, blackLocation)

		then:
		TestHelpers.executeSingleMove(moves)
		TestHelpers.blackJumpsAllRedsTo(board, blackLocation, new Coordinate(2,2))
	}

	def "single pieces can jump more than once and those pieces are removed"() {
		setup:
		Coordinate blackLocation = new Coordinate(0, 0)
		board.blackPieceAt blackLocation
		board.redPieceAt 1,1
		board.redPieceAt 3,3

		when:
		def moves = blackPiece.getJumpMoves(board, blackLocation)

		then:
		TestHelpers.executeSingleMove(moves)
		TestHelpers.blackJumpsAllRedsTo(board, blackLocation, new Coordinate(4,4))
	}

	def "single pieces can have two forward single jumps"() {
		setup:
		Coordinate blackLocation = new Coordinate(0, 2)
		board.blackPieceAt blackLocation
		board.redPieceAt 1,1
		board.redPieceAt 1,3

		when:
		def moves = blackPiece.getJumpMoves(board, blackLocation)

		then:
		assert moves.size() == 2
		def nextCoordinates = moves.collect {m -> m.getNextPosition()} as Set
		assert nextCoordinates == [new Coordinate(2,0), new Coordinate(2,4)] as Set
	}

	def "single pieces can have multiple forward multi jumps"() {
		setup:
		Coordinate blackLocation = new Coordinate(0, 2)
		board.blackPieceAt blackLocation
		board.redPieceAt 1,1
		board.redPieceAt 1,3
		board.redPieceAt 3,5

		when:
		def moves = blackPiece.getJumpMoves(board, blackLocation)

		then:
		assert moves.size() == 2
		def nextCoordinates = moves.collect {m -> m.getNextPosition()} as Set
		assert nextCoordinates == [new Coordinate(2,0), new Coordinate(4,6)] as Set
	}

	def "when a single piece moves into the back row it is kinged"() {
		setup:
		Coordinate blackLocation = new Coordinate(board.size()-2, 0)
		board.blackPieceAt blackLocation

		when:
		def moves = blackPiece.getSimpleMoves(board, blackLocation)

		then:
		TestHelpers.executeSingleMove(moves)
		expectKingAt board.size()-1, 1
	}

	def "when a single piece jumps into the back row it is kinged"() {
		setup:
		Coordinate blackLocation = new Coordinate(board.size()-3, 1)
		board.blackPieceAt blackLocation
		board.redPieceAt board.size()-2, 2

		when:
		def moves = blackPiece.getJumpMoves(board, blackLocation)

		then:
		TestHelpers.executeSingleMove(moves)
		expectKingAt board.size()-1, 3
	}

	void expectKingAt(int row, int col) {
		def shouldBeKing = board.getPieceAt(new Coordinate(row, col)).get()
		assert shouldBeKing != null
		assert shouldBeKing.color == Color.Black
		assert shouldBeKing.canBeKinged() == false
	}
}
