#include "Rook.h"
#include <iostream>
using namespace std;

const int Rook::_pieceValue;

Rook::Rook(PieceColor pieceColor) {
    this->_pieceColor = pieceColor;

    this->_pieceType = PieceType::ROOK;
    this->loadTexture();
}

//destructor, no need to do anything
Rook::~Rook() {
    
}

int Rook::getPieceValue() {
    return Rook::_pieceValue;
}

void Rook::draw(RenderWindow& window) {
    window.draw(this->_pieceSprite);
}

//https://github.com/mbusy/chess/tree/master/src
vector<ChessMove> Rook::computePossbibleMoves(const vector<vector<Cell>>& cells) {
    Vector2i pos = this->getPosition();

    vector<ChessMove> possibleMoves;

    //the Rook can move unlimtedly to any line direction
    //there is 4 directions in total
    vector<Vector2i> offsets = {
        Vector2i(1, 0),
        Vector2i(0, 1), Vector2i(0, -1),
        Vector2i(-1, 0)        
    };

    for (int i = 0; i < offsets.size(); i++) {
        Vector2i destination = pos + offsets[i];

        //this while loop will find the longest distance to every direction
        //that the Rook can move to
        while (true) {
            //break if destination is out of board
            if (utilities::assisstants::isOnBoardPosition(destination) == false) {
                break;
            }

            //check if the destination is empty or occupied
            if (cells[destination.x][destination.y]._status == CellStatus::OCCUPIED) {
                //if that cell is occupied,check if that is ally or enemy
                if (cells[destination.x][destination.y]._piece->getPieceColor() != this->_pieceColor) {
                    //if that is enemy, add it to possible moves
                    possibleMoves.push_back(destination);
                }

                break; //always break on this case because we cannot move farther in this direction
            } else {
                //if that cell is empty, add it to possible moves
                //then continue to this direction
                possibleMoves.push_back(destination);

                destination += offsets[i];
            }
        }
    }

    return possibleMoves;
}