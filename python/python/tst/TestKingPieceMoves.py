'''
Created on Apr 21, 2017

@author: luke
'''
import unittest
from TestBase import TestBase
from KingPiece import KingPiece
from color import Color
from Coordinate import Coordinate


class TestKingPieceMoves(TestBase):
    def testKingsCanMoveForwardAndBackwards(self):
        blackPiece = self.blackPieceAt(2,2)
        
        moves = blackPiece.getSimpleMoves(self.board)
        
        self.assertEqual(4, len(moves))
        for move in moves:
            self.assertTrue(move.moveTo == Coordinate(1,1)\
                            or move.moveTo == Coordinate(1,3)\
                            or move.moveTo == Coordinate(3,1)\
                            or move.moveTo == Coordinate(3,3))

    def testKingsCannotJumpWhenBlocked(self):
        blackPiece = self.blackPieceAt(0,0)
        self.redPieceAt(1,1)
        self.redPieceAt(2,2)
        
        moves = blackPiece.getJumpMoves(self.board)
        self.assertEqual(0, len(moves))
        
    def testKingsCanJumpForwardOnce(self):
        blackPiece = self.blackPieceAt(0,0)
        self.redPieceAt(1,1)
        
        moves = blackPiece.getJumpMoves(self.board)

        self.assertEqual(1, len(moves))
        moves[0].execute()

        self.assertNoRedPieces()
        self.assertNoPieceAt(0,0)
        self.assertPieceIsBlack(2,2)
        
    def testKingsCanJumpBackwardsOnce(self):
        blackPiece = self.blackPieceAt(2,2)
        self.redPieceAt(1,1)
        
        moves = blackPiece.getJumpMoves(self.board)

        self.assertEqual(1, len(moves))
        moves[0].execute()

        self.assertNoRedPieces()
        self.assertNoPieceAt(2,2)
        self.assertPieceIsBlack(0,0)
        
    def testKingsCanJumpForwardsThenBackwards(self):
        blackPiece = self.blackPieceAt(2,0)
        self.redPieceAt(1,1)
        self.redPieceAt(1,3)
        
        moves = blackPiece.getJumpMoves(self.board)

        self.assertEqual(1, len(moves))
        moves[0].execute()

        self.assertNoRedPieces()
        self.assertNoPieceAt(2,0)
        self.assertPieceIsBlack(2,4)
    
    def testKingsCanJumpBackwardsThenForwards(self):
        blackPiece = self.blackPieceAt(2,4)
        self.redPieceAt(1,1)
        self.redPieceAt(1,3)
        
        moves = blackPiece.getJumpMoves(self.board)

        self.assertEqual(1, len(moves))
        moves[0].execute()

        self.assertNoRedPieces()
        self.assertNoPieceAt(2,4)
        self.assertPieceIsBlack(2,0)    
        
    def blackPiece(self):
        return KingPiece(Color.BLACK)
    
    def redPiece(self):
        return KingPiece(Color.RED)
    
if __name__ == "__main__":
    unittest.main()
