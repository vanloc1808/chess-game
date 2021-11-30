//#include <iostream>
//#include "Player.h"
//
//
//
//using namespace std;
//
//Player::Player(string name, bool color) : m_name(name), m_color(color), m_isChess(false), m_isMatt(false)
//{
//	//Khởi tạo bàn cờ với hàm init 
//	initPieceList();
//	//Clear các quân cờ bị ăn cho chắc ăn
//	//Chưa chơi mà bị ăn rồi thì buồn lắm
//	m_capturedPieces.clear();
//}
//
//Player::~Player()
//{
//	
//}
//
//string Player::getName() const
//{
//	return m_name;
//}
//
////Cái này thì WHITE = 1 nha
//bool Player::getColor() const
//{
//	return m_color;
//}
//
////Cái này thì là khởi tạo cái chỉ định màu
//void Player::setColor(bool color)
//{
//	m_color = color;
//}
//
//vector <Piece>& Player::getListPieces()
//{
//	return m_listPieces;
//}
//
//vector <Piece>& Player::getCapturedPieces()
//{
//	return m_capturedPieces;
//}
////	//Piece(bool color = 1, string name = "", int row = 0, int column = 0); 
//	//Các quân cờ gồm có màu tên quân cờ vị trí hiện tại
//void Player::initPieceList()
//{
//	if (m_color)// 1: WHITE
//	{
//		m_listPieces.push_back(new Piece());//("Pawn1", new Pawn(m_color, "Pawn1", 1, 0));
//		m_listPieces.push_back(Piece());//("Pawn2", new Pawn(m_color, "Pawn2", 1, 1));
//		m_listPieces.push_back(Piece());//("Pawn3", new Pawn(m_color, "Pawn3", 1, 2)));
//		m_listPieces.push_back(Piece());//("Pawn4", new Pawn(m_color, "Pawn4", 1, 3)));
//		m_listPieces.push_back(Piece());//("Pawn5", new Pawn(m_color, "Pawn5", 1, 4)));
//		m_listPieces.push_back(Piece());//("Pawn6", new Pawn(m_color, "Pawn6", 1, 5)));
//		m_listPieces.push_back(Piece());//("Pawn7", new Pawn(m_color, "Pawn7", 1, 6)));
//		m_listPieces.push_back(Piece());//("Pawn8", new Pawn(m_color, "Pawn8", 1, 7)));
//		m_listPieces.push_back(Piece());//("Rook1", new Rook(m_color, "Rook1", 0, 0)));
//		m_listPieces.push_back(Piece());//("Rook2", new Rook(m_color, "Rook2", 0, 7)));
//		m_listPieces.push_back(Piece());//("Knight1", new Knight(m_color, "Knight1", 0, 1)));
//		m_listPieces.push_back(Piece());//("Knight2", new Knight(m_color, "Knight2", 0, 6)));
//		m_listPieces.push_back(Piece());//("Bishop1", new Bishop(m_color, "Bishop1", 0, 2)));
//		m_listPieces.push_back(Piece());//("Bishop2", new Bishop(m_color, "Bishop2", 0, 5)));
//		m_listPieces.push_back(Piece());//("King", new King(m_color, "King", 0, 4)));
//		m_listPieces.push_back(Piece());//("Queen", new Queen(m_color, "Queen", 0, 3)));
//	}
//	else
//	{
//		m_listPieces.push_back(Piece());//("Pawn1", new Pawn(m_color, "Pawn1", 6, 0)));
//		m_listPieces.push_back(Piece());//("Pawn2", new Pawn(m_color, "Pawn2", 6, 1)));
//		m_listPieces.push_back(Piece());//("Pawn3", new Pawn(m_color, "Pawn3", 6, 2)));
//		m_listPieces.push_back(Piece());//("Pawn4", new Pawn(m_color, "Pawn4", 6, 3)));
//		m_listPieces.push_back(Piece());//("Pawn5", new Pawn(m_color, "Pawn5", 6, 4)));
//		m_listPieces.push_back(Piece());//("Pawn6", new Pawn(m_color, "Pawn6", 6, 5)));
//		m_listPieces.push_back(Piece());//("Pawn7", new Pawn(m_color, "Pawn7", 6, 6)));
//		m_listPieces.push_back(Piece());//("Pawn8", new Pawn(m_color, "Pawn8", 6, 7)));
//		m_listPieces.push_back(Piece());//("Rook1", new Rook(m_color, "Rook1", 7, 0)));
//		m_listPieces.push_back(Piece());//("Rook2", new Rook(m_color, "Rook2", 7, 7)));
//		m_listPieces.push_back(Piece());//("Knight1", new Knight(m_color, "Knight1", 7, 1)));
//		m_listPieces.push_back(Piece());//("Knight2", new Knight(m_color, "Knight2", 7, 6)));
//		m_listPieces.push_back(Piece());//("Bishop1", new Bishop(m_color, "Bishop1", 7, 2)));
//		m_listPieces.push_back(Piece());//("Bishop2", new Bishop(m_color, "Bishop2", 7, 5)));
//		m_listPieces.push_back(Piece());//("King", new King(m_color, "King", 7, 4)));
//		m_listPieces.push_back(Piece());//("Queen", new Queen(m_color, "Queen", 7, 3)));
//
//	}
//}
//
//void Player::addToCapturedList(Piece* p)
//{
//	m_capturedPieces.push_back(*p);
//}
//
//void Player::removeToCapturedList(string name)
//{
//	for (int i = 0; i < m_capturedPieces.size(); i++) {
//		//if(m_capturedPieces[i].getName() == name)
//		{ 
//			m_capturedPieces.erase(m_capturedPieces.begin() + i);
//			return;
//		}
//	}
//}
//
//void Player::addToListPiece(Piece* p)
//{
//	m_listPieces.push_back(*p);
//}
//
//void Player::removeToListPiece(std::string name)
//{
//	for (int i = 0; i < m_listPieces.size(); i++) {
//		//if(m_capturedPieces[i].getName() == name)
//		{
//			m_listPieces.erase(m_listPieces.begin() + i);
//			return;
//		}
//	}
//}
//
//bool Player::canTake(Piece* p) const
//{
//	return m_color == p->getColor();
//}
//bool Player::canEat(Piece* p) const
//{
//	return m_color != p->getColor();
//}
//bool Player::getIsChess() const
//{
//	return m_isChess;
//}
//bool Player::getIsMatt() const
//{
//	return m_isMatt;
//}
//
//void Player::printListPiece() const
//{
//	//Có lẽ trong Piece sẽ có 1 friend operator << overloading để in ra màn hình qua ostream cout
//
//	cout << endl;
//}
//void Player::printCapturedPiece() const
//{
//	//Cái này cũng tương tự cái trên
//	cout << endl;
//}

#include "Player.h"

Player::Player(Board* b, std::vector<Move*>& leMo, std::vector<Move*>& opponentMoves) {
	this->board = b;

	this->kingOfThis = kingEstablish();

	this->legalMoves = leMo;

	//this->legalMoves.addRange(calcKingCastles(leMo, opponentMoves));

	//this->inCheck = Player::calcAttackedMoves(this->kingOfThis->getPiecePos(), opponentMoves.any());
}

//std::vector<Move*> Player::calcAttackedMoves(int pos, std::vector<Move*>& opponentMoves) {
//	std::vector<Move*> attackMoves;
//
//	for (auto move : opponentMoves) {
//		if (pos == move->getDesCoordinate()) {
//			attackMoves.push_back(move);
//		}
//	}
//
//	return attackMoves;
//}

//King* Player::kingEstablish() {
//	for (auto piece : this->getActivePieces()) {
//		if (piece->isKing()) {
//			return static_cast<King*>(piece);
//		}
//	}
//
//	return nullptr;
//}