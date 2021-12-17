#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.h"

class Pawn : public Piece {
private:
    static const int _pieceValue = 1;
protected:

public:
//https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
    explicit Pawn(PieceColor pieceColor = PieceColor::WHITE);

    ~Pawn();

    int getPieceValue();

    void draw(RenderWindow& window);

    vector<ChessMove> computePossbibleMoves(const vector<vector<Cell>>& cells);    
};

#endif // _PAWN_H_