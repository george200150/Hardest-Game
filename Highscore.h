#pragma once
#include <string>
using std::string;


/*
Custom Exception that receives through constructor a string

has a message that will be returned when print() is called
*/
class MyException {
private:
	string msg;
public:
	MyException(string msg) :msg{ msg } {}
	string print() const {
		return this->msg;
	}
};



/*
Highscore is a class consisting of two fields, name and score.

A highscore is assigned to a player and has a positive value.
*/
class Highscore {
private:
	string name;
	int score;

public:
	Highscore(string name, int score) : name{ name }, score{ score }{}

	string getName() const {
		return this->name;
	}

	int getScore() const {
		return this->score;
	}

	string toString() const {
		return this->name + " - " + std::to_string(this->score);
	}
};