#ifndef _KNIGHT_H_
#define _KNIGH_H_

#include <iostream>
#include <vector>
#include <string>
#include <any>

#include "Piece.h"
#include "Player.h"

class Knight : public Piece {
protected:
	static std::vector<int> legalMoveArguments;

public:
	Knight(int pos, Sides s, bool first);

	std::vector<Move*> getLegalMoves(Board* board);

private:
	static bool firstColumnViolation(int piecePos, int arg);
	static bool secondColumnViolation(int piecePos, int arg);
	static bool seventhColumnViolation(int piecePos, int arg);
	static bool eighthColumnViolation(int piecePos, int arg);

public:
	std::string toString();

	Piece* movePiece(Move* move);

	std::any clone();
};

#endif // _KNIGH_H_


