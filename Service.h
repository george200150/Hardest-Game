#pragma once

#include "Repo.h"

class Service {//service settings could be read from file.
private:
	Repo& repo;
	//1 is for keyboard
	//2 is for mouse
	int command_type;

	//1 is for easy;
	//2 is for normal;
	//3 is for hard;
	int difficulty;

	//name
	string you;


	/*
	string keyUP;
	string keyDOWN;
	string keyLEFT;
	string keyRIGHT;
	*/
	//vector<int> key_commands;

public:

	Service(Repo& repo) : repo{ repo } { this->command_type = 1; this->difficulty = 2; you = "YOU"; /*key_commands = { 16777235,16777237,16777234,16777236 };*/ }//USER SETTINGS CAN BE REMEMBERED IF THEY ARE LOADED FROM A FILE
	//those weird values are for the up,down,left,right keys in Qt convention

	/*vector<int>& getAssignedKeys() {
		return this->key_commands;
	}*/

	string getName() const {
		return this->you;
	}
	void setName(string newYou) {
		this->you = newYou;
	}

	int getDifficulty() const {
		return this->difficulty;
	}
	void setDifficulty(int newDifficulty) {
		this->difficulty = newDifficulty;
	}

	int getCommandType() const {
		return this->command_type;
	}
	void setCommandType(int newCommandType) {
		this->command_type = newCommandType;
	}
	void addHighscore(Highscore h) {
		this->repo.addHighScore(h);
	}
	vector<Highscore>& getHighscores() {
		return this->repo.getHighscores();
	}
};
