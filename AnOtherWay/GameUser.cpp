#include "GameUser.h"

GameUser::GameUser(PieceColor color) {
    this->_score = 0;

    this->_userColor = color;
}

GameUser::~GameUser() {

}

int GameUser::getScore() {
    return this->_score;
}

PieceColor GameUser::getColor() {
    return this->_userColor;
}

void GameUser::setScore(int scr) {
    this->_score = scr;
}

void GameUser::addPiece(PieceType type, const shared_ptr<Piece>& piece) {
    if (piece->getPieceColor() != this->_userColor) {
        throw std::runtime_error("Colors of the piece added and the user don't match");
    }

    weak_ptr<Piece> ptr = piece;
    this->_pieces[type].push_back(ptr);
}

void GameUser::clearPieces() {
    this->_pieces.clear();
}

bool GameUser::isChecked(const vector<vector<Cell>>& cells) {
    //find the position of the King in cells
    Vector2i pos(-1, -1);

    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            if (cells[i][j]._status == CellStatus::EMPTY) {
                continue;
            }
            else if (cells[i][j]._piece->getPieceType() == PieceType::KING && cells[i][j]._piece->getPieceColor() == this->_userColor) {
                pos = Vector2i(i, j);
            }
        }
    }


    //check if the King is found
    if (pos.x == -1 || pos.y == -1) {
        throw std::runtime_error("No King found for this user");
    }

    //check if the King is checked by the Bishops, Rooks or Queen
    vector<vector<Vector2i>> offsets = {
        {Vector2i(1, 1), Vector2i(1, -1), Vector2i(-1, 1), Vector2i(-1, -1),},
        {Vector2i(1, 0), Vector2i(0, 1), Vector2i(0, -1), Vector2i(-1, 0)}
    };

    vector<vector<PieceType>> types = {
        {PieceType::BISHOP, PieceType::QUEEN},
        {PieceType::ROOK, PieceType::QUEEN}
    };

    for (int i = 0; i < offsets.size(); i++) {
        for (int j = 0; j < offsets[i].size(); j++) {
            Vector2i destination = pos + offsets[i][j];

            while (true) {
                if (utilities::assisstants::isOnBoardPosition(destination) == false) {
                    break;
                }

                Cell cell = cells[destination.x][destination.y];

                if (cell._status == CellStatus::OCCUPIED) {
                    if (cell._piece->getPieceColor() != this->_userColor && (cell._piece->getPieceType() == types[i][0] || cell._piece->getPieceType() == types[i][1])) {
                        return true;
                    }
                    else {
                        break;
                    }
                } else {
                    destination += offsets[i][j];
                }
            }
        } 
    }

    //check if the King is checked by Knights
    vector<Vector2i> knightOffsets = {
        Vector2i(2, 1), Vector2i(2, -1),
        Vector2i(1, 2), Vector2i(1, -2),
        Vector2i(-1, 2), Vector2i(-1, -2),
        Vector2i(-2, 1), Vector2i(-2, -1)
    };

    for (int i = 0; i < knightOffsets.size(); i++) {
        Vector2i destination = pos + knightOffsets[i];

        if (utilities::assisstants::isOnBoardPosition(destination) == false) {
            continue;
        }

        Cell cell = cells[destination.x][destination.y];

        if (cell._status == CellStatus::OCCUPIED) {
            if (cell._piece->getPieceColor() != this->_userColor && cell._piece->getPieceType() == PieceType::KNIGHT) {
                return true;
            }
        }
    }

    //check if the King is checked by Pawns
    float xoffset;
    if (this->_userColor == PieceColor::WHITE) {
        xoffset = -1;
    } else {
        xoffset = 1;
    }

    vector<Vector2i> pawnOffsets = {
        Vector2i(xoffset, 1), Vector2i(xoffset, -1)
    };

    for (int i = 0; i < pawnOffsets.size(); i++) {
        Vector2i destination = pos + pawnOffsets[i];

        if (utilities::assisstants::isOnBoardPosition(destination) == false) {
            continue;
        }

        Cell cell = cells[destination.x][destination.y];

        if (cell._status == CellStatus::OCCUPIED) {
            if (cell._piece->getPieceColor() != this->_userColor && cell._piece->getPieceType() == PieceType::PAWN) {
                return true;
            }
        }
    }

    //check if the King is checked by the King
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            Vector2i destination = pos + Vector2i(i, j);

            if ((i == 0 && j == 0) || utilities::assisstants::isOnBoardPosition(destination) == false) {
                continue;
            }

            Cell cell = cells[destination.x][destination.y];

            if (cell._status == CellStatus::OCCUPIED) {
                if (cell._piece->getPieceColor() != this->_userColor && cell._piece->getPieceType() == PieceType::KING) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool GameUser::hasLegalMoves(const vector<vector<Cell>>& cells) {
    vector<ChessMove> possibleMoves;

    Vector2i pos;

    vector<vector<Cell>> copyCells;

    shared_ptr<Piece> king = nullptr;

    for (const auto& element : this->_pieces) {
        for (const auto& piecePtr : element.second) {
            if (piecePtr.expired() == true) {
                continue;
            }

            auto piece = piecePtr.lock();

            //we don't study King's moves in this loop
            if (piece->getPieceType() == PieceType::KING) {
                king = piece;
                continue;
            }

            pos = piece->getPosition();
            possibleMoves = piece->computePossbibleMoves(cells);

            for (const auto& move : possibleMoves) {
                copyCells = cells;

                copyCells[move._position.x][move._position.y]._piece = std::move(copyCells[pos.x][pos.y]._piece);

                copyCells[pos.x][pos.y]._status = CellStatus::EMPTY;
                copyCells[move._position.x][move._position.y]._status = CellStatus::OCCUPIED;

                if (this->isChecked(copyCells) == false){
                    return true;
                }
            }
        }
    }

    if (king == nullptr) {
        throw std::runtime_error("No King found for this user");
    }

    pos = king->getPosition();
    possibleMoves = king->computePossbibleMoves(cells);

    for (const auto& move : possibleMoves) {
        copyCells = cells;

        copyCells[move._position.x][move._position.y]._piece = std::move(copyCells[pos.x][pos.y]._piece);

        copyCells[pos.x][pos.y]._status = CellStatus::EMPTY;
        copyCells[move._position.x][move._position.y]._status = CellStatus::OCCUPIED;

        if (this->isChecked(copyCells) == false) {
            return true;
        }
    }

    return false;
}

void GameUser::checkKingCell(bool check, vector<vector<Cell>>& cells) {
    if (auto king = this->_pieces[PieceType::KING].at(0).lock()) {
        auto pos = king->getPosition();
        cells[pos.x][pos.y].setIsChecked(check);
    } else {
        throw std::runtime_error("No King found for this user");
    }
}