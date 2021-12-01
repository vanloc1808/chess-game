#ifndef  _KING_H_
#define	_KING_H_

#include "Piece.h"

class King : public Piece {
public:
	King(int c, int r, GameColor color);

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

#endif // ! _KING_H_
