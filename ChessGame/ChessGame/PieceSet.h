#ifndef _PIECESET_H_
#define _PIECESET_H_

#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"

//set of pieces for each side (16 pieces)
class PieceSet {
private:
	GameColor _pieceSetColor;

	Piece* _kingPiece;

public:
	bool _isLost;

	vector<Piece*> _pieces;

	vector<Piece*> _eatenPieces;

public:
	PieceSet(); //constructor

	~PieceSet(); //destructor

	void createPieceSet(GameColor color); //construct pieces

	int getPieceNumber(); //return the number of REMAINING pieces

	void unselectPiece(); //undo the selected status

	void erasePiece(); //erase piece

	void erasePieceAtIndex(int i);

	void pawnPromotion(Piece* p, string pieceType); //promote Pawn

	void unselecEaten(); //undo the eaten status

	Piece* cpuSelectionPiece(int c, int r); //return the piece status, used for playing vs CPU

	int findPieceInVector(Piece* p); //find the position of p in vector

	bool castling(Piece* p, PieceBoard pb[][8]); //castling, in Vietnamese we call "nhap thanh"

	GameColor getSetColor(); //getter for set color

	void loseKing();

	Vector2i getKingPosition(); //get the position of the King
};

#endif // !_PIECESET_H_
