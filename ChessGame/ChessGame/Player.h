#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Player {
private:
	string _name;

	int _age;

	string _address;

	int _elo;

	string _gender;

	int _winNumber;

	int _loseNumber;

	string _movedPiece;

public:
	Player(); //constructor

	Player(string n, int a); //parameterized  constructor with name and age

	~Player(); //destructor

	string getName();

	int getElo();

	string getAddress();

	string getGender();

	void addMovedPiece(string p);

	void removeMovedPiece();
};

#endif // !_PLAYER_H
