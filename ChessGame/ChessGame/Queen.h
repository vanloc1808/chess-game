#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "Piece.h"

class Queen : public Piece {
public:
	Queen(int c, int r, GameColor color);

	void setImage(); //setup image

	void setPosition(); //setup image position

	Square getCurrentPlace(); //get the current place of this piece

	GameColor getPieceColor(); //get the color of this piece

	void setSelected(); //setup the selected piece

	void unsetSelected(); //un-setup the selected piece

	//PML = Possible Move Location

	void getPML(PieceBoard pb[][8]); //set up the location that this piece can move to

	void moveToNewPlace(int c, int r); //move the piece to a new position
};

#endif // !_QUEEN_H_
