#pragma once

#include "Repo.h"

class Service {
private:
	Repo& repo;
	//1 is for keyboard
	//2 is for mouse
	int command_type;

	//1 is for easy;
	//2 is for normal;
	//3 is for hard;
	int difficulty;
public:

	Service(Repo& repo) : repo{ repo } { this->command_type = 1; this->difficulty = 2; }//USER SETTINGS CAN BE REMEMBERED IF THEY ARE LOADED FROM A FILE

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
