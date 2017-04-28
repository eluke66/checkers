#  SinglePiece.rb
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

require_relative 'Piece'

class SinglePiece < Piece
	FORWARD = 1
	BACKWARDS = -1
	
	def initialize(color,direction)
		super(color)
		@direction = direction
		
		@get_following_coords = Proc.new do |c|
			[Coordinate.new(c.row+@direction, c.col+1), Coordinate.new(c.row+@direction, c.col-1)]
		end
	end
	
	def get_jump_moves(coordinate, board)
		MoveRules.get_jump_moves(board, self, coordinate, @get_following_coords)
	end
	
	def get_simple_moves(coordinate, board)
		MoveRules.get_simple_moves(board, self, coordinate, @get_following_coords)
	end
	
	def to_s
		return @color.to_s + " piece"
	end
	
	def can_be_kinged?
		return true
	end
end
