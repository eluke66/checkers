package com.eluke.checkers;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Collection;

public class ConsolePlayer implements Player {

	@Override
	public Move selectMove(final Collection<Move> moves, final Board board) {
		System.out.println("Select a move: ");

		Move[] movesAsArray = moves.toArray(new Move[0]);
		for (int i = 0; i < movesAsArray.length; i++) {
			System.out.println("  " + i + ": " + movesAsArray[i]);
		}

		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		while (true) {
			System.out.print("Enter the number of choice: ");
			String input = null;
			try {
				input = reader.readLine();
				int choice = Integer.parseInt(input);
				if (choice < 0 || choice >= movesAsArray.length) {
					System.err.println(choice + " must be between 0 and " + (movesAsArray.length-1));
					continue;
				}
				return movesAsArray[choice];
			} catch (NumberFormatException e) {
				System.err.println(input + " is not a number. Try again");
				continue;
			} catch (IOException e) {
				throw new RuntimeException("Unable to read player input", e);
			}
		}
	}

}
