#include "Knight.h"
#include <iostream>
using namespace std;

const int Knight::_pieceValue; 

Knight::Knight(PieceColor pieceColor) {
    this->_pieceColor = pieceColor;

    this->_pieceType = PieceType::KNIGHT;

    this->loadTexture();
}

//destructor, no need to do anything
Knight::~Knight() {
    
}

int Knight::getPieceValue() {
    return Knight::_pieceValue;
}

void Knight::draw(RenderWindow& window) {
    window.draw(this->_pieceSprite);
}

//https://github.com/mbusy/chess/tree/master/src
vector<ChessMove> Knight::computePossbibleMoves(const vector<vector<Cell>>& cells) {
    Vector2i position = this->getPosition();

    vector<ChessMove> possibleMoves;

    //the Knight can move once in a letter L - shape
    //there is 8 directions in total
    vector<sf::Vector2i> offsets = {
        sf::Vector2i(2, 1), sf::Vector2i(2, -1),
        sf::Vector2i(1, 2), sf::Vector2i(1, -2),
        sf::Vector2i(-1, 2), sf::Vector2i(-1, -2),
        sf::Vector2i(-2, 1), sf::Vector2i(-2, -1)
    };
    for (int i = 0; i < offsets.size(); i++) {
        auto destination = position + offsets[i];

        //check if destination is out of board
        if (utilities::assisstants::isOnBoardPosition(destination) == false) {
            continue;
        }

        //check if the destination is empty or occupied
        if (cells[destination.x][destination.y]._status == CellStatus::OCCUPIED) {
            //if that is enemy, add it to possible moves
            if (cells[destination.x][destination.y]._piece->getPieceColor() != this->_pieceColor) {
                possibleMoves.push_back(destination);
            }
        }
        else {
            possibleMoves.push_back(destination);
            //with the Knight, we do not increase += like Queen or Bishop or Rook
        }
    }

    return possibleMoves;
}