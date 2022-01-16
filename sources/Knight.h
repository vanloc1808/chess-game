#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "Piece.h"

class Knight : public Piece {
private:
    static const int _pieceValue = 3;
protected:

public:
//https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
    explicit Knight(PieceColor pieceColor = PieceColor::WHITE); //fully-parameterized constructor

    ~Knight();

    //re-define pure virtual methods in class Piece
    int getPieceValue();

    void draw(RenderWindow& window);

    vector<ChessMove> computePossbibleMoves(const vector<vector<Cell>>& cells);
};

#endif // _KNIGHT_H_