#include "PieceSet.h"

PieceSet::PieceSet() {
	this->_isLost = false;

	this->_kingPiece = nullptr;
}

PieceSet::~PieceSet() {
	for (int i = 0; i < this->getPieceNumber(); i++) {
		delete this->_pieces[i];
	}

	if (this->_kingPiece) {
		delete this->_kingPiece;
	}
}

void PieceSet::createPieceSet(GameColor color) {
	this->_pieces.clear(); //clear the old one (if there is any)

	if (this->_pieceSetColor == GameColor::Black) {
		GameColor black = GameColor::Black;

		//create 8 (eight) pawns
		for (int i = 0; i < 8; i++) {
			Piece* p = new Pawn(i, 1, black);
			this->_pieces.push_back(p);
		}

		//create 2 (two) rooks
		Piece* r1 = new Rook(0, 0, black);
		this->_pieces.push_back(r1);
		Piece* r2 = new Rook(7, 0, black);
		this->_pieces.push_back(r2);
		
		//create 2 (two) knights
		Piece* kn1 = new Knight(1, 0, black);
		this->_pieces.push_back(kn1);
		Piece* kn2 = new Knight(6, 0, black);
		this->_pieces.push_back(kn2);

		//create 2 (two) bishops
		Piece* b1 = new Bishop(2, 0, black);
		this->_pieces.push_back(b1);
		Piece* b2 = new Bishop(5, 0, black);
		this->_pieces.push_back(b2);
	}
}