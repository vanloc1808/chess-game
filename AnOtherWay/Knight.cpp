#include "Knight.h"

Knight::Knight(PieceColor pieceColor) {
    this->_pieceColor = pieceColor;

    this->_pieceType = PieceType::KNIGHT;

    this->loadTexture();
}

Knight::~Knight() {
    //do nothing
}

int Knight::getPieceValue() {
    return Knight::_pieceValue;
}

void Knight::draw(RenderWindow& window) {
    window.draw(this->_pieceSprite);
}

vector<ChessMove> Knight::computePossbibleMoves(const vector<vector<Cell>>& cells) {
    vector<ChessMove> possibleMoves;

    auto position = this->getPosition();

    vector<sf::Vector2i> offsets = {
        sf::Vector2i(2, 1), sf::Vector2i(2, -1),
        sf::Vector2i(1, 2), sf::Vector2i(1, -2),
        sf::Vector2i(-1, 2), sf::Vector2i(-1, -2),
        sf::Vector2i(-2, 1), sf::Vector2i(-2, -1)
    };

    for (int i = 0; i < offsets.size(); i++) {
        auto destination = position + offsets[i];

        if (utilities::assisstants::isOnBoardPosition(destination) == false) {
            continue;
        }

        if (cells[destination.x][destination.y]._status == CellStatus::OCCUPIED) {
            if (cells[destination.x][destination.y]._piece->getPieceColor() != this->_pieceColor) {

                possibleMoves.push_back(destination);
            }
        }
        else {
            possibleMoves.push_back(destination);
            //don't increase like Queen or Bishop
        }
    }

    return possibleMoves;
}