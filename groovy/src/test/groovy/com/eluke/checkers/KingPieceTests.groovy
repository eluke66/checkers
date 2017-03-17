package com.eluke.checkers

import java.util.Collection
import java.util.Optional

import org.junit.Before
import org.junit.Test

import com.eluke.checkers.Board
import com.eluke.checkers.Color
import com.eluke.checkers.Coordinate
import com.eluke.checkers.KingPiece
import com.eluke.checkers.Move
import com.eluke.checkers.Piece

import spock.lang.Specification

class KingPieceTests extends Specification {
	Board board;
	static Piece blackPiece;

	def setupSpec() {
		blackPiece = new KingPiece(color: Color.Black)
		TestHelpers.setupBoard({new KingPiece(color: Color.Red)}, blackPiece)
	}
	
	def setup() {
		board = new Board()
	}

	def "kings can move forward and backwards"() {
		setup:
		Coordinate blackLocation = new Coordinate(2, 2)
		board.blackPieceAt blackLocation
		
		expect:
		blackPiece.getSimpleMoves(board, blackLocation) as Set == \
			[Move.simpleMove(board, blackPiece, blackLocation, new Coordinate(1,1)),
				Move.simpleMove(board, blackPiece, blackLocation, new Coordinate(1,3)),
				Move.simpleMove(board, blackPiece, blackLocation, new Coordinate(3,1)),
				Move.simpleMove(board, blackPiece, blackLocation, new Coordinate(3,3))] as Set
	}
	
	def "kings cannot jump when blocked"() {
		setup:
		Coordinate blackLocation = new Coordinate(0, 0)
		board.blackPieceAt blackLocation
		board.redPieceAt 1,1
		board.redPieceAt 2,2
		
		expect:
		blackPiece.getJumpMoves(board, blackLocation) == []
	}
	
	def "kings can jump forward once"() {
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
	
	def "kings can jump backwards once"() {
		setup:
		Coordinate blackLocation = new Coordinate(2, 2)
		board.blackPieceAt blackLocation
		board.redPieceAt 1,1
		
		when:
		def moves = blackPiece.getJumpMoves(board, blackLocation)
		
		then:
		TestHelpers.executeSingleMove(moves)
		TestHelpers.blackJumpsAllRedsTo(board, blackLocation, new Coordinate(0,0))
	}
	
	def "kings can jump forwards then backwards"() {
		setup:
		Coordinate blackLocation = new Coordinate(2,0)
		board.blackPieceAt blackLocation
		board.redPieceAt 1,1
		board.redPieceAt 1,3
		
		when:
		def moves = blackPiece.getJumpMoves(board, blackLocation)
		
		then:
		TestHelpers.executeSingleMove(moves)
		TestHelpers.blackJumpsAllRedsTo(board, blackLocation, new Coordinate(2,4))
	}
	
	def "kings can jump backwards then forwards"() {
		setup:
		Coordinate blackLocation = new Coordinate(2,4)
		board.blackPieceAt blackLocation
		board.redPieceAt 1,1
		board.redPieceAt 1,3
		
		when:
		def moves = blackPiece.getJumpMoves(board, blackLocation)
		
		then:
		TestHelpers.executeSingleMove(moves)
		TestHelpers.blackJumpsAllRedsTo(board, blackLocation, new Coordinate(2,0))
	}
}
