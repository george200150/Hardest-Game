#pragma once

#include <fstream>
#include <vector>
#include <algorithm>
#include "Highscore.h"
using std::vector;
using std::ifstream;
using std::ofstream;


class Repo {
private:
	string fileName;
	vector<Highscore> highscores;

	void loadFromFile(string fName);
	void writeToFile(string fName);
public:
	Repo(string fileName) : fileName{ fileName } { loadFromFile(fileName); }
	//the vector of highscores will always be sorted descendingly. no matter what.
	vector<Highscore>& getHighscores() {
		return this->highscores;
	}
	/*
	we have a chart of the 10 highest scores recorded.
	If the list is empty, we will fill it up till it reaches 10 scores.
	When a new score is added to the full list, the latter one will be deleted
	*/
	void addHighScore(Highscore highscore) {
		if (this->highscores.size() < 10) {
			this->highscores.push_back(highscore);
		}
		else {
			this->highscores.pop_back();//the lowest score is always in the back
		}
		sort(highscores.begin(), highscores.end(), [&](Highscore& h1, Highscore& h2) {return h1.getScore() < h2.getScore(); });
		writeToFile(fileName);
	}
};
