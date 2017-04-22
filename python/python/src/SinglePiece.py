'''
Created on Apr 9, 2017

@author: luke
'''

from Piece import Piece
from Coordinate import Coordinate
from MoveRules import MoveRules

class SinglePiece(Piece):
    '''
    classdocs
    '''
    FORWARD = 1
    BACKWARDS = -1

    def __init__(self, color, direction):
        super().__init__(color, True)
        self.direction = direction
    
    def __repr__(self):
        return "%s piece" % self.color
     
    def getSimpleMoves(self, coordinate, board):
        return MoveRules.getSimpleMoves(board, self, coordinate, self.getFollowingCoords)
    
    def getJumpMoves(self, coordinate, board):
        return MoveRules.getJumpMoves(board, self, coordinate, self.getFollowingCoords)
    
    def getFollowingCoords(self, c):
        return [Coordinate(c.row+self.direction, c.col+1), Coordinate(c.row+self.direction, c.col-1)]