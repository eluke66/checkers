package com.eluke.checkers;

import static org.assertj.core.api.Assertions.assertThat;

import java.util.Collection;
import java.util.Optional;

import org.junit.Before;
import org.junit.Test;

public class KingPieceTests {
	private Board board;
	private Piece blackPiece;

	@Before
	public void setup() {
		board = new Board();
		blackPiece = blackPiece();
	}

	@Test
	public void kingsCanMoveForwardAndBackwards() {
		Coordinate blackLocation = new Coordinate(2, 2);
		board.placePieceAt(blackPiece, blackLocation);

		Collection<Move> moves = blackPiece.getSimpleMoves(board, blackLocation);
		assertThat(moves).containsOnly(
				Move.simpleMove(board, blackPiece, blackLocation, new Coordinate(1,1)),
				Move.simpleMove(board, blackPiece, blackLocation, new Coordinate(1,3)),
				Move.simpleMove(board, blackPiece, blackLocation, new Coordinate(3,1)),
				Move.simpleMove(board, blackPiece, blackLocation, new Coordinate(3,3)));
	}

	@Test
	public void kingsCannotJumpWhenBlocked() {
		Coordinate blackLocation = new Coordinate(0, 0);
		board.placePieceAt(blackPiece, blackLocation);
		board.placePieceAt(redPiece(), new Coordinate(1,1));
		board.placePieceAt(redPiece(), new Coordinate(2,2));

		Collection<Move> moves = blackPiece.getJumpMoves(board, blackLocation);
		assertThat(moves).isEmpty();
	}

	@Test
	public void kingsCanJumpForwardOnce() {
		Coordinate blackLocation = new Coordinate(0, 0);
		board.placePieceAt(blackPiece, blackLocation);
		board.placePieceAt(redPiece(), new Coordinate(1,1));

		Collection<Move> moves = blackPiece.getJumpMoves(board, blackLocation);
		assertThat(moves.size()).isEqualTo(1);
		moves.iterator().next().execute();

		assertThat(board.getPiecesForColor(Color.Red)).isEmpty();
		assertThat(board.getPieceAt(new Coordinate(1,1))).isNotPresent();
		assertThat(board.getPieceAt(blackLocation)).isNotPresent();
		Optional<Piece> newBlackPiece = board.getPieceAt(new Coordinate(2,2));
		assertThat(newBlackPiece).isPresent();
		assertThat(newBlackPiece.get().color()).isEqualTo(Color.Black);
	}

	@Test
	public void kingsCanJumpBackwardsOnce() {
		Coordinate blackLocation = new Coordinate(2, 2);
		board.placePieceAt(blackPiece, blackLocation);
		board.placePieceAt(redPiece(), new Coordinate(1,1));

		Collection<Move> moves = blackPiece.getJumpMoves(board, blackLocation);
		assertThat(moves.size()).isEqualTo(1);
		moves.iterator().next().execute();

		assertThat(board.getPiecesForColor(Color.Red)).isEmpty();
		assertThat(board.getPieceAt(new Coordinate(1,1))).isNotPresent();
		assertThat(board.getPieceAt(blackLocation)).isNotPresent();
		Optional<Piece> newBlackPiece = board.getPieceAt(new Coordinate(0,0));
		assertThat(newBlackPiece).isPresent();
		assertThat(newBlackPiece.get().color()).isEqualTo(Color.Black);
	}

	@Test
	public void kingsCanJumpForwardsThenBackwards() {
		Coordinate blackLocation = new Coordinate(2, 0);
		board.placePieceAt(blackPiece, blackLocation);
		board.placePieceAt(redPiece(), new Coordinate(1,1));
		board.placePieceAt(redPiece(), new Coordinate(1,3));
		Collection<Move> moves = blackPiece.getJumpMoves(board, blackLocation);
		assertThat(moves.size()).isEqualTo(1);
		moves.iterator().next().execute();

		assertThat(board.getPiecesForColor(Color.Red)).isEmpty();
		assertThat(board.getPieceAt(new Coordinate(1,1))).isNotPresent();
		assertThat(board.getPieceAt(blackLocation)).isNotPresent();
		Optional<Piece> newBlackPiece = board.getPieceAt(new Coordinate(2,4));
		assertThat(newBlackPiece).isPresent();
		assertThat(newBlackPiece.get().color()).isEqualTo(Color.Black);
	}

	@Test
	public void kingsCanJumpBackwardsThenForwards() {
		Coordinate blackLocation = new Coordinate(2,4);
		board.placePieceAt(blackPiece, blackLocation);
		board.placePieceAt(redPiece(), new Coordinate(1,1));
		board.placePieceAt(redPiece(), new Coordinate(1,3));
		Collection<Move> moves = blackPiece.getJumpMoves(board, blackLocation);
		assertThat(moves.size()).isEqualTo(1);
		moves.iterator().next().execute();

		assertThat(board.getPiecesForColor(Color.Red)).isEmpty();
		assertThat(board.getPieceAt(new Coordinate(1,1))).isNotPresent();
		assertThat(board.getPieceAt(blackLocation)).isNotPresent();
		Optional<Piece> newBlackPiece = board.getPieceAt(new Coordinate(2,0));
		assertThat(newBlackPiece).isPresent();
		assertThat(newBlackPiece.get().color()).isEqualTo(Color.Black);
	}

	private KingPiece blackPiece() {
		return new KingPiece(Color.Black);
	}

	private KingPiece redPiece() {
		return new KingPiece(Color.Red);
	}

}
