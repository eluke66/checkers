#  Board.rb
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

class Numeric 
	def even?
		return self % 2 == 0
	end
end


class Board
	@@DEFAULT_SIZE = 8
	
	
	class PlacedPiece
		attr_reader :piece, :coordinate
		
		def color
			return @piece.color
		end
		
		def initialize(piece,coordinate)
			@piece, @coordinate = piece, coordinate
		end
		
		def get_jump_moves(board)
			return @piece.get_jump_moves(@coordinate, board)
		end
		
		def get_simple_moves(board)
			return @piece.get_simple_moves(@coordinate, board)
		end
		
		def can_be_kinged?
			return @piece.can_be_kinged?
		end
		
		def to_s
			return @piece.to_s + "@" + @coordinate.to_s
		end
	end

	def initialize(size=@@DEFAULT_SIZE)
		@squares = Array.new(size) { Array.new(size) }
	end
	
	def size
		return @squares.length
	end
	
	def valid_position?(coordinate)
		return coordinate.row >= 0 && coordinate.col >= 0 &&
			coordinate.row < @squares.length && coordinate.col < @squares.length &&
            usable_square?(coordinate.row, coordinate.col)
	end
    
	def usable_square?(row,col)
		return (row.even? && col.even?) || (!row.even? && !col.even?)
	end
	
	def get_pieces_for_color(color)
        pieces = []
		@squares.each do |row|
			pieces.concat(row.find_all { |space| space != nil && space.color == color })
		end
        return pieces
	end
    
	def final_row_for_piece?(piece, coordinate)
		return (piece.color == :Red && coordinate.row == 0) ||
			(piece.color == :Black && coordinate.row == (self.size()-1))
	end
	
	# Lookup	
	def [](coordinate)
		return @squares[coordinate.row][coordinate.col]
	end
	
	# Assign
	def []=(coordinate, piece)
		if piece.is_a? PlacedPiece
            placed = piece
        else
            placed = PlacedPiece.new(piece,coordinate)
		end
        @squares[coordinate.row][coordinate.col] = placed
        return placed
	end
    
    def remove(coordinate)
		@squares[coordinate.row][coordinate.col] = nil
    end
    
    def to_s
		nums = (0..@squares.length-1)
		s = "  "
		s += nums.to_a.join("")
		s += "\n"
		nums.each { |row| 
			s += row.to_s + " "
			nums.each { |col|
				if !usable_square?(row,col) then
					s += "|"
				else
					p = @squares[row][col]
					if p == nil
						s += "_"
					elsif p.color == :Black
						if p.can_be_kinged?
							s += "b"
						else
							s += "B"
						end
					elsif p.color == :Red
						if p.can_be_kinged?
							s += "r"
						else
							s += "R"
						end
					else
						s += "?"
					end
				end
			}
			s += "\n"
		}
        s += "\n"
        return s
    end
    
	private :usable_square?
end


