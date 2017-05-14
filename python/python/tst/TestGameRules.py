'''
Created on Apr 21, 2017

@author: luke
'''
import unittest
from TestBase import TestBase
from game import Game
from color import Color
from Coordinate import Coordinate
from unittest.mock import MagicMock,call
from MoveRules import MoveRules
from Move import Move
from Player import Player

class TestGameRules(TestBase):


    def testEachPlayerStartsWith12Pieces(self):
        Game.putPiecesOnTheBoard(self.board)
        
        self.assertEqual(12, len(self.board.getPiecesForColor(Color.BLACK)))
        self.assertEqual(12, len(self.board.getPiecesForColor(Color.RED)))

    def testClosestLeftSquareToEachPlayerStartsWithAPiece(self):
        Game.putPiecesOnTheBoard(self.board)
        
        self.assertPieceIsBlack(0,0)
        end = self.board.size()-1
        self.assertPieceIsRed(end, end)
        
    def testBoardIs8x8(self):
        self.assertEqual(8, self.board.size())
        
    def testBlackMovesFirst(self):
        player1 = Player()
        player2 = Player()
        rules = MoveRules()
        game = Game(player1, player2, rules)
        rules.getMovesForColor = MagicMock(returnValue=[])
        
        game.play()

        rules.getMovesForColor.assert_called_once_with(Color.BLACK, game.board)
        
    def testRedMovesAfterBlack(self):
        player1 = Player()
        player2 = Player()
        rules = MoveRules()
        game = Game(player1, player2, rules)
        move = Move.simpleMove(game.board, self.blackPiece(), Coordinate(2,0), Coordinate(3,1))
        
        rules.getMovesForColor = MagicMock(side_effect=[[move], []])
        
        game.play()
        
        rules.getMovesForColor.assert_has_calls([call(Color.BLACK, game.board), call(Color.RED, game.board)])
        
    def testWhenAPlayerCannotMoveThenOtherPlayerWins(self):
        player1 = Player()
        player2 = Player()
        rules = MoveRules()
        game = Game(player1, player2, rules)
        move = Move.simpleMove(game.board, self.blackPiece(), Coordinate(2,0), Coordinate(3,1))
        
        rules.getMovesForColor = MagicMock(side_effect=[[move], []])
        
        winner = game.play()
        
        self.assertEqual(player1, winner)

if __name__ == "__main__":
    unittest.main()
