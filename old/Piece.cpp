#include <iostream>
#include "Piece.h"

//Values of pieces from this link:
//https://www.masterclass.com/articles/chess-piece-guide
PieceType* PieceType::PAWN = new PieceType("Pawn", 1);
PieceType* PieceType::ROOK = new PieceType("Rook", 5);
PieceType* PieceType::KNIGHT = new PieceType("Knight", 3);
PieceType* PieceType::BISHOP= new PieceType("Bishop", 3);
PieceType* PieceType::QUEEN = new PieceType("Queen", 9);
//the link above does not contain the value of King, so I set it to 10,
//because it is the most important one in the board.
PieceType* PieceType::KING = new PieceType("King", 10);
