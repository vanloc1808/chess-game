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
    namespace assisstants {
        string getPieceLocation(PieceColor color, PieceType type); 

        string getSoundLocation(GameSound soundType);

        bool isOnBoardPosition(int x, int y);

        bool isOnBoardPosition(const Vector2i& pos);

        bool isOnBoardPosition(const ChessMove& move);

        bool isOnWindowPosition(const Vector2i& pos);

        Vector2f convertToDrawablePosition(int x, int y);

        Vector2f convertToDrawablePosition(const Vector2i& pos);

        Vector2i convertToBoardIndex(float x, float y);

        Vector2i convertToBoardIndex(const Vector2f& pos);     
    }
}

#endif //_ULTILITY_H_