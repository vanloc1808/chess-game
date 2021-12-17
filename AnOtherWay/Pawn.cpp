#include "Pawn.h"

const int Pawn::_pieceValue;

Pawn::Pawn(PieceColor pieceColor) {
    this->_pieceColor = pieceColor;

    if (this->_pieceColor == PieceColor::WHITE) {
        this->_pieceDirection = PieceDirection::UP;
    } else {
        this->_pieceDirection = PieceDirection::DOWN;
    }

    this->_pieceType = PieceType::PAWN;
    this->loadTexture();
}

Pawn::~Pawn() {
    //do nothing
}

int Pawn::getPieceValue() {
    return Pawn::_pieceValue;
}

void Pawn::draw(RenderWindow& window) {
    window.draw(this->_pieceSprite);
}

vector<ChessMove> Pawn::computePossbibleMoves(const vector<vector<Cell>>& cells) {
    Vector2i pos = this->getPosition();

    vector<ChessMove> possibleMoves;

    int direction;

    if (this->_pieceDirection == PieceDirection::UP) {
        direction = -1;
    } else {
        direction = 1;
    }

    int xnew = pos.x + direction;
    int doubleStepIndex;

    if (this->_pieceColor == PieceColor::WHITE) {
        doubleStepIndex = 6;
    } else {
        doubleStepIndex = 1;
    }

    if (xnew < 0 || xnew >= 8) {
        return possibleMoves;
    }

    ChessMove pawnMove;
    bool promoteCond1 = this->_pieceColor == PieceColor::WHITE && xnew == 0;
    bool promoteCond2 = this->_pieceColor == PieceColor::BLACK && xnew == 7;
    if (promoteCond1 || promoteCond2) {
        pawnMove._type = MoveType::PROMOTION;
    }

    //check the possible capturing moves for the pawn
    for (auto yoffset : {-1, 1}) {
        if (pos.y + yoffset < 0 || pos.y + yoffset >= 8) {
            continue;
        }

        Cell cell = cells[xnew][pos.y + yoffset];

        if (cell._status == CellStatus::OCCUPIED && cell._piece->getPieceColor() != this->_pieceColor) {
            pawnMove._position = Vector2i(xnew, pos.y + yoffset);
            possibleMoves.push_back(pawnMove);
        }
    }

    //check for a simple forward step
    if (cells[xnew][pos.y]._status == CellStatus::EMPTY) {
        pawnMove._position = Vector2i(xnew, pos.y);
        possibleMoves.push_back(pawnMove);
    } else {
        return possibleMoves;
    }

    //checl fpr a double forward step, if this is the first move of the pawn,
    //and the path is empty
    bool doubleCond1 = pos.x == doubleStepIndex;
    bool doubleCond2 = xnew + direction >= 0;
    bool doubleCond3 = xnew + direction <= 7;
    bool doubleCond4 = cells[xnew + direction][pos.x]._status == CellStatus::EMPTY;
    if (doubleCond1 && doubleCond2 && doubleCond3 && doubleCond4) {
        possibleMoves.push_back(Vector2i(xnew + direction, pos.y));
    }
    
    return possibleMoves;
}