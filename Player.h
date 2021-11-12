//#pragma once
////Include mấy file của các quân cờ
///*
//#include "Pawn.h"
//#include "Rook.h"
//#include "Player.h"
//#include "Bishop.h"
//#include "Knight.h"
//#include "Rook.h"
//#include "King.h"
//#include "Queen.h"
//*/
//#include "Piece.h"
//
//#include <string>
//#include <vector>
//class Player
//{
//private:
//	//Name là tên người chơi
//	string m_name;
//	//Cái này chỉ lưu là 0: đen 1: trăng
//	bool m_color;
//	//Kiểm tra bị chiếu --- cũng không biết để làm gì nhưng coppy ngta có cái thuộc tính này
//	bool m_isChess;
//	//Kiểm tra hoà cờ  --- Cái này cũng giống cái isChess
//	bool m_isMatt; 
//	//Vecor chứa các quân cờ đang có
//	vector <Piece> m_listPieces;	
//	//Vecor chứa các quân cờ đã bị ăn 
//	vector <Piece> m_capturedPieces;
//
//public:
//
//	Player(string name, bool color);
//	~Player();
//	//Hàm liên quan đến tên người chơi
//	std::string getName() const;
//	//Hàm liên quan đến màu cờ đang chơi
//	bool getColor() const;
//	void setColor(bool color);
//
//	//Hàm lấy các quân cờ đang có trên bàn hoặc ăn được
//	vector <Piece>& getListPieces();
//	vector <Piece>& getCapturedPieces();
//	
//	/*Tóm tắt:
//	* Đây là hàm khởi tạo các quân cờ có trong bàn khi bắt đầu tức 16 quân các loại
//	* Tuỳ thuộc vào quân cờ có các thuộc tính gì mà khi khởi tạo theo như vậy:
//	* ở đây mô tả Piece có các thuộc tính như sau
//	* Piece(bool color = 1, string name = "", int row = 0, int column = 0);
//	*/
//	void initPieceList();
//
//	/*Tóm tắt:
//	* Sau nước đi của đối thủ nếu là nước ăn quân cờ thì thêm quân cờ đó vào list đã bị ăn
//	*/
//	void addToCapturedList(Piece* p);
//
//	/*Tóm tắt:
//	* Hàm lấy ra khỏi list cờ đã bị ăn nhằm hỗ trợ việc xây dựng phím tắt đi lại
//	* hàm này dùng kết hợp với hàm addToListPiece
//	*/
//	void removeToCapturedList(string name);
//	
//	/*Tóm tắt:
//	* Hàm thêm vào list quân cờ đang có
//	* Hàm hỗ trợ cho việc phong Hậu cho quân Tốt (việc này kết hợp với hàm removeToListPiece 1 quân tốt)
//	*/
//	void addToListPiece(Piece* p);
//	
//	/*Tóm tắt:
//	* Hàm loại bỏ một quân cờ ra khỏi list cờ đang có bằng tên của quân cờ
//	*/
//	void removeToListPiece(string name);
//
//	/*Tóm tắt:
//	* Hàm trả về xem có thể chọn quân cờ p không
//	* Cùng màu thì đi được  ---- Dùng kết hợp với hàm tìm các nước có thể đi của Piece
//	*/
//	bool canTake(Piece* p) const;
//
//	/*Tóm tắt:
//	* Hàm trả về xem có thể ăn quân cờ p không
//	* Khác màu thì ăn được
//	*/
//	bool canEat(Piece* p) const;
//
//	//Lấy giá trị dùng để kt bị chiếu 
//	bool getIsChess() const;
//	//Lấy giá trị xem có hoà không
//	bool getIsMatt() const;
//	//In ra List cờ có ---  In ra kiểu gì k biết --- Bây giờ mặc định là in ra console bằng cout
//	void printListPiece() const;
//	//Tương tự
//	void printCapturedPiece() const;
//};


#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <algorithm>

#include "Piece.h"
#include "Board.h"
#include "King.h"
#include "Move.h"


enum class Sides {
	WHITE,
	BLACK
};

class Player {
protected:
	Board* board;

	King* kingOfThis; //king of this player

	std::vector<Move*> legalMoves; //consist of legal moves of this player

private:
	bool inCheck = false;

public:
	virtual ~Player() {
		if (this->board) {
			delete[] this->board;
		}

		if (this->kingOfThis) {
			delete[] this->kingOfThis;
		}
	}

	Player(Board* b, std::vector<Move*>& m, std::vector<Move*> &opponentMoves);

protected:
	//calculate how many attacking moves of enemey on this cell
	static std::vector<Move*> calcAttackedMoves(int pos, std::vector<Move*>& opponentMoves);

private:
	
	King* kingEstablish();

public:
	//determine King of this player on the board
	King* getPlayerKing();

	std::vector<Move*> getLegalMoves();

	virtual std::vector<Piece*> getActivePieces() = 0;

	//determine if OPPONENT of this player is black or white
	virtual Sides getAlliance() = 0;

	virtual Player* getOpponent() = 0;

	bool isLegalMove(Move* move);

	//if this player is in check
	bool isInCheck();

	//if this player is in checkmate (aka end game)
	bool isInCheckmate();

private:
	//determine when the king can escape from being checked or not
	bool canEspace();

public:
	bool isStalemate();

	//in Vietnamese, we call "castling" "nhập thành"
	bool isCastling();

	//MoveTransition* makeMove(Move* move);

	//determine if the king is able to castle
	virtual std::vector<Move*> calcKingCastlings(std::vector<Move*>& playerLegalMoves, std::vector<Move*> opponentLegalMoves) = 0;
};


class WhitePlayer : public Player {
public:
	WhitePlayer(Board* b, std::vector<Move*>& whiteStandardLegalMoves, std::vector<Move*>& blacktandardLegalMoves);

	std::vector<Piece*> getActivePieces();

	Sides getAlliance();

	Player* getOpponent();

	std::vector<Move*> calcKingCastlings(std::vector<Move*>& playerLegalMoves, std::vector<Move*> opponentLegalMoves);
};

class BlackPlayer : public Player {
	BlackPlayer(Board* b, std::vector<Move*>& whiteStandardLegalMoves, std::vector<Move*>& blacktandardLegalMoves);

	std::vector<Piece*> getActivePieces();

	Sides getAlliance();

	Player* getOpponent();

	std::vector<Move*> calcKingCastlings(std::vector<Move*>& playerLegalMoves, std::vector<Move*> opponentLegalMoves);
};

#endif