require "benchmark"
require "Game"
require "ConsolePlayer"

class RandomOptionPlayer 
	def initialize(name)
		@name = name
	end
	def select_move(moves, board)
		return moves.sample
	end
	def to_s
		return @name
	end
end

def profile(numRuns)
    totalTime = 0
    
    player1 = RandomOptionPlayer.new("player 1")
    player2 = RandomOptionPlayer.new("player 2")
    winsPerPlayer = {player1 => 0, player2 => 0}
    (1..numRuns).each do |run|
		game = Game.new(player1, player2)
		totalTime += Benchmark.realtime { winsPerPlayer[game.play()] += 1 }
	end
    msPerGame = (totalTime*1000) / numRuns
    puts "Total time is %0.2f sec to play %d games, or %0.2f ms/game" % [totalTime, numRuns, msPerGame]
    puts "Wins per player: "
    winsPerPlayer.each do |p,v| 
		puts p.to_s + ": " + v.to_s
    end
end

def playInteractive
	Game.new(ConsolePlayer.new("Player 1"), ConsolePlayer.new("Player 2"), eventHandler: ConsoleEventHandler.new).play
end

if ARGV.length > 0 then
	profile(ARGV[0].to_i)
else
	playInteractive # TODO
end
