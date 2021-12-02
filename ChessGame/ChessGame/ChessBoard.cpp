#include "ChessBoard.h"

ChessBoard::ChessBoard() {
	this->_pieceMoveSelection = nullptr;
	this->_pieceEatenSelection = nullptr;
	this->_blackPieces = nullptr;
	this->_whitePieces = nullptr;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == 0 || i == 1) {
				this->_pieceboard[j][i] = PieceBoard::BlackBoard;
			}
			else if (i == 6 || i == 7) {
				this->_pieceboard[j][i] == PieceBoard::WhiteBoard;
			}
			else {
				this->_pieceboard[j][i] = PieceBoard::EmptyBoard;
			}
		}
	}
}

ChessBoard::~ChessBoard() {
	if (this->_pieceMoveSelection) {
		delete this->_pieceMoveSelection;
		this->_pieceMoveSelection = nullptr;
	}

	if (this->_pieceEatenSelection) {
		delete this->_pieceEatenSelection;
		this->_pieceEatenSelection = nullptr;
	}

	if (this->_blackPieces) {
		delete this->_blackPieces;
		this->_blackPieces = nullptr;
	}

	if (this->_whitePieces) {
		delete this->_whitePieces;
		this->_whitePieces = nullptr;
	}
}

void ChessBoard::createChessBoard() {
	//black side
	this->_blackPieces = new PieceSet;
	this->_blackPieces->createPieceSet(GameColor::Black);

	//white side
	this->_whitePieces = new PieceSet;
	this->_whitePieces->createPieceSet(GameColor::White);

	this->_pieceMoveSelection = nullptr;
	this->_pieceEatenSelection = nullptr;
}

void ChessBoard::updateChessBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			this->_pieceboard[j][i] = PieceBoard::EmptyBoard;
		}
	}

	for (int i = 0; i < this->_blackPieces->getPieceNumber(); i++) {
		this->_pieceboard[this->_blackPieces->_pieces[i]->getCurrentPlace().getColumn()][this->_blackPieces->_pieces[i]->getCurrentPlace().getRow()] = PieceBoard::BlackBoard;
	}

	for (int i = 0; i < this->_whitePieces->getPieceNumber(); i++) {
		this->_pieceboard[this->_whitePieces->_pieces[i]->getCurrentPlace().getColumn()][this->_whitePieces->_pieces[i]->getCurrentPlace().getRow()] = PieceBoard::WhiteBoard;
	}
}

PieceBoard ChessBoard::squareColor(int c, int r) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == r && j == c) {
				if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) {
					return PieceBoard::WhiteBoard;
				}

				return PieceBoard::BlackBoard;
			}
		}
	}
}

void ChessBoard::showToConsole() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->_pieceboard[j][i] == PieceBoard::BlackBoard) {
				cout << "B ";
			}
			else if (this->_pieceboard[j][i] == PieceBoard::WhiteBoard) {
				cout << "W ";
			}
			else {
				cout << "E ";
			}
		}
		cout << "\n";
	}
}

PieceBoard ChessBoard::getPieceBoard(int c, int r) {
	return this->_pieceboard[c][r];
}

void ChessBoard::setBoardImage(string l, string b, string w, string s) {
	this->_boardTexture.loadFromFile(l);
	this->_boardSprite.setTexture(this->_boardTexture);

	this->_selectBlackTexture.loadFromFile(b);
	this->_selectBlackSprite.setTexture(this->_selectBlackTexture);

	this->_selectWhiteTexture.loadFromFile(w);
	this->_selectWhiteSprite.setTexture(this->_selectWhiteTexture);

	this->_possibleMoveTexture.loadFromFile(s);
	this->_possibleMoveSprite.setTexture(this->_possibleMoveTexture);
}

void ChessBoard::drawBoard(GameWindow* w) {
	this->_boardSprite.setPosition(LANDMARK, LANDMARK);

	w->draw(this->_boardSprite);
}

Vector2u ChessBoard::getBoardImageSize() {
	return this->_boardTexture.getSize();
}

void ChessBoard::drawSelectedPiece(GameWindow* w) {
	for (int i = 0; i < this->_blackPieces->getPieceNumber(); i++) {
		if (this->_blackPieces->_pieces[i]->_isSelected == true) {
			if (this->squareColor(this->_blackPieces->_pieces[i]->getCurrentPlace().getColumn(), this->_blackPieces->_pieces[i]->getCurrentPlace().getRow()) == PieceBoard::WhiteBoard) {
				this->_selectWhiteSprite.setPosition(LANDMARK + IMAGE_SIZE * this->_blackPieces->_pieces[i]->getCurrentPlace().getColumn(), LANDMARK + IMAGE_SIZE * this->_blackPieces->_pieces[i]->getCurrentPlace().getRow());

				w->draw(this->_selectWhiteSprite);
			}
			else {
				this->_selectBlackSprite.setPosition(LANDMARK + IMAGE_SIZE * this->_blackPieces->_pieces[i]->getCurrentPlace().getColumn(), LANDMARK + IMAGE_SIZE * this->_blackPieces->_pieces[i]->getCurrentPlace().getRow());

				w->draw(this->_selectBlackSprite);
			}
		}
	}

	for (int i = 0; i < this->_whitePieces->getPieceNumber(); i++) {
		if (this->_whitePieces->_pieces[i]->_isSelected == true) {
			if (this->squareColor(this->_whitePieces->_pieces[i]->getCurrentPlace().getColumn(), this->_whitePieces->_pieces[i]->getCurrentPlace().getRow()) == PieceBoard::WhiteBoard) {
				this->_selectWhiteSprite.setPosition(LANDMARK + IMAGE_SIZE * this->_whitePieces->_pieces[i]->getCurrentPlace().getColumn(), LANDMARK + IMAGE_SIZE * this->_whitePieces->_pieces[i]->getCurrentPlace().getRow());

				w->draw(this->_selectWhiteSprite);
			}
			else {
				this->_selectBlackSprite.setPosition(LANDMARK + IMAGE_SIZE * this->_whitePieces->_pieces[i]->getCurrentPlace().getColumn(), LANDMARK + IMAGE_SIZE * this->_whitePieces->_pieces[i]->getCurrentPlace().getRow());

				w->draw(this->_selectBlackSprite);
			}
		}
	}
}

void ChessBoard::setSelectedPiece(Piece* p) {
	this->_pieceMoveSelection = p;
}

void ChessBoard::setEatenPiece(Piece* p) {
	this->_pieceEatenSelection = p;
	this->_pieceEatenSelection->setCaptured();
}