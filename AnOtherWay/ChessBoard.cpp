#include "ChessBoard.h"

ChessBoard::ChessBoard(RenderWindow& window) : ChessBoard("ChessBoard", window) {

}

ChessBoard::ChessBoard(const string& name, RenderWindow& window) : _window(window), _whiteUser(PieceColor::WHITE), _blackUser(PieceColor::BLACK) {
    this->_window.setFramerateLimit(120);

    this->_window.setTitle(name);
}

void ChessBoard::run() {
    cout << "Started to run\n";
    //load the sound
    utilities::AudioPlayer::loadSound();
    
    cout << "Started to reset\n";
    this->reset();
    cout << "Reset successfully\n";

    cout << "Started to display\n";
    this->_window.display();
    cout << "Display successfully\n";

    while (this->_window.isOpen() == true) {
        Event event;
        cout << "In loop if isOpen()\n";
        while (this->_window.pollEvent(event) == true) {
            if (event.type == Event::Closed) {
                cout << "Closed event\n";
                this->_window.close();
            } 
            //exit by press escape key
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                cout << "Esc pressed event\n";
                this->_window.close();
            }

            if (Mouse::isButtonPressed(Mouse::Left)) {
                cout << "Left mouse button pressed\n";
                this->onMouseClicked(Mouse::getPosition(this->_window));
            }
        }
        cout << "Before clearing\n";
        this->_window.clear(Color(150, 150, 150));
        cout << "After clearing\n";
        cout << "Before drawing\n";
        this->drawBoard();
        cout << "After drawing\n";
        cout << "Before displaying\n";
        this->_window.display();
        cout << "After displaying\n";
    }
}

void ChessBoard::reset() {
    this->_blackUser.setScore(0);
    this->_whiteUser.setScore(0);
    cout << "Set score successfully\n";
    this->_blackUser.clearPieces();
    this->_whiteUser.clearPieces();
    cout << "Clear pieces successfully\n";
    this->initializeBoard();
    cout << "Initialize board successfully\n";
    this->populateBoard();
    cout << "Populate board successfully\n";
}

void ChessBoard::initializeBoard() {
    bool white = true;

    //specify the size of a cell
    utilities::Settings::updateCellSize(this->_window.getSize());

    float cellSize = utilities::Settings::getCellSize();

    this->_cells.clear();
    this->_cells.resize(BOARD_WIDTH);

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        this->_cells[i].resize(BOARD_WIDTH);

        for (int j = 0; j < BOARD_WIDTH; j++) {
            this->_cells[i][j]._rect.setSize(Vector2f(cellSize, cellSize));

            Color colorToFill;
            if (white == true) {
                colorToFill = utilities::Settings::getWhiteSquareColor();
            } else {
                colorToFill = utilities::Settings::getBlackSquareColor();
            }
            this->_cells[i][j]._rect.setFillColor(colorToFill);

            this->_cells[i][j]._rect.setPosition(utilities::assisstants::convertToDrawablePosition(i, j));

            this->_cells[i][j]._checkedRect = this->_cells[i][j]._rect;

            this->_cells[i][j]._checkedRect.setFillColor(utilities::Settings::getCheckedColor());

            this->_cells[i][j]._status = CellStatus::EMPTY;

            this->_cells[i][j]._highlightedCircle.setFillColor(utilities::Settings::getHighlightedColor());

            this->_cells[i][j]._highlightedCircle.setOutlineColor(utilities::Settings::getHighlightedColor());

            this->_cells[i][j]._highlightedCircle.setRadius(cellSize / 2.00);

            this->_cells[i][j]._highlightedCircle.setOrigin(cellSize / 2.00, cellSize / 2.00);

            Vector2f pos = utilities::assisstants::convertToDrawablePosition(i, j);
            this->_cells[i][j]._highlightedCircle.setPosition(pos.x + cellSize / 2.00, pos.y + cellSize/2.00);

            white = !white;
        }

        white = !white;
    }
}

void ChessBoard::populateBoard() {
    if (this->_cells.empty() == true) {
        throw std::runtime_error("Cannot populate chess board because it has not been initialized yet!\n");
    }

    Sprite sprite;

    float cellSize = utilities::Settings::getCellSize();
    cout << "Started to create pieces vector\n";
    vector<shared_ptr<Piece>> pieces = {
        make_shared<Rook>(Rook(PieceColor::BLACK)),
        make_shared<Knight>(Knight(PieceColor::BLACK)),
        make_shared<Bishop>(Bishop(PieceColor::BLACK)),
        make_shared<Queen>(Queen(PieceColor::BLACK)),
        make_shared<King>(King(PieceColor::BLACK)),
        make_shared<Bishop>(Bishop(PieceColor::BLACK)),
        make_shared<Knight>(Knight(PieceColor::BLACK)),
        make_shared<Rook>(Rook(PieceColor::BLACK)),

        make_shared<Rook>(Rook(PieceColor::WHITE)),
        make_shared<Knight>(Knight(PieceColor::WHITE)),
        make_shared<Bishop>(Bishop(PieceColor::WHITE)),
        make_shared<Queen>(Queen(PieceColor::WHITE)),
        make_shared<King>(King(PieceColor::WHITE)),
        make_shared<Bishop>(Bishop(PieceColor::WHITE)),
        make_shared<Knight>(Knight(PieceColor::WHITE)),
        make_shared<Rook>(Rook(PieceColor::WHITE))
    };
    cout << "Created pieces vector successfully\n";
    for (int i = 0; i < pieces.size(); i++) {
        cout << "In loop with i = " << i << "\n";
        int row = (i / 8) * 7;
        int col = i % 8;

        for (int j = 0; j <= 1; j++) {
            cout << "In sub-loop with j = " << j << "\n";
            if (j == 0) {
                this->_cells[row][col]._piece = pieces[i];
            } else if (row == 0) {
                row++;
                this->_cells[row][col]._piece = make_shared<Pawn>(Pawn(PieceColor::BLACK));
            } else if (row != 0) {
                row--;
                this->_cells[row][col]._piece = make_shared<Pawn>(Pawn(PieceColor::WHITE));
                
            }
            cout << "Pass the first conditional statement\n";

            this->_cells[row][col]._status = CellStatus::OCCUPIED;
            cout << "Started to set the position\n";
            this->_cells[row][col]._piece->getPieceSprite().setPosition(this->_cells[row][col]._rect.getPosition());
            cout << "Set the position successfully\n";
            //add the pieces to the respective players
            cout << "Started to add pieces\n";
            if (this->_cells[row][col]._piece->getPieceColor() == PieceColor::WHITE) {
                this->_whiteUser.addPiece(this->_cells[row][col]._piece->getPieceType(), this->_cells[row][col]._piece);
            } else {
                this->_blackUser.addPiece(this->_cells[row][col]._piece->getPieceType(), this->_cells[row][col]._piece);
            }
            cout << "Added pieces successfully\n";
        }
    }

    //set the current user to white user
    this->_currentUser = make_shared<GameUser>(this->_whiteUser);
}

void ChessBoard::drawBoard() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            //draw the cell rectangle (square actually)
            this->_window.draw(this->_cells[i][j]._rect);

            //check the king's cell if we detec a check
            if (this->_cells[i][j].getIsChecked() == true) {
                this->_window.draw(this->_cells[i][j]._checkedRect);
            }

            //draw the highlighted circle if the cell is highlighted
            if (this->_cells[i][j]._status == CellStatus::HIGHLIGHTED) {
                this->_window.draw(this->_cells[i][j]._highlightedCircle);
            }

            //draw the piece if there is one
            if (this->_cells[i][j]._piece.get() != nullptr) {
                this->_cells[i][j]._piece->draw(this->_window);
            }
        }
    }
}

void ChessBoard::showPossibleMoves(const vector<ChessMove>& positions){
    for (int i = 0; i < positions.size(); i++) {
        this->_cells[positions[i]._position.x][positions[i]._position.y].highlight(true);
    }
}

void ChessBoard::movePiece(Cell& originCell, Cell& destinationCell) {
    if (this->_cells.empty() == true) {
        throw std::runtime_error("Cannot move pieces because the board is empty");
    } else if (originCell._status == CellStatus::EMPTY) {
        throw std::runtime_error("Cannot move an unexisted piece");
    }

    //check that the destination is valid,
    //aka it exists in the possible moves vector
    ChessMove requiredMove;

    Vector2i destinationIndex = utilities::assisstants::convertToBoardIndex(destinationCell._rect.getPosition());

    for (const auto& move : this->_possibleMoves) {
        if (move._position == destinationIndex) {
            requiredMove = move;
            break;
        }
    }

    if (requiredMove._position.x == -1 || requiredMove._position.y == -1) {
        throw std::runtime_error("Cannot move to an invalid position");
    }

    //capture the piece at destination if possible
    if (destinationCell._piece.get() != nullptr) {
        this->capturePiece(destinationCell);
        utilities::AudioPlayer::playSound(GameSound::CAPTURE);
    } else {
        utilities::AudioPlayer::playSound(GameSound::MOVE);
    }

    //process the pawn promotion, short castiling and long castling
    int row;
    if (this->_currentUser->getColor() == PieceColor::WHITE) {
        row = 7;
    } else {
        row = 0;
    }

    if (requiredMove._type == MoveType::PROMOTION) {
        this->promotePiece(originCell);
    } else if (requiredMove._type == MoveType::LONG_CASTLING) {
        this->_cells[row][3]._piece = std::move(this->_cells[row][0]._piece);

        this->_cells[row][3]._piece->getPieceSprite().setPosition(this->_cells[row][3]._rect.getPosition());

        this->_cells[row][3]._piece->markAsMoved();
    } else if (requiredMove._type == MoveType::SHORT_CASTLING) {
        this->_cells[row][5]._piece = std::move(this->_cells[row][7]._piece);

        this->_cells[row][5]._piece->getPieceSprite().setPosition(this->_cells[row][5]._rect.getPosition());

        this->_cells[row][5]._piece->markAsMoved();
    } else if (requiredMove._type == MoveType::NONE) {
        //do nothing;
    }

    //move the piece to the destination
    destinationCell._piece = std::move(originCell._piece);

    //update the position of piece
    destinationCell._piece->getPieceSprite().setPosition(destinationCell._rect.getPosition());

    //specify the moved piece
    destinationCell._piece->markAsMoved();

    //update the status of cells
    originCell._status = CellStatus::EMPTY;
    destinationCell._status = CellStatus::OCCUPIED;
}

void ChessBoard::capturePiece(Cell& cell) {
    if (this->_cells.empty() == true) {
        throw std::runtime_error("Cannot capture pieces because the board is empty");
    } else if (cell._status == CellStatus::EMPTY) {
        throw std::runtime_error("Cannot capture an unexisted piece");
    }

    //increase the score of the user who have just captured enemy's piece
    this->_currentUser->setScore(this->_currentUser->getScore() + cell._piece->getPieceValue());

    //remove the captured piece;
    cell._piece = nullptr;
}

void ChessBoard::promotePiece(Cell& cell) {
    vector<RectangleShape> rectangles;

    vector<shared_ptr<Piece>> pieces = {
        make_shared<Rook>(Rook(this->_currentUser->getColor())),
        make_shared<Knight>(Knight(this->_currentUser->getColor())),
        make_shared<Bishop>(Bishop(this->_currentUser->getColor())),
        make_shared<Queen>(Queen(this->_currentUser->getColor()))
    };

    for (int i = 0; i < pieces.size(); i++) {
        rectangles.push_back(this->_cells[i + 2][0]._checkedRect);

        pieces[i]->getPieceSprite().setPosition(rectangles[i].getPosition());

        this->_window.draw(rectangles[i]);
        pieces[i]->draw(this->_window);
    }

    this->_window.display();

    //wait for the user to click
    Event event;
    int selectedRow = -1;

    while (true) {
        this->_window.waitEvent(event);

        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
            this->_window.close();
            
            break;
        }

        if (Mouse::isButtonPressed(Mouse::Left) == true) {
            Vector2i pos = Mouse::getPosition(this->_window);

            if (utilities::assisstants::isOnWindowPosition(pos) == false) {
                continue;
            } else {
                selectedRow = pos.y / utilities::Settings::getCellSize();

                break;
            }
        }
    }

    cell._piece = nullptr;

    PieceColor color = this->_currentUser->getColor();

    if (selectedRow == 2) {
        cell._piece = make_shared<Rook>(Rook(color));
    } else if (selectedRow == 3) {
        cell._piece = make_shared<Knight>(Knight(color));
    } else if (selectedRow == 4) {
        cell._piece = make_shared<Bishop>(Bishop(color));
    } else if (selectedRow == 5) {
        cell._piece = make_shared<Queen>(Queen(color));
    } else {
        cell._piece = make_shared<Queen>(Queen(color));
    }
}

void ChessBoard::clearHighlightedCells() {
    for (auto&& row : this->_cells) {
        for (auto&& cell : row) {
            cell.highlight(false);
        }
    }
}

void ChessBoard::onMouseClicked(const Vector2i& position) {
    cout << "onMouseClicked function\n";
    //check if the position is on the window
    if (utilities::assisstants::isOnWindowPosition(position) == false) {
        return;
    }
    cout << "After conditional statement 1\n";

    Vector2i cellPosition(position.y / utilities::Settings::getCellSize(), position.x / utilities::Settings::getCellSize());

    if (this->_cells[cellPosition.x][cellPosition.y]._status == CellStatus::HIGHLIGHTED) {
        cout << "Before onHighlighted... function\n";
        this->onHighlightedCellClicked(cellPosition);
        cout << "After onHighlighted... function\n";
    } else if (this->_cells[cellPosition.x][cellPosition.y]._status == CellStatus::OCCUPIED) {
        cout << "Before onOccupied... function\n";
        this->onOccupiedCellClicked(cellPosition);
        cout << "After onOccupied... function\n";
    } else if (this->_cells[cellPosition.x][cellPosition.y]._status == CellStatus::EMPTY) {
        cout << "Before onEmpty... function\n";
        this->clearHighlightedCells();
        cout << "After onEmpty... function\n";
    }
}

void ChessBoard::onOccupiedCellClicked(const Vector2i& position) {
    cout << "Before clear highlighted\n";
    this->clearHighlightedCells();
    cout << "After clear highlighted\n";

    //if the player's color is not the same as the clicked piece, return
    if (this->_currentUser->getColor() != this->_cells[position.x][position.y]._piece->getPieceColor()) {
        return;
    }

    cout << "Pass the conditional statement 1\n";

    this->_selectedPosition = Vector2i(position.x, position.y);
    cout << "Successfully create selectedPosition\n";

    //filter the possible moves based on the checks
    vector<vector<Cell>> copyCells;
    cout << "Initiazlied copyCells\n";
    this->_possibleMoves.clear();
    cout << "Successfully cleared possibleMoves\n";

    cout << "Before creating moves\n";
    vector<ChessMove> moves = this->_cells[position.x][position.y]._piece->computePossbibleMoves(this->_cells);
    cout << "After creating moves\n";
    
    int row;
    if (this->_currentUser->getColor() == PieceColor::WHITE) {
        row = 7;
    } else {
        row = 0;
    }
    cout << "Row = " << row << "\n";

    bool isShortCastling = false;
    bool isLongCastling = false;

    for (int i = 0; i < moves.size(); i++) {
        if (moves[i]._type == MoveType::SHORT_CASTLING || moves[i]._type == MoveType::LONG_CASTLING) {
            if (this->_currentUser->isChecked(this->_cells) == true) {
                continue;
            }
        }
        cout << "Pass the long/short castling condition\n";

        copyCells = this->_cells;
        copyCells[moves[i]._position.x][moves[i]._position.y]._piece = nullptr;
        copyCells[moves[i]._position.x][moves[i]._position.y]._piece = std::move(copyCells[position.x][position.y]._piece);
        copyCells[position.x][position.y]._status = CellStatus::EMPTY;
        copyCells[moves[i]._position.x][moves[i]._position.y]._status = CellStatus::OCCUPIED;

        cout << "Before the conditional checked copyCells\n";
        if (this->_currentUser->isChecked(copyCells) == false) {
            cout << "To the statement\n";
            if (moves[i]._position == Vector2i(row, 5)) {
                cout << "Row, 5\n";
                isShortCastling = true;
            } else if (moves[i]._position == Vector2i(row, 3)) {
                cout << "Row, 3\n";
                isLongCastling = true;
            } else if (moves[i]._type == MoveType::SHORT_CASTLING && isShortCastling == false) {
                cout << "Short castle\n";
                continue;
            } else if (moves[i]._type == MoveType::LONG_CASTLING && isLongCastling == false) {
                cout << "Long castle\n";
                continue;
            }
            cout << "Before pushing back\n";
            this->_possibleMoves.push_back(moves[i]);
            cout << "After pushing back\n";
        }
        cout << "After the conditional checked copyCells\n";
    }
    cout << "Before showing possible moves\n";
    this->showPossibleMoves(this->_possibleMoves);
    cout << "After showing possible moves\n";
}

void ChessBoard::onHighlightedCellClicked(const Vector2i& position) {
    //remove any possible checks for the current user before ending turn
    this->_currentUser->checkKingCell(false, this->_cells);

    this->movePiece(this->_cells[this->_selectedPosition.x][this->_selectedPosition.y], this->_cells[position.x][position.y]);

    this->clearHighlightedCells();

    //change the current user
    GameUser user = this->_currentUser->getColor() == PieceColor::WHITE ? this->_blackUser : this->_whiteUser;
    this->_currentUser = make_shared<GameUser>(user);

    bool hasMoves = this->_currentUser->hasLegalMoves(this->_cells);
    
    string player;
    if (this->_currentUser->getColor() == PieceColor::WHITE) {
        player = "Black";
    } else {
        player = "White";
    }

    if (this->_currentUser->isChecked(this->_cells) == true) {
        this->_currentUser->checkKingCell(true, this->_cells);
        utilities::AudioPlayer::playSound(GameSound::CHECK);

        if (hasMoves == false) {
            utilities::AudioPlayer::playSound(GameSound::CHECKMATE);
            cout << player << " is the winner!\n";
        }
    } else {
        this->_currentUser->checkKingCell(false, this->_cells);

        if (hasMoves == false) {
            utilities::AudioPlayer::playSound(GameSound::STALEMATE);
            cout << "Stalemate!\n";
        }
    }
}