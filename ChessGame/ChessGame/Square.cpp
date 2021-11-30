#include "Square.h"

//default constructor
//with row = column = 0
Square::Square() {
	this->_row = 0;
	this->_column = 0;
}

Square::Square(int c, int r) {
	this->_row = r;
	this->_column = c;
}

//default destructor,
//do nothing
Square::~Square() {

}

void Square::change(int c, int r) {
	this->_row = r;
	this->_column = c;
}

int Square::getRow() {
	return this->_row;
}

int Square::getColumn() {
	return this->_column;
}