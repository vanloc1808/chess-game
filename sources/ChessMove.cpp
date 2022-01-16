#include "ChessMove.h"

//fully-parameterized constructor, construct position and type
ChessMove::ChessMove(const Vector2i& pos, MoveType t) {
    this->_position = pos;
    this->_type = t;
}

//partly-parameterized constructor, call the fully-parameterized constructor
ChessMove::ChessMove(const Vector2i& pos) : ChessMove(pos, MoveType::NONE) {

}

//default construct, call the partly-parameterized constructor
ChessMove::ChessMove() : ChessMove(Vector2i(-1, -1), MoveType::NONE) {

}

//destructor, no need to do anything
ChessMove::~ChessMove() {
    
}