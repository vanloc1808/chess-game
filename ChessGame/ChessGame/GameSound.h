#ifndef _GAMESOUND_H_
#define _GAMESOUND_H_

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

class GameSound {
private:
	SoundBuffer _buffer;

	Sound _gameSound;

	string _soundLocation;

	bool _isRepeated;

	int _soundVolume;

public:
	GameSound(); //constructor

	~GameSound(); //destructor

	void setSoundBuffer(string location);

	void setRepeatedSound();

	void playSound();

	void pauseSound();

	void stopSound();

	void changeSoundVolume(int volume); 
};


#endif // !_GAMESOUND_H_

