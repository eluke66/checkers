'''
Created on Apr 16, 2017

@author: luke
'''

from color import Color

class Board(object):
    '''
    classdocs
    '''
    DEFAULT_SIZE = 8

    class PlacedPiece(object):
        def __init__(self, piece, coordinate):
            if isinstance(piece, Board.PlacedPiece):
                raise Exception("PASSING IN A PLACED PIECE TO A PLACED PIECE")
            self.piece = piece
            self.coordinate = coordinate
            self.getSimpleMoves = lambda b: piece.getSimpleMoves(self.coordinate, b)
            #self.getJumpMoves = lambda b: piece.getJumpMoves(self.coordinate, b)
        
        def __str__(self):
            return str(self.piece) + "@" + str(self.coordinate)
        
        def __repr__(self):
            return str(self.piece) + "@" + str(self.coordinate)
        
        def __getattr__(self, name):
            theMethod = getattr(self.piece, name)
            if theMethod is not None:
                return theMethod
            else:
                print ("UNSUPPORTED GET: " + name)
                
        def getJumpMoves(self, board):
            try:
                return self.piece.getJumpMoves(self.coordinate, board)
            except Exception as e:
                print("BAD! Piece is " + self.piece)
            
            
    def __init__(self, size=DEFAULT_SIZE):
        self.squares = [[None for x in range(size)] for y in range(size)]
        
    def size(self):
        return len(self.squares)
    
    def isValidPosition(self, coordinate):
        return coordinate.row >= 0 and coordinate.col >= 0\
                and coordinate.row < len(self.squares) and coordinate.col < len(self.squares)\
                and self.isUsableSquare(coordinate.row, coordinate.col)
    
    def isUsableSquare(self, row, col):
        return (isEven(row) and isEven(col)) or (not isEven(row) and  not isEven(col))
    
    def placePieceAt(self, piece, coordinate):
        if isinstance(piece, Board.PlacedPiece):
            placed = piece
        else:
            placed = Board.PlacedPiece(piece,coordinate)
        self.squares[coordinate.row][coordinate.col] = placed
        return placed
    
    def getPiecesForColor(self, color):
        pieces = []
        for row in range(len(self.squares)):
            pieces.extend([piece for piece in self.squares[row] if piece is not None and piece.color == color])
        return pieces
    
    def isFinalRowForPiece(self, piece, coordinate):
        return (piece.color == Color.RED and coordinate.row == 0) \
            or (piece.color == Color.BLACK and coordinate.row == len(self.squares)-1)
    
    def __getitem__(self, coordinate):
        return self.squares[coordinate.row][coordinate.col]
    
    def __delitem__(self, coordinate):
        self.squares[coordinate.row][coordinate.col] = None
    
    def __setitem__(self, coordinate, piece):
        self.placePieceAt(piece, coordinate)
        
    def __repr__(self):
        s = "  "
        s += "".join(map(str,range(len(self.squares))))
        s += "\n"
        for row in range(len(self.squares)):
            s += str(row) + " "
            for col in range(len(self.squares)):
                if not self.isUsableSquare(row,col):
                    s += "|"
                else:
                    p = self.squares[row][col]
                    if p is None:
                        s += "_"
                    elif p.color == Color.BLACK:
                        if p.canBeKinged:
                            s += "b"
                        else:
                            s += "B"
                    elif p.color == Color.RED:
                        if p.canBeKinged:
                            s += "r"
                        else:
                            s += "R"
                    else:
                        s += "?"
            s += "\n"
        return s
    
def isEven(num):
    return num % 2 == 0