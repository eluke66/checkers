'''
Created on Apr 16, 2017

@author: luke
'''
import unittest

from Coordinate import Coordinate
from color import Color
from SinglePiece import SinglePiece
from Board import Board


class TestBase(unittest.TestCase):

    def setUp(self):
        self.board = Board()
        
    # Utility methods
    def assertNoRedPieces(self):
        self.assertEquals(0, len(self.board.getPiecesForColor(Color.RED)))
        
    def assertNoBlackPieces(self):
        self.assertEquals(0, len(self.board.getPiecesForColor(Color.BLACK)))
        
    def assertPieceIsBlack(self, row, col):
        piece = self.board[Coordinate(row,col)]
        self.assertTrue(piece is not None)
        self.assertEquals(Color.BLACK, piece.color)
        return piece
        
    def assertPieceIsRed(self, row, col):
        piece = self.board[Coordinate(row,col)]
        self.assertTrue(piece is not None)
        self.assertEquals(Color.RED, piece.color)
        return piece
        
    def assertNoPieceAt(self, row, col):
        piece = self.board[Coordinate(row,col)]
        self.assertIsNone(piece)
        
    def redPieceAt(self, row, col):
        return self.board.placePieceAt(self.redPiece(), Coordinate(row,col))
        
    def blackPieceAt(self, row, col):
        return self.board.placePieceAt(self.blackPiece(), Coordinate(row,col))
        
    def blackPiece(self):
        return SinglePiece(Color.BLACK, SinglePiece.FORWARD)
    
    def redPiece(self):
        return SinglePiece(Color.RED, SinglePiece.BACKWARDS)

if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()