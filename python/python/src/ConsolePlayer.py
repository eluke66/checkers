'''
Created on Apr 21, 2017

@author: luke
'''

from Player import Player

class ConsolePlayer(Player):
    '''
    classdocs
    '''

    def selectMove(self, moves, board):
        for i in range(len(moves)):
            print("{}: {}".format(i,moves[i]))
        choice = input("Enter move choice:")
        try:
            intChoice = int(choice)
            if intChoice < 0 or intChoice >= len(moves):
                print("Invalid choice {}".format(intChoice))
                return self.selectMove(moves,board)
            else:
                return moves[intChoice]
        except Exception as e:
            print("Invalid choice {} - {}".format(choice, e))
            return self.selectMove(moves, board)
        
class ConsoleHandler(object):
    def playerTurn(self,whichTurn, currentPlayer, board, color):
        print("Turn {}: Player {} ({})\n{}".format(whichTurn, currentPlayer, color, board))
        
    def gameFinished(self, whichTurn, winningPlayer):
        print("Player {} wins on turn {}".format(winningPlayer, whichTurn))

        