CXXFLAGS =	-O2 -g -pg -Wall -fmessage-length=0 -std=c++11

OBJS =		Board.o SinglePiece.o Move.o MoveRules.o KingPiece.o Game.o ConsolePlayer.o RandomChoicePlayer.o

LIBS =

TARGET =	Game

$(TARGET):	$(OBJS) Driver.o
	$(CXX) -pg -o $(TARGET) $(OBJS) Driver.o $(LIBS)

Tests:	$(OBJS) Tests.o GameTests.cpp KingPiecesTests.cpp SinglePiecesTests.cpp
	$(CXX) -o Tests Tests.o $(OBJS) $(LIBS) -lgtest -lpthread
	
all:	$(TARGET)

clean:
	rm -f $(OBJS) Tests.o Game.o Driver.o $(TARGET) Tests
