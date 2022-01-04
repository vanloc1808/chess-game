#ifndef _ROOK_H_
#define _ROOK_H_

#include "Piece.h"

class Rook : public Piece {
private:
    static const int _pieceValue = 5;
protected:

public:
//https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
    explicit Rook(PieceColor pieceColor = PieceColor::WHITE); //fully-parameterized constructor

    ~Rook();

    //re-define pure virtual methods in class Piece
    int getPieceValue();

    void draw(RenderWindow& window);

    vector<ChessMove> computePossbibleMoves(const vector<vector<Cell>>& cells);
};

#endif // _ROOK_H_