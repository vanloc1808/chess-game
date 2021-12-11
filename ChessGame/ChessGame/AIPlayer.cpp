#define _CRT_SECURE_NO_WARNINGS

#include "AIPlayer.h"

AIPlayer::AIPlayer() {
	this->connectToEngine();
}

AIPlayer::~AIPlayer() {
	this->closeConnection();
}

void AIPlayer::connectToEngine() {
	STARTUPINFO tempStif = { 0 };
	SECURITY_ATTRIBUTES tempScat = { 0 };
	PROCESS_INFORMATION tempPcif = { 0 };

	this->_stif = tempStif;
	this->_scat = tempScat;
	this->_pcif = tempPcif;

	char txt[] = "stockfish.exe";

	wchar_t wtxt[20];

	mbstowcs(wtxt, txt, strlen(txt) + 1); //place for end file character '\0'

	LPWSTR lstr = wtxt;

	this->_wPipIn = NULL;
	this->_wPipOut = NULL;
	this->_rPipIn = NULL;
	this->_rPipOut = NULL;

	this->_scat.nLength = sizeof(this->_scat);
	this->_scat.bInheritHandle = TRUE;
	this->_scat.lpSecurityDescriptor = NULL;
	
	CreatePipe(&this->_rPipOut, &this->_wPipOut, &this->_scat, 0);
	CreatePipe(&this->_rPipIn, &this->_wPipIn, &this->_scat, 0);

	this->_stif.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	this->_stif.wShowWindow = SW_HIDE;
	this->_stif.hStdInput = this->_rPipIn;
	this->_stif.hStdOutput = this->_wPipOut;
	this->_stif.hStdError = this->_wPipOut;
	
	CreateProcess(NULL, lstr, NULL, NULL, TRUE, 0, NULL, NULL, &this->_stif, &this->_pcif);
}

string AIPlayer::getNextMove(string pos) {
	string str;

	pos = "position startpos moves " + pos + "\ngo\n";

	WriteFile(this->_wPipIn, pos.c_str(), pos.length(), &this->_writ, NULL);

	Sleep(75);

	PeekNamedPipe(this->_rPipOut, this->_buffer, sizeof(this->_buffer), &this->_decode, &this->_available, NULL);

	do {
		ZeroMemory(this->_buffer, sizeof(this->_buffer));

		if (!ReadFile(this->_rPipOut, this->_buffer, sizeof(this->_buffer), &this->_decode, NULL) || !(this->_decode)) {
			break;
		}

		this->_buffer[this->_decode] = 0;

		str += (char*)this->_buffer;

	} while (this->_decode >= sizeof(this->_buffer));

	int n = str.find("bestmove");

	if (n != -1) {
		return str.substr(n + 9, 4);
	}

	return "error";
}

void AIPlayer::closeConnection() {
	WriteFile(this->_wPipIn, "quit\n", 5, &this->_writ, NULL);

	if (this->_wPipIn != NULL) {
		CloseHandle(this->_wPipIn);
	}

	if (this->_rPipIn != NULL) {
		CloseHandle(this->_rPipIn);
	}

	if (this->_wPipOut != NULL) {
		CloseHandle(this->_wPipOut);
	}

	if (this->_rPipOut != NULL) {
		CloseHandle(this->_rPipOut);
	}

	if (this->_pcif.hProcess != NULL) {
		CloseHandle(this->_pcif.hProcess);
	}

	if (this->_pcif.hThread != NULL) {
		CloseHandle(this->_pcif.hThread);
	}
}