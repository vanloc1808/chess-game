#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <iostream>
#include <string>

using namespace std;

//square on the board
class Square {
private:
	int _row;

	int _column;

public:
	Square(); //default constructor

	Square(int c, int r); //fully-parameterized constructor

	~Square();

	void change(int c, int r); //change to square on row r and column c

	//getters
	int getRow();

	int getColumn();
};

#endif // !_SQUARE_H_

