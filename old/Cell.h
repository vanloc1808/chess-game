#ifndef _CELL_H_
#define _CELL_H_

#include <string>
#include <unordered_map>

#include "Piece.h"

class Cell {
protected:
	//we use the int type to store coordinates of cells
	//because we will define it as integer from 0 to 63
	int cellCoordinate;

private:
	//empty cells to be reused
	static std::unordered_map<int, EmptyCell*> cachedEmptyCells;

public:
	Cell(int coor);

	//create empty cells
	static std::unordered_map<int, EmptyCell*> createCachedEmptyCells();

	//create a cell, this cell can store a piece or not
	static Cell* createCell(int coor, Piece* piece);

	virtual bool isOccupied() = 0;

	virtual Piece* getPiece() = 0;

	int getCellCoordinate();
};

class EmptyCell : public Cell {
public:
	EmptyCell(int coor);

	bool isOccupied();

	Piece* getPiece();

	std::string toString();
};

class OccupiedCell : public Cell {
private:
	Piece* pieceOnCell;

public:
	~OccupiedCell() {
		if (pieceOnCell) {
			delete[] pieceOnCell;
		}
	}

	OccupiedCell(int coor, Piece* p);

	bool isOccupied();

	Piece* getPiece();

	std::string toString();
};

#endif // !_CELL_H_
