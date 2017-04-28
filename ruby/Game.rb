#  Game.rb
#  
#  Copyright 2017 Bert <luke@luke-desktop>
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#  
#  
require "Coordinate"
require "Board"
require "SinglePiece"
require "MoveRules"

class Game
	NUM_PIECES_PER_PLAYER = 12
	attr_accessor :board
	
	def initialize(player1, player2, rules: MoveRules.new, eventHandler: nil)
		@player1 = [player1, :Black]
		@player2 = [player2, :Red]
		
		@rules, @eventHandler = rules, eventHandler
		@board = Board.new
	end
	
	def play
		Game.put_pieces_on_the_board(@board)
        whichPlayer = 0
        whichTurn = 0
        players = [@player1, @player2]
        while true
            currentPlayer,color = players[whichPlayer]
            @eventHandler.playerTurn(whichTurn, currentPlayer, @board, color) if @eventHandler != nil

            moves = @rules.get_moves_for_color(color, @board)
            break if moves.length == 0
            
            move = currentPlayer.select_move(moves, @board)
            move.execute()

            whichPlayer = (whichPlayer+1)%2
            whichTurn += 1
        end
        
        winningPlayer,_ = players[(whichPlayer+1)%2]
        @eventHandler.gameFinished(whichTurn, winningPlayer) if @eventHandler != nil

        return winningPlayer
	end
	
	def Game.put_pieces_on_the_board(board)
        piecesPerRow = board.size()/2
        rows = (Game::NUM_PIECES_PER_PLAYER / piecesPerRow).to_i
        
        if (piecesPerRow * rows != Game::NUM_PIECES_PER_PLAYER)
            raise "Cannot fit " + Game::NUM_PIECES_PER_PLAYER + " onto a board of size " + board.size()
        end
		
		# Black pieces
		(0..rows-1).each do |row|
            colStart = row % 2
            (colStart..board.size()-1).step(2) do |col|
				piece = SinglePiece.new(:Black, SinglePiece::FORWARD)
                board[Coordinate.new(row,col)] = piece
            end
		end
        
        # Red pieces
		(0..rows-1).each do |row|
			thisRow = board.size() - row - 1
            colStart = thisRow % 2
            (colStart..board.size()-1).step(2) do |col|
				piece = SinglePiece.new(:Red, SinglePiece::BACKWARDS)
                board[Coordinate.new(thisRow,col)] = piece
            end
		end
	end
	
end

