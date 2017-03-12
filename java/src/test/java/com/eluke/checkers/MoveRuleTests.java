package com.eluke.checkers;

import java.util.Collection;
import java.util.Optional;

import static org.assertj.core.api.Assertions.assertThat;

import org.junit.Before;
import org.junit.Test;

public class MoveRuleTests {
	private Board board;
	private MoveRules rules;
	
	@Before
	public void setup() {
		board = new Board();
		rules = new MoveRules();
	}
	
	@Test
	public void ifCapturingMovesAreAvailableTheyMustBePickedForSimple() {
		board.placePieceAt(blackPiece(), new Coordinate(0,2));
		board.placePieceAt(redPiece(), new Coordinate(1,1));
		Collection<Move> moves = rules.getMovesForColor(Color.Black, board);
		
		assertThat(moves.size()).isEqualTo(1);
		moves.iterator().next().execute();
		assertThat(board.getPiecesForColor(Color.Red)).isEmpty();
	}
	
	@Test
	public void ifCapturingMovesAreAvailableTheyMustBePickedForMultiJumps() {
		board.placePieceAt(blackPiece(), new Coordinate(0,2));
		board.placePieceAt(redPiece(), new Coordinate(1,3));
		board.placePieceAt(redPiece(), new Coordinate(3,5));
		
		Collection<Move> moves = rules.getMovesForColor(Color.Black, board);
		
		assertThat(moves.size()).isEqualTo(1);
		moves.iterator().next().execute();
		
		assertThat(board.getPiecesForColor(Color.Red)).isEmpty();
		Optional<Piece> newBlackPiece = board.getPieceAt(new Coordinate(4,6));
		assertThat(newBlackPiece).isPresent();
		assertThat(newBlackPiece.get().color()).isEqualTo(Color.Black);
	}

	private SinglePiece blackPiece() {
		return new SinglePiece(Color.Black, SinglePiece.FORWARD);
	}
	
	private SinglePiece redPiece() { 
		return new SinglePiece(Color.Red, SinglePiece.REVERSE);
	}
	
	private final void printBoard() {
		System.err.println("Board:\n" + board);
	}
}
