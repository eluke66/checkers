package com.eluke.checkers

import com.eluke.checkers.Coordinate
import com.eluke.checkers.Piece

class TestHelpers {
	static void setupBoard(Closure redPieceCreator, Piece blackPiece) {
		Board.getMetaClass().redPieceAt { row, col ->
			def redPiece = redPieceCreator.call()
			placePieceAt(redPiece, new Coordinate(row,col))
			return redPiece
		}
		Board.getMetaClass().blackPieceAt { coord ->
			placePieceAt(blackPiece, coord)
		}
	}
	
	static void blackJumpsAllRedsTo(Board board, Coordinate from, Coordinate to) {
		board.getPiecesForColor(Color.Red) == []
		board.getPieceAt(from).present == false
		board.getPieceAt(to).get().color == Color.Black
	}
	
	static void executeSingleMove(Collection<Move> moves) {
		assert moves.size() == 1
		moves[0].execute()
	}
}
