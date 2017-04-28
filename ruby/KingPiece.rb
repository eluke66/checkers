
require "Piece"

class KingPiece < Piece
	def initialize(color)
		super(color)
		
		@get_following_coords = Proc.new do |c|
			[Coordinate.new(c.row+1, c.col+1), Coordinate.new(c.row+1, c.col-1), 
			Coordinate.new(c.row-1, c.col+1), Coordinate.new(c.row-1, c.col-1)]
		end
	end
		
	def get_jump_moves(coordinate, board)
		MoveRules.get_jump_moves(board, self, coordinate, @get_following_coords)
	end
	
	def get_simple_moves(coordinate, board)
		MoveRules.get_simple_moves(board, self, coordinate, @get_following_coords)
	end
		
	def to_s
		return @color.to_s + " king"
	end
	
	def can_be_kinged?
		return false
	end
end

