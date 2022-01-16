#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "Settings.h" //header from SFML or contains headers from SFML must be on the first of #include list
#include "ChessMove.h"
#include "GameSound.h"
#include "PieceData.h"
#include <string>

using namespace std;
using namespace sf;


namespace utilities {
    //define a sub-namespace in the namespace of utilities
    namespace assisstants {
        string getPieceLocation(PieceColor color, PieceType type); //get the location of the images of pieces

        string getSoundLocation(GameSound soundType); //get the location of sound effects

        //the following three functions are used to determine 
        //if a position is on board
        bool isOnBoardPosition(int x, int y);

        bool isOnBoardPosition(const Vector2i& pos);

        bool isOnBoardPosition(const ChessMove& move);

        bool isOnWindowPosition(const Vector2i& pos); //determine if a position is on window
        
        //the following two functions are used to convert a vector (x, y)
        //to a drawable position on board
        Vector2f convertToDrawablePosition(int x, int y);

        Vector2f convertToDrawablePosition(const Vector2i& pos);

        //the following two functions are used to convert a vector(x, y)
        //to index on chess board
        Vector2i convertToBoardIndex(float x, float y);

        Vector2i convertToBoardIndex(const Vector2f& pos);     
    }
}

#endif //_ULTILITY_H_