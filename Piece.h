#ifndef _PIECE_H_
#define _PIECE_H_

#include <string>
#include <vector>
#include <iostream>
#include <any>

#include "Player.h"

class PieceType {
private:
	std::string pieceType;
	int pieceValue = 0;

public:
	static PieceType* PAWN;
	static PieceType* ROOK;
	static PieceType* KNIGHT;
	static PieceType* BISHOP;
	static PieceType* QUEEN;
	static PieceType* KING;

	PieceType(const std::string& name, int val);

	std::string toString();

	bool isEqual(PieceType* p);

	std::string getPieceName();

	int getPieceValue();
};

class Piece {
protected:
	//positions are number from 0 to 63
	int piecePosition = 0;

	Sides pieceSide = static_cast<Sides>(0);

	bool firstMove = false;

	PieceType* type;

public:
	int cachedHashValue = 0;

	virtual ~Piece() {
		if (type) {
			delete[] type;
		}
	}

	Piece(int pos, Sides side, PieceType* t, bool firstMove);

	bool isEquals(std::any obj);

private:
	int calcHashValue;

public:
	int getHashValue();

	bool isWhite();
	bool isBlack();

	bool getFirstMove();

	void setFirstMove(bool val);

	bool isFirstMove();

	bool isKing();
	bool isQueen();
	bool isBishop();
	bool isKnight();
	bool isRook();
	bool isPawn();

	int getPiecePosition();

	PieceType* getPieceType();

	Sides getPieceSide();

	int getPieceValue();

	//get all legal moves of this piece
	virtual std::vector<Move*> getLegalMoves(Board* board) = 0;

	virtual Piece* movePiece(Move* move) = 0;

	virtual std::any clone() = 0;
};

#endif