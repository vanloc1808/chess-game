#include "PieceSet.h"

PieceSet::PieceSet() {
	this->_isLost = false;

	this->_kingPiece = nullptr;
}

PieceSet::~PieceSet() {
	for (int i = 0; i < this->getPieceNumber(); i++) {
		if (this->_pieces[i]) {
			delete this->_pieces[i];
			this->_pieces[i] = nullptr;
		}
	}

	/*if (this->_kingPiece) {
		delete this->_kingPiece;
		this->_kingPiece = nullptr;
	}*/
}

void PieceSet::createPieceSet(GameColor color) {
	this->_pieces.clear(); //clear the old one (if there is any)

	if (color == GameColor::Black) {
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

		//create king
		Piece* k = new King(4, 0, black);
		this->_kingPiece = k;
		this->_pieces.push_back(k);

		//create queen
		Piece* q = new Queen(3, 0, black);
		this->_pieces.push_back(q);
	}
	else {
		GameColor white = GameColor::White;

		//create 8 (eight) pawns
		for (int i = 0; i < 8; i++) {
			Piece* p = new Pawn(i, 6, white);
			this->_pieces.push_back(p);
		}

		//create 2 (two) rooks
		Piece* r1 = new Rook(0, 7, white);
		this->_pieces.push_back(r1);
		Piece* r2 = new Rook(7, 7, white);
		this->_pieces.push_back(r2);

		//create 2 (two) knights
		Piece* kn1 = new Knight(1, 7, white);
		this->_pieces.push_back(kn1);
		Piece* kn2 = new Knight(6, 7, white);
		this->_pieces.push_back(kn2);

		//create 2 (two) bishops
		Piece* b1 = new Bishop(2, 7, white);
		this->_pieces.push_back(b1);
		Piece* b2 = new Bishop(5, 7, white);
		this->_pieces.push_back(b2);

		//create king
		Piece* k = new King(4, 7, white);
		this->_kingPiece = k;
		this->_pieces.push_back(k);

		//create queen
		Piece* q = new Queen(3, 7, white);
		this->_pieces.push_back(q);
	}
	cout << this->_pieces.size() << "\n";
}

int PieceSet::getPieceNumber() {
	return this->_pieces.size();
}

void PieceSet::unselectPiece() {
	for (int i = 0; i < this->_pieces.size(); i++) {
		this->_pieces[i]->unsetSelected();
	}
}

void PieceSet::erasePiece() {
	for (int i = 0; i < this->_pieces.size(); i++) {
		if (this->_pieces[i]->_isErase == true) {
			if (typeid(*this->_pieces[i]) == typeid(Pawn)) {
				//if that is the pawn
				if (this->_pieces[i]->getPieceColor() == GameColor::Black) {
					this->_pieces[i]->changeTextureLocation("images/pieces/SmallBlackPawn.png");
				}
				else {
					this->_pieces[i]->changeTextureLocation("images/pieces/SmallWhitePawn.png");
				}
			}
			else if (typeid(*this->_pieces[i]) == typeid(Rook)) {
				//if that is the rook
				if (this->_pieces[i]->getPieceColor() == GameColor::Black) {
					this->_pieces[i]->changeTextureLocation("images/pieces/SmallBlackRook.png");
				}
				else {
					this->_pieces[i]->changeTextureLocation("images/pieces/SmallWhiteRook.png");
				}
			}
			else if (typeid(*this->_pieces[i]) == typeid(Knight)) {
				//if that is the knight
				if (this->_pieces[i]->getPieceColor() == GameColor::Black) {
					this->_pieces[i]->changeTextureLocation("images/pieces/SmallBlackKnight.png");
				}
				else {
					this->_pieces[i]->changeTextureLocation("images/pieces/SmallWhiteKnight.png");
				}
			}
			else if (typeid(*this->_pieces[i]) == typeid(Bishop)) {
				//if that is the bishop
				if (this->_pieces[i]->getPieceColor() == GameColor::Black) {
					this->_pieces[i]->changeTextureLocation("images/pieces/SmallBlackBishop.png");
				}
				else {
					this->_pieces[i]->changeTextureLocation("images/pieces/SmallWhiteBishop.png");
				}
			}
			else if (typeid(*this->_pieces[i]) == typeid(Queen)) {
				//if that is the queen
				if (this->_pieces[i]->getPieceColor() == GameColor::Black) {
					this->_pieces[i]->changeTextureLocation("images/pieces/SmallBlackQueen.png");
				}
				else {
					this->_pieces[i]->changeTextureLocation("images/pieces/SmallWhiteQueen.png");
				}
			}
			else {
				this->loseKing();
			}

			this->_eatenPieces.push_back(this->_pieces[i]);

			this->_pieces.erase(this->_pieces.begin() + i);
		}
	}
}

void PieceSet::erasePieceAtIndex(int i) {
	this->_pieces.erase(this->_pieces.begin() + i);
}

void PieceSet::pawnPromotion(Piece* p, string pieceType) {
	Piece* replacePiece;

	Vector2i posPieceReplace;

	int check = this->findPieceInVector(p);

	if (p->checkPieceChange() == true) {
		if (check != -1) {
			posPieceReplace = Vector2i(this->_pieces[check]->getCurrentPlace().getColumn(), this->_pieces[check]->getCurrentPlace().getRow());

			if (pieceType == "Knight") {
				GameColor color = this->_pieces[check]->getPieceColor();

				replacePiece = new Knight(posPieceReplace.x, posPieceReplace.y, color);
			}
			else if (pieceType == "Bishop") {
				GameColor color = this->_pieces[check]->getPieceColor();

				replacePiece = new Bishop(posPieceReplace.x, posPieceReplace.y, color);
			}
			else if (pieceType == "Rook") {
				GameColor color = this->_pieces[check]->getPieceColor();

				replacePiece = new Rook(posPieceReplace.x, posPieceReplace.y, color);
			}
			else if (pieceType == "Queen") {
				GameColor color = this->_pieces[check]->getPieceColor();

				replacePiece = new Queen(posPieceReplace.x, posPieceReplace.y, color);
			}

			this->erasePieceAtIndex(check);
			this->_pieces.push_back(replacePiece);
		}
	}
}

void PieceSet::unselecEaten() {
	for (int i = 0; i < this->_pieces.size(); i++) {
		this->_pieces[i]->unsetCaptured();
	}
}

Piece* PieceSet::cpuSelectionPiece(int c, int r) {
	for (int i = 0; i < this->_pieces.size(); i++) {
		if (this->_pieces[i]->getCurrentPlace().getColumn() == c && this->_pieces[i]->getCurrentPlace().getRow() == r) {
			return this->_pieces[i];
		}
	}
}

int PieceSet::findPieceInVector(Piece* p) {
	for (int i = 0; i < this->_pieces.size(); i++) {
		if (p->getCurrentPlace().getColumn() == this->_pieces[i]->getCurrentPlace().getColumn() && p->getCurrentPlace().getRow() == this->_pieces[i]->getCurrentPlace().getRow()) {
			return i;
		}
	}

	return -1;
}

bool PieceSet::castling(Piece* p, PieceBoard pb[][8]) {
	int emptyCell = 0;
	int check = 0;

	if (p->getPieceColor() == GameColor::Black) {
		//has the king moved yet?
		if (p->getCurrentPlace().getColumn() == 4 && p->getCurrentPlace().getRow() == 0) {
			//has the rook moved yet?
			if (typeid(*cpuSelectionPiece(0, 0)) == typeid(Rook)) {
				//count the number of empty cells
				for (int i = 1; i <= 3; i++) {
					if (pb[i][0] == PieceBoard::EmptyBoard) {
						emptyCell++;
					}
				}
			}
			if (emptyCell == 3) {
				p->addPML(Vector2i(0, 0));
				check++;
			}

			emptyCell = 0;
			if (typeid(*cpuSelectionPiece(7, 0)) == typeid(Rook)) {
				for (int i = 5; i <= 6; i++) {
					if (pb[i][0] == PieceBoard::EmptyBoard) {
						emptyCell++;
					}
				}
			}
			if (emptyCell == 2) {
				p->addPML(Vector2i(7, 0));
				check++;
			}
		}
	}
	else {
		//has the king moved yet?
		if (p->getCurrentPlace().getColumn() == 4 && p->getCurrentPlace().getRow() == 7) {
			//has the rook moved yet?
			if (typeid(*cpuSelectionPiece(0, 7)) == typeid(Rook)) {
				//count the number of empty cells
				for (int i = 1; i <= 3; i++) {
					if (pb[i][7] == PieceBoard::EmptyBoard) {
						emptyCell++;
					}
				}
			}
			if (emptyCell == 3) {
				p->addPML(Vector2i(0, 7));
				check++;
			}

			emptyCell = 0;
			if (typeid(*cpuSelectionPiece(7, 7)) == typeid(Rook)) {
				for (int i = 5; i <= 6; i++) {
					if (pb[i][7] == PieceBoard::EmptyBoard) {
						emptyCell++;
					}
				}
			}
			if (emptyCell == 2) {
				p->addPML(Vector2i(7, 7));
				check++;
			}
		}
	}

	if (check > 0) {
		return true;
	}
	
	return false;
}

GameColor PieceSet::getSetColor() {
	return this->_pieceSetColor;
}

void PieceSet::loseKing() {
	this->_isLost = true;
}

Vector2i PieceSet::getKingPosition() {
	return Vector2i(this->_kingPiece->getCurrentPlace().getColumn(), this->_kingPiece->getCurrentPlace().getRow());
}