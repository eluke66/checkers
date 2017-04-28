class ConsolePlayer
	def initialize(name)
		@name = name
	end
	def select_move(moves, board)
		moves.each_with_index do |move,index| 
			puts "%d: %s" % [index, move]
		end
		while (true) do
			puts "Enter choice: "
			begin
				choice = gets
				if choice.to_i >= moves.length then
					puts "Invalid choice - too large"
					redo
				end
				move = moves[choice.to_i]
				return move
			rescue => exception
				puts "Invalid choice " + exception.to_s
			end
		end 
	end
	def to_s
		return @name
	end
end

class ConsoleEventHandler
	def playerTurn(whichTurn, currentPlayer, board, color)
		puts "Turn %d: Player %s (%s)\n%s" % [whichTurn, currentPlayer, color, board]
	end
	
	def gameFinished(whichTurn, winningPlayer)
		puts "Player %s wins on turn %d" % [winningPlayer, whichTurn]
	end
end
