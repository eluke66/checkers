#  Move.rb
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

require "KingPiece"

class Move
	attr_reader :moveFrom, :moveTo
	
	def initialize(piece, board, moveFrom, moveTo)
		@piece, @board, @moveFrom, @moveTo = piece, board, moveFrom, moveTo
	end
	
	def Move.simple_move(board, piece, startCoord, endCoord)
        return SimpleMove.new(piece, board, startCoord, endCoord)
	end
    
    
	def Move.jump_move(board, piece, startCoord, endCoord)
        return JumpMove.new(piece, board, startCoord, endCoord, Coordinate.extending(startCoord, endCoord))
	end
    
    def Move.multi_jump_move(board, piece, startCoord, endCoord, move)
        return MultiJumpMove.new(piece, board, startCoord, endCoord, Coordinate.extending(startCoord, endCoord), move)
    end
    
	def move_and_king_piece(piece)
		@board[@moveTo] = piece
        if @board.final_row_for_piece?(piece, @moveTo) && piece.can_be_kinged?
            @board[@moveTo] = KingPiece.new(piece.color)
        end
	end
	
	def to_s
		@piece.to_s + " from " + moveFrom.to_s + " to " + moveTo.to_s
	end
end

class SimpleMove < Move
	def initialize(piece, board, moveFrom, moveTo)
		super(piece,board,moveFrom,moveTo)
	end
	
	def execute
		@board.remove(@moveFrom)
		move_and_king_piece(@piece)
	end
	
	def unExecute
		@board.remove(@moveTo)
		@board[@moveFrom] = @piece
	end

end

class JumpMove < Move
	def initialize(piece, board, moveFrom, existingPieceLocation, moveTo)
		super(piece,board,moveFrom,moveTo)
		@removed_piece = nil
		@existing_piece_location = existingPieceLocation
	end
	
	def execute
		if @removed_piece == nil
			@removed_piece = @board[@existing_piece_location]
			@board.remove(@moveFrom)
			move_and_king_piece(@piece)
			@board.remove(@existing_piece_location)
		else
			raise ("Trying to re-execute jump move " + self.to_s)
		end
	end
	
	def unExecute
		if @removed_piece != nil
			@board.remove(@moveTo)
			@board[@moveFrom] = @piece
			@board[@existing_piece_location] = @removed_piece
			@removed_piece = nil
		else
			raise ("TTrying to unexecute jump move that has not been executed " + @self)
		end
	end
	
	def to_s
		return super().to_s() + " jumping " + @existing_piece_location.to_s
	end
end

class MultiJumpMove < JumpMove
	def initialize(piece, board, moveFrom, existingPieceLocation, moveTo, move)
		super(piece,board,moveFrom,existingPieceLocation,moveTo)
		@previous_move = move
	end

	def execute
		@previous_move.execute
		super
	end
	
	def unExecute
		super
		@previous_move.unExecute()
	end
	
	def to_s
		return  @previous_move.to_s + "\n\t" + super().to_s()
	end
end
