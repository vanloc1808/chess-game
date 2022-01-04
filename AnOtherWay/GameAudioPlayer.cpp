#include "GameAudioPlayer.h"

namespace utilities {
    Sound AudioPlayer::_sound;

    map<GameSound, SoundBuffer> AudioPlayer::_bufferMap;

    //default constructor, no need to do anything
    AudioPlayer::AudioPlayer() {

    }

    //destructor, no need to do anything
    AudioPlayer::~AudioPlayer() {

    }

    void AudioPlayer::loadSound() {
        vector<GameSound> soundTypes = {GameSound::MOVE, GameSound::CAPTURE, GameSound::CHECK, 
        GameSound::CHECKMATE, GameSound::STALEMATE};

        for (int i = 0; i < soundTypes.size(); i++) {
            if (AudioPlayer::_bufferMap.find(soundTypes[i]) == AudioPlayer::_bufferMap.end()) {
                SoundBuffer buffer;

                if (buffer.loadFromFile(assisstants::getSoundLocation(soundTypes[i])) == false) {
                    throw std::runtime_error("Could not load sound");
                }

                AudioPlayer::_bufferMap[soundTypes[i]] = buffer;
            }
        }
    }

    void AudioPlayer::playSound() {
        AudioPlayer::_sound.play();
    }

    void AudioPlayer::playSound(GameSound soundType) {
        //if already sound play, stop it
        if (AudioPlayer::_sound.getStatus() != Sound::Status::Stopped) {
            AudioPlayer::_sound.stop();
        }

        AudioPlayer::_sound.setBuffer(AudioPlayer::_bufferMap[soundType]);
        AudioPlayer::_sound.play();
    }

    void AudioPlayer::pauseSound() {
        AudioPlayer::_sound.pause();
    }

    void AudioPlayer::stopSound() {
        AudioPlayer::_sound.stop();
    }
} 