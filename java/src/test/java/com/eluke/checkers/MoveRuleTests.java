package com.eluke.checkers;

import static org.assertj.core.api.Assertions.assertThat;

import java.util.Collection;
import java.util.Optional;

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
		board.placePieceAt(BlackPiece(), new Coordinate(0,2));
		board.placePieceAt(RedPiece(), new Coordinate(1,1));
		Collection<Move> moves = rules.getMovesForColor(Color.Black, board);

		assertThat(moves.size()).isEqualTo(1);
		moves.iterator().next().execute();
		assertThat(board.getPiecesForColor(Color.Red)).isEmpty();
	}

	@Test
	public void ifCapturingMovesAreAvailableTheyMustBePickedForMultiJumps() {
		board.placePieceAt(BlackPiece(), new Coordinate(0,2));
		board.placePieceAt(RedPiece(), new Coordinate(1,3));
		board.placePieceAt(RedPiece(), new Coordinate(3,5));

		Collection<Move> moves = rules.getMovesForColor(Color.Black, board);

		assertThat(moves.size()).isEqualTo(1);
		moves.iterator().next().execute();

		assertThat(board.getPiecesForColor(Color.Red)).isEmpty();
		Optional<Piece> newBlackPiece = board.getPieceAt(new Coordinate(4,6));
		assertThat(newBlackPiece).isPresent();
		assertThat(newBlackPiece.get().color()).isEqualTo(Color.Black);
	}

	private SinglePiece BlackPiece() {
		return new SinglePiece(Color.Black, SinglePiece.FORWARD);
	}

	private SinglePiece RedPiece() {
		return new SinglePiece(Color.Red, SinglePiece.REVERSE);
	}
}
