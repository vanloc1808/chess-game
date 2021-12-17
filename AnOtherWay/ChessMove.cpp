#include "ChessMove.h"

ChessMove::ChessMove(const Vector2i& pos, MoveType t) {
    this->_position = pos;
    this->_type = t;
}

ChessMove::ChessMove(const Vector2i& pos) : ChessMove(pos, MoveType::NONE) {

}

ChessMove::ChessMove() : ChessMove(Vector2i(-1, -1), MoveType::NONE) {

}

ChessMove::~ChessMove() {
    
}