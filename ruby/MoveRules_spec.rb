
require 'MoveRules'
require 'Board'
require 'Coordinate'
require 'SinglePiece'
require "TestHelpers"

RSpec.describe MoveRules do
	include TestHelpers
	
	before :each do
        @board = Board.new
        @rules = MoveRules.new
	end

	it "captures moves when they are available" do
		black_piece_at(0,2)
        red_piece_at(1,1)
        
        moves = @rules.get_moves_for_color(:Black, @board)

		expect(moves.length).to eq(1)
        moves[0].execute()
        
        assert_no_red_pieces()
	end
	
	it "captures moves for multi jumps when they are available" do
		black_piece_at(0,2)
        red_piece_at(1,3)
        red_piece_at(3,5)
        
        moves = @rules.get_moves_for_color(:Black, @board)
        
		expect(moves.length).to eq(1)
        moves[0].execute
        
        assert_no_red_pieces()
	end
end

