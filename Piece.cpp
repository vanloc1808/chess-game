#include <iostream>
#include "Piece.h"

PieceType::PieceType(std::string name, int value) {
    this->pieceName = name;
    this->pieceValue = value;
}

std::string PieceType::toString() {
    return this->pieceName;
}

bool PieceType::isEqual(PieceType diffType) {
    return this->pieceName == diffType.pieceName;
}

std::string PieceType::getPieceName() {
    return this->pieceName;
}

int PieceType::getPieceValue() {
    return this->pieceValue;
}

class Piece {
protected:
    int piecePosition;

    //Sides pieceSide;

    bool firstMove;

    PieceType type;

public:
    //Piece(int position, Sides pieceSide, bool first, PieceType t);
    bool isFirstMove();
}