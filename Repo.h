#pragma once

#include <fstream>
#include <vector>
#include <algorithm>
#include "Highscore.h"
using std::vector;
using std::ifstream;
using std::ofstream;

/*
Repo is a class consisting of a vector of Highscores and a file name(basically a database of scores read from a text file).

The vector is sorted descendingly and has at most 10 values, so that the lowest value stays on the last position.
When a value is added, if there are less than 10 values, the score is added. If the dimension is maximum, the least high
score will be deleted and the new one will be inserted in the vector which (the vector) will be sorted immediatelly.

PRECONDITIONS: the score inserted must be greater than the lowest one.

*/
class Repo {
private:
	string fileName;
	vector<Highscore> highscores;

	void loadFromFile(string fName);
	void writeToFile(string fName);
public:
	Repo(string fileName) : fileName{ fileName } { loadFromFile(fileName); }
	
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
			this->highscores.push_back(highscore);
		}
		sort(highscores.begin(), highscores.end(), [&](Highscore& h1, Highscore& h2) {return h1.getScore() > h2.getScore(); });
		writeToFile(fileName);
	}
};
