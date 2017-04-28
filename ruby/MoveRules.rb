require_relative "Move"

class MoveRules
	def initialize
		
	end
	
	def MoveRules.get_simple_moves(board, piece, coordinate, coordProducer)
		coords = coordProducer.call(coordinate)
		validCoords = coords.find_all { |c| board.valid_position?(c) && board[c] == nil }
		return validCoords.map { |c| Move.simple_move(board, piece, coordinate, c) }
	end
	
	def MoveRules.get_jump_moves(board, piece, coordinate, coordProducer)
		coords = coordProducer.call(coordinate)
		validCoords = coords.find_all { |c| 
				board.valid_position?(c) && 
				piece_is_jumpable?(board,piece,c) && 
				next_space_is_landable?(board,piece,coordinate,c) }
		initialMoves = validCoords.map { |c| Move.jump_move(board, piece, coordinate, c) }
		
		return MoveRules.search_jumps(initialMoves, board, piece, coordProducer)
	end
		
	def get_moves_for_color(color, board)
        pieces = board.get_pieces_for_color(color)
        
        moves = pieces.flat_map { |piece| piece.get_jump_moves(board) }
        
        # Do jumps if available   
        if moves.length > 0
            return moves
        end

        # Otherwise do simple moves.
        return pieces.flat_map { |piece| piece.get_simple_moves(board) }
	end
	
	def MoveRules.piece_is_jumpable?(board,piece,c)
		boardPiece = board[c]
		return boardPiece != nil && boardPiece.color != piece.color
	end
	
	def MoveRules.next_space_is_landable?(board,piece,startCoordinate,nextCoordinate)
		landingSpot = Coordinate.extending(startCoordinate, nextCoordinate)
		return board.valid_position?(landingSpot) && board[landingSpot] == nil
	end
	
	def MoveRules.search_jumps(incomingMoves, board, piece, coordProducer)	
		finalMoves = []
		incomingMoves.each do |move|
			# Let's assume we execute the move.
			move.execute()
			
			# Get the next jump moves.
			nextCoordinate = move.moveTo
			
			nextCoordinates = coordProducer.call(nextCoordinate)
			validCoords = nextCoordinates.find_all { |c|
				board.valid_position?(c) && 
				piece_is_jumpable?(board,piece,c) && 
				next_space_is_landable?(board,piece,nextCoordinate,c)
			}
			nextMovesForThisMove = validCoords.map { |c| Move.multi_jump_move(board, piece, nextCoordinate, c, move) }
			
			# And undo the move
			move.unExecute()

			# If there are any next moves, then we replace this move with those moves AND THEIR CONTINUED MOVES
			if nextMovesForThisMove.length > 0
				finalMoves.concat(search_jumps(nextMovesForThisMove, board, piece, coordProducer))
			else
				# Otherwise we don't have to jump more, and just add this move.
				finalMoves << move
			end
		end
		
		return finalMoves
	end
end

