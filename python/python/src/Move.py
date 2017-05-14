'''
Created on Apr 9, 2017

@author: luke
'''

from Coordinate import Coordinate
from KingPiece import KingPiece

class Move(object):
    def __init__(self, piece, board, moveFrom, moveTo):
        self.piece = piece
        self.board = board
        self.moveFrom = moveFrom
        self.moveTo = moveTo
        
    def __repr__(self):
        return "{} moving from {} to {}".format(self.piece, self.moveFrom, self.moveTo)
    
    @staticmethod
    def simpleMove(board, piece, startCoord, endCoord):
        return SimpleMove(piece, board, startCoord, endCoord)
    
    @staticmethod
    def jumpMove(board, piece, startCoord, endCoord):
        return JumpMove(piece, board, startCoord, endCoord, Coordinate.extending(startCoord, endCoord))
    
    @staticmethod
    def multiJumpMove(board, piece, startCoord, endCoord, move):
        return MultiJumpMove(piece, board, startCoord, endCoord, Coordinate.extending(startCoord, endCoord), move)
    
    def moveAndKingPiece(self, piece):
        self.board.placePieceAt(piece, self.moveTo)
        if self.board.isFinalRowForPiece(piece, self.moveTo) and piece.canBeKinged:
            self.board.placePieceAt(KingPiece(piece.color), self.moveTo)

class SimpleMove(Move):
    def __init__(self, piece, board, moveFrom, moveTo):
        super().__init__(piece, board, moveFrom, moveTo)
    
    def execute(self):
        del self.board[self.moveFrom]
        self.moveAndKingPiece(self.piece)
    
    def unExecute(self):
        del self.board[self.moveTo]
        self.board[self.moveFrom] = self.piece
        
    
class JumpMove(Move):
    def __init__(self, piece, board, moveFrom, existingPieceLocation, moveTo):
        super().__init__(piece, board, moveFrom, moveTo)
        self.removedPiece = None
        self.existingPieceLocation = existingPieceLocation
      
    def execute(self):
        if self.removedPiece is None:
            self.removedPiece = self.board[self.existingPieceLocation]
            del self.board[self.moveFrom]
            self.moveAndKingPiece(self.piece)
            del self.board[self.existingPieceLocation]
        else:
            raise RuntimeError("Trying to re-execute jump move " + str(self))
        
    def unExecute(self):
        if self.removedPiece is not None:
            del self.board[self.moveTo]
            self.board[self.moveFrom] = self.piece
            self.board[self.existingPieceLocation] = self.removedPiece
            self.removedPiece = None
        else:
            raise RuntimeError("Trying to unexecute jump move that has not been executed" + str(self))

class MultiJumpMove(JumpMove):
    def __init__(self, piece, board, moveFrom, existingPieceLocation, moveTo, previousMove):
        super().__init__(piece, board, moveFrom, existingPieceLocation, moveTo)
        self.previousMove = previousMove
        
    def execute(self):
        self.previousMove.execute()
        JumpMove.execute(self)
        
    def unExecute(self):
        JumpMove.unExecute(self)
        self.previousMove.unExecute()
