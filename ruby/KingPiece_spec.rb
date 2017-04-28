
require_relative 'Board'
require_relative 'Coordinate'
require_relative 'KingPiece'
require "TestHelpers"

RSpec.describe KingPiece do
	include TestHelpers

	before :each do
        @board = Board.new
	end

	it "can move forward and backwards" do
        blackPiece = black_piece_at(2,2)
        
        moves = blackPiece.get_simple_moves(@board)
        expect(moves.length).to eq(4)
        
        expect(moves.map {|m| m.moveTo}).to include(Coordinate.new(1,1), Coordinate.new(1,3),Coordinate.new(3,1), Coordinate.new(3,3))
	end
	
	it "cannot jump when blocked" do
        blackPiece = black_piece_at(0,0)
        red_piece_at(1,1)
        red_piece_at(2,2)
        
        moves = blackPiece.get_jump_moves(@board)
        expect(moves.length).to eq(0)
	end
	
	it "can jump forward once" do
        blackPiece = black_piece_at(0,0)
        red_piece_at(1,1)

        moves = blackPiece.get_jump_moves(@board)
        expect(moves.length).to eq(1)
        moves[0].execute()

		assert_no_red_pieces()
		assert_no_piece_at(0,0)
		assert_piece_is_black(2,2)
	end
	
	it "can jump backwards once" do
        blackPiece = black_piece_at(2,2)
        red_piece_at(1,1)

        moves = blackPiece.get_jump_moves(@board)
        expect(moves.length).to eq(1)
        moves[0].execute()

		assert_no_red_pieces()
		assert_no_piece_at(2,2)
		assert_piece_is_black(0,0)
	end
	
	it "can jump forwards then backwards" do
        blackPiece = black_piece_at(2,0)
        red_piece_at(1,1)
        red_piece_at(1,3)

        moves = blackPiece.get_jump_moves(@board)
        expect(moves.length).to eq(1)
        moves[0].execute()

		assert_no_red_pieces()
		assert_no_piece_at(2,0)
		assert_piece_is_black(2,4)
	end
	
	it "can jump backwards then forwards" do
        blackPiece = black_piece_at(2,4)
        red_piece_at(1,1)
        red_piece_at(1,3)

        moves = blackPiece.get_jump_moves(@board)
        expect(moves.length).to eq(1)
        moves[0].execute()

		assert_no_red_pieces()
		assert_no_piece_at(2,4)
		assert_piece_is_black(2,0)
	end
	
	def blackPiece()
		return KingPiece.new(:Black)
	end
	def redPiece()
		return KingPiece.new(:Red)
	end
	
end
