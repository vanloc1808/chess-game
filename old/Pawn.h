#ifndef _PAWN_H_
#define _PAWN_H_

#include <iostream>
#include <vector>
#include <string>
#include <any>

#include "Piece.h"
#include "Player.h"

class Pawn : public Piece {
//PAWN is a special piece, it has the ability to promte =))
private:
	int direction = 0;

protected:
	static std::vector<int> legalMoveArguments;

public:
	Pawn(int pos, Sides s, bool first);

private:
	bool isPromotionPosition(int pos);

public:
	std::vector<Move*> getLegalMoves(Board* board);

	std::string toString();

	Piece* movePiece(Move* move);

	Piece* getPromotionPiece(PieceType* proType);

	Piece* getPromotionPiece();

	std::any clone();
};

#endif // !_PAWN_H_

