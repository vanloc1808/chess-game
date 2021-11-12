#ifndef _ROOK_H_
#define _ROOK_H_

#include <iostream>
#include <vector>
#include <string>
#include <any>

#include "Piece.h"
#include "Player.h"

class Rook : public Piece {
protected:
	static std::vector<int> legalMoveArguments;

public:
	Rook(int pos, Sides s, bool first);

	std::vector<Move*> getLegalMoves(Board* board);

private:
	static bool firstColumnViolation(int piecePos, int arg);
	static bool eighthColumnViolation(int piecePos, int arg);

public:
	std::string toString();

	Piece* movePiece(Move* move);

	std::any clone();
};

#endif // ! _ROOK_H_