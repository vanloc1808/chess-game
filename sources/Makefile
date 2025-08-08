CC = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SOURCES = Bishop.cpp Cell.cpp ChessBoard.cpp ChessMove.cpp GameAudioPlayer.cpp GameSound.cpp GameUser.cpp King.cpp Knight.cpp Pawn.cpp Piece.cpp PieceData.cpp Queen.cpp Rook.cpp Settings.cpp Utility.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = chess

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o

cleanall: clean
	rm -f $(TARGET)