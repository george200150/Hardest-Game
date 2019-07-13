#pragma once
#include <string>
using std::string;



class MyException {
private:
	string msg;
public:
	MyException(string msg) :msg{ msg } {}
	string print() const {
		return this->msg;
	}
};



class Highscore {
private:
	string name, score;

public:
	Highscore(string name, string score) : name{ name }, score{ score }{}

	string getName() const {
		return this->name;
	}

	string getScore() const {
		return this->score;
	}

	string toString() const {
		return this->name + " - " + this->score;
	}
};