#ifndef _AIPLAYER_H_
#define _AIPLAYER_H_

#include "GameWindow.h" //all the header of SFML must be the FIRST one, ABOVE ALL
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Mouse.h"

using namespace std;

class AIPlayer {
private:
	STARTUPINFO _stif;

	SECURITY_ATTRIBUTES _scat;

	PROCESS_INFORMATION _pcif;

	HANDLE _wPipIn, _rPipIn, _wPipOut, _rPipOut;

	BYTE _buffer[2048];

	DWORD _writ, _encode, _decode, _available;

	void connectToEngine();

	void closeConnection();

public:
	AIPlayer(); //constructor

	~AIPlayer(); //destructor

	string getNextMove(string pos);
};

#endif // !_AIPLAYER_H_

