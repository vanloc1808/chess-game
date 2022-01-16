#ifndef _GAMESOUND_H_
#define _GAMESOUND_H_

//enum class to define the sound effects for actions in game
enum class GameSound {
    MOVE, //sound effect for moving a piece
    CAPTURE, //sound effect for capturing a piece
    CHECK, //sound effect for checking
    CHECKMATE, //sound effect for checkmate
    STALEMATE, //sound effect for stalemate,
    //stalemate is the game status that there is NO possible moves for both side, therefore they will draw the game.
};

#endif //_GAMESOUND_H_