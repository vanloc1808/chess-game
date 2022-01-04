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
        //documents of class Sound and SoundBuffer of SFML here:
        //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Sound.php
        //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1SoundBuffer.php
        static Sound _sound; //sound object

        static map<GameSound, SoundBuffer> _bufferMap; //sound buffer map
    protected:

    public:
        AudioPlayer(); //default constructor

        ~AudioPlayer(); //destructor

        static void loadSound(); //load different sound buffers

        static void playSound(); //resume playing this sound

        static void playSound(GameSound soundType); //play a new type of sound

        static void pauseSound(); //pause the sound

        static void stopSound(); //stop the sound
    };
}

#endif // _GAMEAUDIOPLAYER_H_