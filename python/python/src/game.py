'''
Created on Apr 9, 2017

@author: luke

To profile: python3 -m cProfile -s time src/game.py 1000
'''

from color import Color
from Coordinate import Coordinate
from SinglePiece import SinglePiece
from Board import Board
from MoveRules import MoveRules

class Game(object):
    '''
    classdocs
    '''
    NUM_PIECES_PER_PLAYER = 12

    def __init__(self, player1, player2, moveRules=None, eventHandler=None):
        self.player1 = (player1, Color.BLACK)
        self.player2 = (player2, Color.RED)
        
        self.moveRules = MoveRules() if moveRules == None else moveRules
        self.eventHandler = eventHandler
        self.board = Board()
    
        
    def play(self):
        Game.putPiecesOnTheBoard(self.board)
        whichPlayer = 0
        whichTurn = 0
        players = [self.player1, self.player2]
        while (True):
            currentPlayer,color = players[whichPlayer]
            if (self.eventHandler is not None):
                self.eventHandler.playerTurn(whichTurn, currentPlayer, self.board, color)
            moves = self.moveRules.getMovesForColor(color, self.board)
            if len(moves) == 0:
                break
           
            move = currentPlayer.selectMove(moves, self.board)
            move.execute()

            whichPlayer = (whichPlayer+1)%2
            whichTurn += 1
        
        winningPlayer,winningColor = players[(whichPlayer+1)%2]
        if (self.eventHandler is not None):
            self.eventHandler.gameFinished(whichTurn, winningPlayer)

        return winningPlayer

    @staticmethod
    def putPiecesOnTheBoard(board):
        piecesPerRow = board.size()/2
        rows = int(Game.NUM_PIECES_PER_PLAYER / piecesPerRow)
        
        if (piecesPerRow * rows != Game.NUM_PIECES_PER_PLAYER):
            raise RuntimeError("Cannot fit " + Game.NUM_PIECES_PER_PLAYER + " onto a board of size " + board.size())

        for row in range(rows):
            colStart = 0 if (row % 2 == 0) else 1
            for col in range(colStart, board.size(), 2):
                piece = SinglePiece(Color.BLACK, SinglePiece.FORWARD)
                board.placePieceAt(piece, Coordinate(row,col))
                
        for row in range(rows):
            thisRow = board.size() - row - 1
            colStart = 0 if (thisRow % 2 == 0) else 1
            for col in range(colStart, board.size(), 2):
                piece = SinglePiece(Color.RED, SinglePiece.BACKWARDS)
                board.placePieceAt(piece, Coordinate(thisRow,col))
         
def profile(numRuns):
    from time import perf_counter
    from RandomOptionPlayer import RandomOptionPlayer
    totalTime = 0
    
    for i in range(numRuns):
        game = Game(RandomOptionPlayer(), RandomOptionPlayer())
        start = perf_counter()
        game.play()
        end = perf_counter()
        totalTime += (end-start)
    
    msPerGame = (totalTime*1000) / numRuns
    print ("Total time is {:.2f} sec to play {:d} games, or {:.2f} ms/game".format(totalTime, numRuns, msPerGame))
         
def playInteractive():
    from ConsolePlayer import ConsolePlayer, ConsoleHandler
    Game(ConsolePlayer(), ConsolePlayer(), eventHandler=ConsoleHandler()).play()
        
if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1:
        numRuns = int(sys.argv[1])
        print("Going to profile using " + str(numRuns) + " runs")
        profile(numRuns)
    else:
        playInteractive()
