
require_relative 'Board'
require_relative 'Coordinate'
require_relative 'SinglePiece'
require "TestHelpers"

RSpec.describe SinglePiece do
	include TestHelpers

	before :each do
        @board = Board.new
	end

	it "cannot jump when blocked" do
        blackPiece = black_piece_at(0,0)
        red_piece_at(1,1)
        red_piece_at(2,2)
        
        moves = blackPiece.get_jump_moves(@board)
        expect(moves.length).to eq(0)
	end
	
	it "cannot jump its own man" do
        blackPiece = black_piece_at(0,0)
        black_piece_at(1,1)
        
        moves = blackPiece.get_jump_moves(@board)
        expect(moves.length).to eq(0)
	end
	
	it "has two forward moves" do
        blackPiece = black_piece_at(0,2)
        
        moves = blackPiece.get_simple_moves(@board)
        expect(moves.length).to eq(2)
        expect(moves.map {|m| m.moveTo}).to include(Coordinate.new(1,1), Coordinate.new(1,3))
	end
	
	it "cannot move off the board or when blocked" do
        blackPiece = black_piece_at(0,0)
        red_piece_at(1,1)
        
        moves = blackPiece.get_simple_moves(@board)
        expect(moves.length).to eq(0)
	end
	
	it "can jump once at that piece is removed" do
        blackPiece = black_piece_at(0,0)
        red_piece_at(1,1)
        
        moves = blackPiece.get_jump_moves(@board)
        expect(moves.length).to eq(1)
        
        moves[0].execute()
        
        assert_no_red_pieces()
        assert_no_piece_at(0,0)
        assert_piece_is_black(2,2)
	end
	
	it "can jump more than once and those pieces are removed" do
        blackPiece = black_piece_at(0,0)
        red_piece_at(1,1)
        red_piece_at(3,3)
        
        moves = blackPiece.get_jump_moves(@board)
        expect(moves.length).to eq(1)
        
        moves[0].execute()
        
        assert_no_red_pieces()
        assert_no_piece_at(0,0)
        assert_piece_is_black(4,4)
	end
	
	it "can have two forward single jumps" do
        blackPiece = black_piece_at(0,2)
        red_piece_at(1,1)
        red_piece_at(1,3)
        
        moves = blackPiece.get_jump_moves(@board)
        expect(moves.length).to eq(2)
        
        expect(moves.map {|m| m.moveTo}).to include(Coordinate.new(2,0), Coordinate.new(2,4))
	end
	
	it "can have multiple forward multi-jumps" do
        blackPiece = black_piece_at(0,2)
        red_piece_at(1,1)
        red_piece_at(1,3)
        red_piece_at(3,5)

        moves = blackPiece.get_jump_moves(@board)
        expect(moves.length).to eq(2)
        
        expect(moves.map {|m| m.moveTo}).to include(Coordinate.new(2,0), Coordinate.new(4,6))
	end
	
	it "gets kinged when it moves into the back row" do
        blackPiece = black_piece_at(@board.size-2,0)
        
        moves = blackPiece.get_simple_moves(@board)
        expect(moves.length).to eq(1)
        
        moves[0].execute()
        
        assert_piece_is_black(@board.size-1,1)
        assert_piece_is_king(@board.size-1,1)
	end
	
	it "gets kinged when it jumps into the back row" do
        blackPiece = black_piece_at(@board.size-3,1)
        red_piece_at(@board.size-2,2)
        
        moves = blackPiece.get_jump_moves(@board)
        expect(moves.length).to eq(1)
        
        moves[0].execute()
        
        assert_no_red_pieces()
        assert_piece_is_black(@board.size-1,3)
        assert_piece_is_king(@board.size-1,3)
	end
end
