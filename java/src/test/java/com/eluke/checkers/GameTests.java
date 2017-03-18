package com.eluke.checkers;

import static org.assertj.core.api.Assertions.assertThat;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.ArgumentMatchers.eq;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.util.Arrays;
import java.util.Collection;
import java.util.Optional;

import org.assertj.core.util.Lists;
import org.junit.Test;

import com.eluke.checkers.Board.PlacedPiece;

public class GameTests {

	@Test
	public void eachPlayerStartsWith12Pieces() {
		Board board = new Board();
		Game.putPiecesOnTheBoard(board);

		Collection<PlacedPiece> piecesForBlack = board.getPiecesForColor(Color.Black);
		org.assertj.core.api.Assertions.assertThat(piecesForBlack).hasSize(12);

		Collection<PlacedPiece> piecesForRed = board.getPiecesForColor(Color.Red);
		org.assertj.core.api.Assertions.assertThat(piecesForRed).hasSize(12);
	}
	@Test
	public void closestLeftSquareToEachPlayerStartsWithAPiece() {
		Board board = new Board();
		Game.putPiecesOnTheBoard(board);

		Optional<Piece> blackPiece = board.getPieceAt(new Coordinate(0,0));
		org.assertj.core.api.Assertions.assertThat(blackPiece.isPresent()).isTrue();
		org.assertj.core.api.Assertions.assertThat(blackPiece.get()).as("Black is at 0,0").isNotNull();

		Optional<Piece> redPiece = board.getPieceAt(new Coordinate(board.size()-1,board.size()-1));
		org.assertj.core.api.Assertions.assertThat(redPiece.isPresent()).isTrue();
		org.assertj.core.api.Assertions.assertThat(redPiece.get()).as("Red is at 7,7").isNotNull();
	}

	@Test
	public void boardIs8x8() {
		Board board = new Board();

		org.assertj.core.api.Assertions.assertThat(board.size()).as("Board size").isEqualTo(8);
	}

	@Test
	public void blackMovesFirst() {
		Player player1 = mock(Player.class);
		Player player2 = mock(Player.class);
		MoveRules rules = mock(MoveRules.class);
		Game game = new Game(player1, player2, rules);

		when(rules.getMovesForColor(eq(Color.Black), any(Board.class))).thenReturn(Lists.emptyList());
		game.play();

		verify(rules).getMovesForColor(eq(Color.Black), any(Board.class));
	}

	@Test
	public void redMovesAfterBlack() {
		Player player1 = mock(Player.class);
		Player player2 = mock(Player.class);
		MoveRules rules = mock(MoveRules.class);
		Game game = new Game(player1, player2, rules);

		Move simpleMove = Move.simpleMove(game.board, BlackPiece(), new Coordinate(2,0), new Coordinate(3,1));
		Collection<Move> moves = Arrays.asList(simpleMove);
		when(rules.getMovesForColor(Color.Black, game.board)).thenReturn(moves);
		when(player1.selectMove(moves, game.board)).thenReturn(simpleMove);
		when(rules.getMovesForColor(Color.Red, game.board)).thenReturn(Lists.emptyList());
		Player winner = game.play();

		verify(rules).getMovesForColor(eq(Color.Black), any(Board.class));
		verify(rules).getMovesForColor(eq(Color.Red), any(Board.class));

		assertThat(winner).isEqualTo(player1);
	}

	@Test
	public void whenAPlayerCannotMoveThenOtherPlayerWins() {
		Player player1 = mock(Player.class);
		Player player2 = mock(Player.class);
		MoveRules rules = mock(MoveRules.class);

		Game game = new Game(player1, player2, rules);
		when(rules.getMovesForColor(eq(Color.Black), any(Board.class))).thenReturn(Lists.emptyList());

		Player winner = game.play();
		assertThat(winner).isEqualTo(player2);
	}

	private SinglePiece BlackPiece() {
		return new SinglePiece(Color.Black, SinglePiece.FORWARD);
	}

}
