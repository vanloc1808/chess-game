#ifndef _GAMEMUSIC_H_
#define _GAMEMUSIC_H_

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

enum class MusicStatus {
	PLAY,
	PAUSE,
	STOP,
};

class GameMusic {
private:
	Music _gameMusic;

	string _musicLocation;

	bool _isRepeated;

	int _musicVolume;

	MusicStatus _musicStatus;

public:
	GameMusic(); //constructor

	~GameMusic(); //destructor

	void setMusic(string location);

	void setRepeatedMusic();

	void playMusic();

	void pauseMusic();

	void stopMusic();

	void continueMusic(); //use when pause only

	void changeMusicVolume(int volume);

	MusicStatus getMusicStatus();
};

#endif // !_GAMEMUSIC_H_
