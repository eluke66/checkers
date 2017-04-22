'''
Created on Apr 9, 2017

@author: luke
'''
from Coordinate import Coordinate
from Move import Move
import itertools

class MoveRules(object):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
        pass
        
    
    @staticmethod 
    def getJumpMoves(board, piece, coordinate, coordProducer):
        isValid = lambda c: board.isValidPosition(c) and pieceIsJumpable(board,piece,c) and nextSpaceIsLandable(board,piece,coordinate,c)
        toMove = lambda c: Move.jumpMove(board, piece, coordinate, c)
        
        #print ("getJumpMoves::Coords are " + str(coordProducer(coordinate)))
        #print ("getJumpMoves::Valid coords are " + str(list(filter(isValid,coordProducer(coordinate)))))
        initialMoves = list(map(toMove, filter(isValid,coordProducer(coordinate))))
        #print ("getJumpMoves::MoveRules - initial jump moves are " + str(initialMoves))
        return searchJumps(initialMoves, board, piece, coordProducer)
       
    @staticmethod
    def getSimpleMoves(board, piece, coordinate, coordProducer):
        isValid = lambda c: board.isValidPosition(c) and board[c] is None
        toMove = lambda c: Move.simpleMove(board, piece, coordinate, c)
        
        #print ("getSimpleMoves::Coords are " + str(coordProducer(coordinate)))
        #print ("getSimpleMoves::Valid coords are " + str(list(filter(isValid,coordProducer(coordinate)))))
        return list(map(toMove, filter(isValid,coordProducer(coordinate))))
    
     
    def getMovesForColor(self, color, board):
        pieces = board.getPiecesForColor(color)
        
        moves = list(itertools.chain.from_iterable([piece.getJumpMoves(board) for piece in pieces]))
        
        # Do jumps if available   
        if len(moves) != 0:
            return moves

        # Otherwise do simple moves.
        return list(itertools.chain.from_iterable([piece.getSimpleMoves(board) for piece in pieces]))


def pieceIsJumpable(board, piece, coordinate):
    boardPiece = board[coordinate]
    return boardPiece is not None and boardPiece.color != piece.color

def nextSpaceIsLandable(board,piece,startCoordinate,nextCoordinate):
    landingSpot = Coordinate.extending(startCoordinate, nextCoordinate)
    return board.isValidPosition(landingSpot) and board[landingSpot] is None

def searchJumps(incomingMoves, board, piece, coordProducer):
    finalMoves = []
    for move in incomingMoves:
        # Let's assume we execute the move.
        move.execute()

        # Get the next jump moves.
        nextCoordinate = move.moveTo
        toMove = lambda c: Move.multiJumpMove(board, piece, nextCoordinate, c, move)
        isValid = lambda c: board.isValidPosition(c)\
            and pieceIsJumpable(board,piece,c)\
            and nextSpaceIsLandable(board, piece, nextCoordinate, c)
        
        nextCoordinates = coordProducer(nextCoordinate)
        validSpots = filter(isValid, nextCoordinates)
        nextMovesForThisMove = list(map(toMove, validSpots))
        
        # And undo the move
        move.unExecute()

        # If there are any next moves, then we replace this move with those moves AND THEIR CONTINUED MOVES
        if len(nextMovesForThisMove) > 0:
            finalMoves.extend(searchJumps(nextMovesForThisMove, board, piece, coordProducer))
        else:
            # Otherwise we don't have to jump more, and just add this move.
            finalMoves.append(move)
    
    return finalMoves
    