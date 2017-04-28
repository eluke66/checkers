#  Coordinate.rb
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


class Coordinate
	attr_reader :row,:col
	
	def initialize(row,col)
		@row,@col = row,col
	end
	
	def Coordinate.extending(c1, c2)
		newRow = (c2.row-c1.row) + c2.row
        newCol = (c2.col-c1.col) + c2.col
        return Coordinate.new(newRow, newCol)
	end
	
	def to_s
		return "(" + @row.to_s + "," + @col.to_s + ")"
	end
	
	def ==(other)
		return @row==other.row && @col==other.col
	end
end


