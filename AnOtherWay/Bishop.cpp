#include "Bishop.h"
#include <iostream>
using namespace std;

const int Bishop::_pieceValue;

Bishop::Bishop(PieceColor pieceColor) {
    this->_pieceColor = pieceColor;

    this->_pieceType = PieceType::BISHOP;

    this->loadTexture();
}

//destructor, no need to do anything
Bishop::~Bishop() {
    
}

int Bishop::getPieceValue() {
    return Bishop::_pieceValue;
}

void Bishop::draw(RenderWindow& window) {
    window.draw(this->_pieceSprite);
}

vector<ChessMove> Bishop::computePossbibleMoves(const vector<vector<Cell>>& cells) {
    Vector2i pos = this->getPosition();

    vector<ChessMove> possibleMoves;

    //the Bishop can move unlimtedly to any diagonal direction
    //there is 4 directions in total
    vector<Vector2i> offsets = {Vector2i(1, 1), Vector2i(1, -1), Vector2i(-1, 1), Vector2i(-1, -1)};

    for (int i = 0; i < offsets.size(); i++) {
        Vector2i destination = pos + offsets[i];

        //this while loop will find the longest distance to every direction
        //that the Bishop can move to
        while (true) {
            //break if destination is out of board
            if (utilities::assisstants::isOnBoardPosition(destination) == false) {
                break;
            }

            //check if the destination is empty or occpuied
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