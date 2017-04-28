module TestHelpers
	def black_piece_at(row,col)
        @board[Coordinate.new(row,col)] = blackPiece
        return @board[Coordinate.new(row,col)]
	end
	
	def red_piece_at(row,col)
        @board[Coordinate.new(row,col)] = redPiece
        return @board[Coordinate.new(row,col)]
	end

	def blackPiece()
		return SinglePiece.new(:Black, SinglePiece::FORWARD)
	end
	def redPiece()
		return SinglePiece.new(:Red, SinglePiece::BACKWARDS)
	end
	
	def assert_no_red_pieces()
		expect(@board.get_pieces_for_color(:Red).length).to eq(0)
	end
	
    def assert_no_piece_at(row, col)
        piece = @board[Coordinate.new(row,col)]
        expect(piece).to be_nil
	end

	def assert_piece_is_black(row,col)
        piece = @board[Coordinate.new(row,col)]
        expect(piece.color).to eq(:Black)
	end
	
	def assert_piece_is_red(row,col)
        piece = @board[Coordinate.new(row,col)]
        expect(piece.color).to eq(:Red)
	end
	
	def assert_piece_is_king(row,col)
        piece = @board[Coordinate.new(row,col)]
        expect(piece.can_be_kinged?).to eq(false)
	end
end
