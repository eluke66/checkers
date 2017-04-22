'''
Created on Apr 9, 2017

@author: luke
'''

class Coordinate(object):
    '''
    classdocs
    '''


    def __init__(self, row, col):
        self.row = row
        self.col = col
        
    def __repr__(self):
        return "(%d,%d)" % (self.row, self.col)
    
    def __eq__(self, other):
        return self.row == other.row and self.col == other.col

    @staticmethod
    def extending(c1, c2):
        '''
        Extends c1 and c2 to produce another coordinate in the same line
        '''
        newRow = (c2.row-c1.row) + c2.row
        newCol = (c2.col-c1.col) + c2.col
        return Coordinate(newRow, newCol);
        