'''
Created on Apr 9, 2017

@author: luke
'''

from Piece import Piece
from Coordinate import Coordinate

import MoveRules
    
class KingPiece(Piece):

    def __init__(self, color):
        super().__init__(color, False)
    
    def __repr__(self):
        return "%s King" % self.color
     
    def getSimpleMoves(self, coordinate, board):
        return MoveRules.MoveRules.getSimpleMoves(board, self, coordinate, self.getFollowingCoords)
    
    def getJumpMoves(self, coordinate, board):
        return MoveRules.MoveRules.getJumpMoves(board, self, coordinate, self.getFollowingCoords)
    
    def getFollowingCoords(self, c):
        return [Coordinate(c.row+1, c.col+1), Coordinate(c.row+1, c.col-1), Coordinate(c.row-1, c.col+1), Coordinate(c.row-1, c.col-1)]
