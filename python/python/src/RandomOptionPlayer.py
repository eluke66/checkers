'''
Created on Apr 21, 2017

@author: luke
'''

from Player import Player
import random

class RandomOptionPlayer(Player):
    def selectMove(self, moves, board):
        return random.choice(moves)
        
