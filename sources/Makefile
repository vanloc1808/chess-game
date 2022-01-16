CC = g++

all: Bishop.o Cell.o ChessBoard.o ChessMove.o GameAudioPlayer.o GameSound.o GameUser.o King.o Knight.o Pawn.o Piece.o PieceData.o Queen.o Rook.o Settings.o Utility.o main.o 
	$(CC) Bishop.o Cell.o ChessBoard.o ChessMove.o GameAudioPlayer.o GameSound.o GameUser.o King.o Knight.o Pawn.o Piece.o PieceData.o Queen.o Rook.o Settings.o Utility.o main.o -o chess -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

Bishop.o: Bishop.cpp Bishop.h
	$(CC) -g -c Bishop.cpp

Cell.o: Cell.cpp Cell.h
	$(CC) -g -c Cell.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h
	$(CC) -g -c ChessBoard.cpp

ChessMove.o: ChessMove.cpp ChessMove.h
	$(CC) -g -c ChessMove.cpp

GameAudioPlayer.o: GameAudioPlayer.cpp GameAudioPlayer.h
	$(CC) -g -c GameAudioPlayer.cpp

GameSound.o: GameSound.cpp GameSound.h
	$(CC) -g -c GameSound.cpp

GameUser.o: GameUser.cpp GameUser.h
	$(CC) -g -c GameUser.cpp

King.o: King.cpp King.h
	$(CC) -g -c King.cpp

Knight.o: Knight.cpp Knight.h
	$(CC) -g -c Knight.cpp

Pawn.o: Pawn.cpp Pawn.h
	$(CC) -g -c Pawn.cpp

Piece.o: Piece.cpp Piece.h
	$(CC) -g -c Piece.cpp

PieceData.o: PieceData.cpp PieceData.h
	$(CC) -g -c PieceData.cpp

Queen.o: Queen.cpp Queen.h
	$(CC) -g -c Queen.cpp

Rook.o: Rook.cpp Rook.h
	$(CC) -g -c Rook.cpp

Settings.o: Settings.cpp Settings.h
	$(CC) -g -c Settings.cpp

Utility.o: Utility.cpp Utility.h
	$(CC) -g -c Utility.cpp

main.o: Bishop.h Cell.h ChessBoard.h ChessMove.h GameAudioPlayer.h GameSound.h GameUser.h King.h Knight.h Pawn.h Piece.h PieceData.h Queen.h Rook.h Settings.h Utility.h main.cpp
	$(CC) -g -c main.cpp

clean: 
	rm *.o

cleanall:
	rm *.o 
	rm chess