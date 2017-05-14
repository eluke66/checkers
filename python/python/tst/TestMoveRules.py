'''
Created on Apr 16, 2017

@author: luke
'''
import unittest
from TestBase import TestBase
from color import Color
from MoveRules import MoveRules

class TestMoveRules(TestBase):
    
    def setUp(self):
        TestBase.setUp(self)
        self.rules = MoveRules()
        
    def testIfCapturingMovesAreAvailableTheyMustBePickedForSimple(self):
        self.blackPieceAt(0,2)
        self.redPieceAt(1,1)
        
        moves = self.rules.getMovesForColor(Color.BLACK, self.board)

        self.assertEqual(1, len(moves)) 
        moves[0].execute()
        
        self.assertNoRedPieces()

    def testIfCapturingMovesAreAvailableTheyMustBePickedForMultiJumps(self):
        self.blackPieceAt(0,2)
        self.redPieceAt(1,3)
        self.redPieceAt(3,5)

        moves = self.rules.getMovesForColor(Color.BLACK, self.board);

        self.assertEqual(1, len(moves)) 
        moves[0].execute()

        self.assertNoRedPieces()
        self.assertPieceIsBlack(4,6)
    
if __name__ == "__main__":
    unittest.main()
