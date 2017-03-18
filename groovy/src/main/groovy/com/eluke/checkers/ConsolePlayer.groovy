package com.eluke.checkers

class ConsolePlayer implements Player {

	@Override
	public Move selectMove(Collection<Move> moves, Board board) {
		println "Select a move: "

		moves.eachWithIndex { move, index -> println " ${index}: $move" }

		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))
		while (true) {
			println "Enter the number of choice: "
			String input = null
			try {
				input = reader.readLine()
				int choice = Integer.parseInt(input)
				if (choice < 0 || choice >= moves.size()) {
					System.err.println "$choice must be between 0 and ${moves.size()}"
					continue
				}
				return moves[choice]
			} catch (NumberFormatException e) {
				println "$input is not a number. Try again"
				continue
			} catch (IOException e) {
				throw new RuntimeException("Unable to read player input", e)
			}
		}
	}
}
