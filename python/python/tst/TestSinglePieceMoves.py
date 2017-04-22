'''
Created on Apr 19, 2017

@author: luke
'''
import unittest
from TestBase import TestBase
from Coordinate import Coordinate

class TestSinglePieceMoves(TestBase):

    def setUp(self):
        TestBase.setUp(self)

    def testSinglePiecesCannotJumpWhenBlocked(self):
        blackPiece = self.blackPieceAt(0,0)
        self.redPieceAt(1,1)
        self.redPieceAt(2,2)
        
        moves = blackPiece.getJumpMoves(self.board)
        self.assertEqual(0, len(moves))

    def testSinglePiecesCannotJumpItsOwnMan(self):
        blackPiece = self.blackPieceAt(0,0)
        self.blackPieceAt(1,1)

        moves = blackPiece.getJumpMoves(self.board)
        self.assertEqual(0, len(moves))
        
    def testSinglePiecesHaveTwoForwardMoves(self):
        blackPiece = self.blackPieceAt(0,2)
        moves = blackPiece.getSimpleMoves(self.board)
        
        self.assertEqual(2, len(moves))
        for move in moves:
            self.assertTrue(move.moveTo == Coordinate(1,1) or move.moveTo == Coordinate(1,3))

        redPiece = self.redPieceAt(4,2)
        moves = redPiece.getSimpleMoves(self.board)
        self.assertEqual(2, len(moves))
        for move in moves:
            self.assertTrue(move.moveTo == Coordinate(3,1) or move.moveTo == Coordinate(3,3))
                
    def testSinglePiecesCannotMoveOffTheBoardOrWhenBlocked(self):
        blackPiece = self.blackPieceAt(0,0)
        self.redPieceAt(1,1)
        
        moves = blackPiece.getSimpleMoves(self.board)
        self.assertEqual(0, len(moves))
        
    def testSinglePiecesCanJumpOnceAndThatPieceIsRemoved(self):
        blackPiece = self.blackPieceAt(0,0)
        self.redPieceAt(1,1)
        
        moves = blackPiece.getJumpMoves(self.board)

        self.assertEqual(1, len(moves))
        moves[0].execute()

        self.assertNoRedPieces()
        self.assertNoPieceAt(0,0)
        self.assertPieceIsBlack(2,2)
        
    def testSinglePiecesCanJumpMoreThanOnceAndThosePiecesAreRemoved(self):
        blackPiece = self.blackPieceAt(0,0)
        self.redPieceAt(1,1)
        self.redPieceAt(3,3)
        
        moves = blackPiece.getJumpMoves(self.board)
        self.assertEqual(1, len(moves))
        moves[0].execute()

        self.assertNoRedPieces()
        self.assertNoPieceAt(0,0)
        self.assertPieceIsBlack(4,4)
        
    def testSinglePiecesCanHaveTwoForwardSingleJumps(self):
        blackPiece = self.blackPieceAt(0,2)
        self.redPieceAt(1,1)
        self.redPieceAt(1,3)
        
        moves = blackPiece.getJumpMoves(self.board)
        self.assertEqual(2, len(moves))
        
        for move in moves:
            self.assertTrue(move.moveTo == Coordinate(2,0) or move.moveTo == Coordinate(2,4))
            
    def testSinglePiecesCanHaveMultipleForwardMultiJumps(self):
        blackPiece = self.blackPieceAt(0,2)
        self.redPieceAt(1,1)
        self.redPieceAt(1,3)
        self.redPieceAt(3,5)

        moves = blackPiece.getJumpMoves(self.board)
        self.assertEqual(2, len(moves))
        
        for move in moves:
            self.assertTrue(move.moveTo == Coordinate(2,0) or move.moveTo == Coordinate(4,6))

    def testWhenSinglePieceMovesIntoTheBackRowItIsKinged(self):
        blackPiece = self.blackPieceAt(self.board.size()-2,0)
        
        moves = blackPiece.getSimpleMoves(self.board)
        
        self.assertEqual(1, len(moves))
        moves[0].execute()
        
        newPiece = self.assertPieceIsBlack(self.board.size()-1,1)
        self.assertFalse(newPiece.canBeKinged)
        
    def testWhenSinglePieceJumpsIntoTheBackRowItIsKinged(self):
        blackPiece = self.blackPieceAt(self.board.size()-3,1)
        self.redPieceAt(self.board.size()-2,2)
        
        moves = blackPiece.getJumpMoves(self.board)
        self.assertEqual(1, len(moves))
        moves[0].execute()

        newPiece = self.assertPieceIsBlack(self.board.size()-1,3)
        self.assertFalse(newPiece.canBeKinged)

if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()