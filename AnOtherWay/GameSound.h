#ifndef _GAMESOUND_H_
#define _GAMESOUND_H_

enum class GameSound {
    MOVE,
    CAPTURE,
    CHECK,
    CHECKMATE,
    STALEMATE, //stalemate is the game status that there is NO possible moves for both side, therefore they will draw the game.
};

#endif //_GAMESOUND_H_