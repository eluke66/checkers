package com.eluke.checkers;

import static org.assertj.core.api.Assertions.assertThat;

import java.util.Collection;
import java.util.Optional;

import org.junit.Before;
import org.junit.Test;

public class SinglePieceTests {
	private Board board;
	private Piece blackPiece;

	@Before
	public void setup() {
		board = new Board();
		blackPiece = blackPiece();
	}

	@Test
	public void singlePiecesCannotJumpWhenBlocked() {
		Coordinate blackLocation = new Coordinate(0, 0);
		board.placePieceAt(blackPiece, blackLocation);
		board.placePieceAt(redPiece(), new Coordinate(1,1));
		board.placePieceAt(redPiece(), new Coordinate(2,2));

		Collection<Move> moves = blackPiece.getJumpMoves(board, blackLocation);
		assertThat(moves).isEmpty();
	}

	@Test
	public void singlePiecesCannotJumpItsOwnMan() {
		Coordinate blackLocation = new Coordinate(0, 0);
		board.placePieceAt(blackPiece, blackLocation);
		board.placePieceAt(blackPiece(), new Coordinate(1,1));

		Collection<Move> moves = blackPiece.getJumpMoves(board, blackLocation);
		assertThat(moves).isEmpty();
	}

	@Test
	public void singlePiecesHaveTwoForwardMoves() {
		Coordinate blackLocation = new Coordinate(0, 2);
		board.placePieceAt(blackPiece, blackLocation);
		Collection<Move> moves = blackPiece.getSimpleMoves(board, blackLocation);
		assertThat(moves).containsOnly(
				Move.simpleMove(board, blackPiece, blackLocation, new Coordinate(1,1)),
				Move.simpleMove(board, blackPiece, blackLocation, new Coordinate(1,3)));


		Piece redPiece = redPiece();
		Coordinate redLocation = new Coordinate(4, 2);
		board.placePieceAt(redPiece, redLocation);
		moves = redPiece.getSimpleMoves(board, redLocation);
		assertThat(moves).containsOnly(
				Move.simpleMove(board, redPiece, redLocation, new Coordinate(3,1)),
				Move.simpleMove(board, redPiece, redLocation, new Coordinate(3,3)));
	}

	@Test
	public void singlePiecesCannotJumpOffTheBoardOrWhenBlocked() {
		Piece redPiece = redPiece();
		Coordinate blackLocation = new Coordinate(0, 0);

		board.placePieceAt(blackPiece, blackLocation);
		board.placePieceAt(redPiece, new Coordinate(1,1));
		Collection<Move> moves = blackPiece.getSimpleMoves(board, blackLocation);
		assertThat(moves).isEmpty();
	}

	@Test
	public void singlePiecesCanJumpOnceAndThatPieceIsRemoved() {
		Piece redPiece = redPiece();
		Coordinate blackLocation = new Coordinate(0, 0);

		board.placePieceAt(blackPiece, blackLocation);
		Coordinate redLocation = new Coordinate(1,1);
		board.placePieceAt(redPiece, redLocation);
		Collection<Move> moves = blackPiece.getJumpMoves(board, blackLocation);
		Move jumpMove = Move.jumpMove(board, blackPiece, blackLocation, redLocation);
		org.assertj.core.api.Assertions.assertThat(moves).containsOnly(jumpMove);

		jumpMove.execute();
		assertThat(board.getPiecesForColor(Color.Red)).isEmpty();
		assertThat(board.getPieceAt(redLocation)).isNotPresent();
		assertThat(board.getPieceAt(blackLocation)).isNotPresent();
		Optional<Piece> newBlackPiece = board.getPieceAt(new Coordinate(2,2));
		assertThat(newBlackPiece).isPresent();
		assertThat(newBlackPiece.get().color()).isEqualTo(Color.Black);
	}

	@Test
	public void singlePiecesCanJumpMoreThanOnceAndThosePiecesAreRemoved() {
		Piece redPiece1 = redPiece();
		Piece redPiece2 = redPiece();
		Coordinate blackLocation = new Coordinate(0, 0);

		board.placePieceAt(blackPiece, blackLocation);
		board.placePieceAt(redPiece1, new Coordinate(1,1));
		board.placePieceAt(redPiece2, new Coordinate(3,3));
		Collection<Move> moves = blackPiece.getJumpMoves(board, blackLocation);
		assertThat(moves.size()).isEqualTo(1);

		moves.iterator().next().execute();
		assertThat(board.getPiecesForColor(Color.Red)).isEmpty();
		Optional<Piece> newBlackPiece = board.getPieceAt(new Coordinate(4,4));
		assertThat(newBlackPiece).isPresent();
		assertThat(newBlackPiece.get().color()).isEqualTo(Color.Black);

	}

	@Test
	public void singlePiecesCanHaveTwoForwardSingleJumps() {
		Piece redPiece1 = redPiece();
		Piece redPiece2 = redPiece();
		Coordinate blackLocation = new Coordinate(0, 2);

		board.placePieceAt(blackPiece, blackLocation);
		Coordinate redLocation1 = new Coordinate(1,1);
		board.placePieceAt(redPiece1, redLocation1);
		Coordinate redLocation2 = new Coordinate(1,3);
		board.placePieceAt(redPiece2, redLocation2);
		Collection<Move> moves = blackPiece.getJumpMoves(board, blackLocation);
		assertThat(moves.size()).isEqualTo(2);
		assertThat(moves)
			.extractingResultOf("getNextPosition")
			.contains(new Coordinate(2,0), new Coordinate(2,4));

	}

	@Test
	public void singlePiecesCanHaveMultipleForwardMultiJumps() {
		Piece redPiece1 = redPiece();
		Piece redPiece2 = redPiece();
		Piece redPiece3 = redPiece();
		Coordinate blackLocation = new Coordinate(0, 2);
		board.placePieceAt(blackPiece, blackLocation);
		Coordinate redLocation1 = new Coordinate(1,1);
		board.placePieceAt(redPiece1, redLocation1);
		Coordinate redLocation2 = new Coordinate(1,3);
		board.placePieceAt(redPiece2, redLocation2);
		Coordinate redLocation3 = new Coordinate(3,5);
		board.placePieceAt(redPiece3, redLocation3);

		Collection<Move> moves = blackPiece.getJumpMoves(board, blackLocation);
		assertThat(moves.size()).isEqualTo(2);
		assertThat(moves)
			.extractingResultOf("getNextPosition")
			.contains(new Coordinate(2,0), new Coordinate(4,6));
	}

	@Test
	public void whenSinglePieceMovesIntoTheBackRowItIsKinged() {
		Coordinate blackLocation = new Coordinate(board.size()-2, 0);
		board.placePieceAt(blackPiece, blackLocation);
		Collection<Move> moves = blackPiece.getSimpleMoves(board, blackLocation);
		assertThat(moves.size()).isEqualTo(1);

		Move move = moves.iterator().next();
		move.execute();

		Piece piece = board.getPieceAt(new Coordinate(board.size()-1, 1)).get();
		assertThat(piece).isNotNull();
		assertThat(piece.color()).isEqualTo(Color.Black);
		assertThat(piece.canBeKinged()).isFalse();
	}

	@Test
	public void whenSinglePieceJumpsIntoTheBackRowItIsKinged() {
		Coordinate blackLocation = new Coordinate(board.size()-3, 1);
		board.placePieceAt(blackPiece, blackLocation);
		board.placePieceAt(redPiece(), new Coordinate(board.size()-2,2));
		Collection<Move> moves = blackPiece.getJumpMoves(board, blackLocation);
		assertThat(moves.size()).isEqualTo(1);

		Move move = moves.iterator().next();
		move.execute();

		Piece piece = board.getPieceAt(new Coordinate(board.size()-1, 3)).get();
		assertThat(piece).isNotNull();
		assertThat(piece.color()).isEqualTo(Color.Black);
		assertThat(piece.canBeKinged()).isFalse();
	}

	private SinglePiece blackPiece() {
		return new SinglePiece(Color.Black, SinglePiece.FORWARD);
	}

	private SinglePiece redPiece() {
		return new SinglePiece(Color.Red, SinglePiece.REVERSE);
	}
}
