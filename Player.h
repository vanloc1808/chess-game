#pragma once
//Include mấy file của các quân cờ
/*
#include "Pawn.h"
#include "Rook.h"
#include "Player.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
*/
#include "Piece.h"

#include <string>
#include <vector>
class Player
{
private:
	//Name là tên người chơi
	string m_name;
	//Cái này chỉ lưu là 0: đen 1: trăng
	bool m_color;
	//Kiểm tra bị chiếu --- cũng không biết để làm gì nhưng coppy ngta có cái thuộc tính này
	bool m_isChess;
	//Kiểm tra hoà cờ  --- Cái này cũng giống cái isChess
	bool m_isMatt; 
	//Vecor chứa các quân cờ đang có
	vector <Piece> m_listPieces;	
	//Vecor chứa các quân cờ đã bị ăn 
	vector <Piece> m_capturedPieces;

public:

	Player(string name, bool color);
	~Player();
	//Hàm liên quan đến tên người chơi
	std::string getName() const;
	//Hàm liên quan đến màu cờ đang chơi
	bool getColor() const;
	void setColor(bool color);

	//Hàm lấy các quân cờ đang có trên bàn hoặc ăn được
	vector <Piece>& getListPieces();
	vector <Piece>& getCapturedPieces();
	
	/*Tóm tắt:
	* Đây là hàm khởi tạo các quân cờ có trong bàn khi bắt đầu tức 16 quân các loại
	* Tuỳ thuộc vào quân cờ có các thuộc tính gì mà khi khởi tạo theo như vậy:
	* ở đây mô tả Piece có các thuộc tính như sau
	* Piece(bool color = 1, string name = "", int row = 0, int column = 0);
	*/
	void initPieceList();

	/*Tóm tắt:
	* Sau nước đi của đối thủ nếu là nước ăn quân cờ thì thêm quân cờ đó vào list đã bị ăn
	*/
	void addToCapturedList(Piece* p);

	/*Tóm tắt:
	* Hàm lấy ra khỏi list cờ đã bị ăn nhằm hỗ trợ việc xây dựng phím tắt đi lại
	* hàm này dùng kết hợp với hàm addToListPiece
	*/
	void removeToCapturedList(string name);
	
	/*Tóm tắt:
	* Hàm thêm vào list quân cờ đang có
	* Hàm hỗ trợ cho việc phong Hậu cho quân Tốt (việc này kết hợp với hàm removeToListPiece 1 quân tốt)
	*/
	void addToListPiece(Piece* p);
	
	/*Tóm tắt:
	* Hàm loại bỏ một quân cờ ra khỏi list cờ đang có bằng tên của quân cờ
	*/
	void removeToListPiece(string name);

	/*Tóm tắt:
	* Hàm trả về xem có thể chọn quân cờ p không
	* Cùng màu thì đi được  ---- Dùng kết hợp với hàm tìm các nước có thể đi của Piece
	*/
	bool canTake(Piece* p) const;

	/*Tóm tắt:
	* Hàm trả về xem có thể ăn quân cờ p không
	* Khác màu thì ăn được
	*/
	bool canEat(Piece* p) const;

	//Lấy giá trị dùng để kt bị chiếu 
	bool getIsChess() const;
	//Lấy giá trị xem có hoà không
	bool getIsMatt() const;
	//In ra List cờ có ---  In ra kiểu gì k biết --- Bây giờ mặc định là in ra console bằng cout
	void printListPiece() const;
	//Tương tự
	void printCapturedPiece() const;
};
