#ifndef _KING_H_
#define _KING_H_

#include "Piece.h"

class King : public Piece {
private:
    static const int _pieceValue = 0;
protected:

public:
    //https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
    explicit King(PieceColor pieceColor = PieceColor::WHITE);

    ~King();

    int getPieceValue();

    void draw(RenderWindow& window);

    vector<ChessMove> computePossbibleMoves(const vector<vector<Cell>>& cells);

};

#endif // _KING_H_