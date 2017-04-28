
require_relative 'Board'
require_relative 'Game'
require "TestHelpers"

RSpec.describe Game do
	include TestHelpers

	before :each do
        @board = Board.new
	end
	
	it "starts players with 12 pieces" do
        Game.put_pieces_on_the_board(@board)

        expect(@board.get_pieces_for_color(:Black).length).to eq(12)
        expect(@board.get_pieces_for_color(:Red).length).to eq(12)
	end
	
	it "puts a piece on the closest left square for each player" do
        Game.put_pieces_on_the_board(@board)
		endSquare = @board.size-1
		
		assert_piece_is_black(0,0)
		assert_piece_is_red(endSquare,endSquare)
	end
	
	it "makes a board that is 8x8" do
		expect(@board.size).to eq(8)
	end
	
	it "moves black first" do
        player1 = double("Player")
        player2 = double("Player")
        rules = double("MoveRules")
        game = Game.new(player1, player2, rules)
        
        expect(rules).to receive(:get_moves_for_color).with(:Black, game.board).and_return([])
        
        game.play()
	end
	
	it "moves red after black" do
        player1 = double("Player1")
        player2 = double("Player2")
        rules = double("MoveRules")
        game = Game.new(player1, player2, rules)
        
        move = Move.simple_move(game.board, blackPiece, Coordinate.new(2,0), Coordinate.new(3,1))
        moves = [move]
        expect(rules).to receive(:get_moves_for_color).with(:Black, game.board).and_return(moves)
        expect(rules).to receive(:get_moves_for_color).with(:Red, game.board).and_return([])
        expect(player1).to receive(:select_move).with(moves, game.board).and_return(move)
        
        game.play()
	end
	
	it "makes a player a winner when the other has no moves" do
        player1 = double("Player1")
        player2 = double("Player2")
        rules = double("MoveRules")
        game = Game.new(player1, player2, rules)
        
        expect(rules).to receive(:get_moves_for_color).with(:Black, game.board).and_return([])
        
        winner = game.play()
        expect(winner).to eq(player2)
	end
end
