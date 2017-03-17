package com.eluke.checkers


import com.eluke.checkers.Board
import com.eluke.checkers.Color
import com.eluke.checkers.Coordinate
import com.eluke.checkers.KingPiece
import com.eluke.checkers.MoveRules
import com.eluke.checkers.Piece
import com.eluke.checkers.SinglePiece

import spock.lang.Specification

class MoveRuleTests extends Specification {
	Board board
	MoveRules rules
	static Piece blackPiece

	def setupSpec() {
		blackPiece = new SinglePiece(color: Color.Black, forwardDirection: SinglePiece.FORWARD)
		TestHelpers.setupBoard({ new SinglePiece(color: Color.Red, forwardDirection: SinglePiece.REVERSE)}, blackPiece)
	}
	
	def setup() {
		board = new Board()
		rules = new MoveRules()
	}
	
	def "if capturing moves are available they must be picked for single jumps"() {
		setup:
		board.blackPieceAt new Coordinate(0,2)
		board.redPieceAt 1,1
		
		when:
		def moves = rules.getMovesForColor(Color.Black, board)
		
		then:
		TestHelpers.executeSingleMove(moves)
		assert board.getPiecesForColor(Color.Red) == []
	}

	def "if capturing moves are available they must be picked for multi jumps"() {
		setup:
		board.blackPieceAt new Coordinate(0,2)
		board.redPieceAt 1,3
		board.redPieceAt 3,5
		
		when:
		def moves = rules.getMovesForColor(Color.Black, board)
		
		then:
		TestHelpers.executeSingleMove(moves)
		assert board.getPiecesForColor(Color.Red) == []
		assert board.getPieceAt(new Coordinate(4,6)).get().color == Color.Black
	}
}
