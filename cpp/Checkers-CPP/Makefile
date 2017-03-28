CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++11

OBJS =		Board.o SinglePiece.o Move.o MoveRules.o KingPiece.o Game.o ConsolePlayer.o RandomChoicePlayer.o
TESTOBJS = 	Tests.o GameTests.o KingPiecesTests.o SinglePiecesTests.o
LIBS =

TARGET =	Game

all:	$(TARGET) Tests

$(TARGET):	$(OBJS) Driver.o
	$(CXX) -o $(TARGET) $(OBJS) Driver.o $(LIBS)

Tests:	$(OBJS) $(TESTOBJS)
	$(CXX) -o Tests $(TESTOBJS) $(OBJS) $(LIBS) -lgtest -lpthread
	

clean:
	rm -f *.o $(TARGET) Tests
