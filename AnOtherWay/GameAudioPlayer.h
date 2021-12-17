#ifndef _GAMEAUDIOPLAYER_H_
#define _GAMEAUDIOPLAYER_H_

#include <SFML/Audio.hpp>
#include <vector>
#include <map>
#include "GameSound.h"
#include "Utility.h"

using namespace sf;
using namespace std;

namespace utilities {
    class AudioPlayer {
    private:
        static Sound _sound;

        static map<GameSound, SoundBuffer> _bufferMap;
    protected:

    public:
        AudioPlayer(); //constructor

        ~AudioPlayer();

        static void loadSound(); //load different sound buffers

        static void playSound(); //resume playing sound

        static void playSound(GameSound soundType); //play a new type of sound

        static void pauseSound(); //pause the sound

        static void stopSound(); //stop the sound
    };
}

#endif // _GAMEAUDIOPLAYER_H_