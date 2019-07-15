#include "Repo.h"


void Repo::loadFromFile(string fName) {
	ifstream in(fName);
	if (!in.is_open()) {
		throw MyException{ "CANNOT OPEN STREAM" };
	}

	while (!in.eof()) {

		string name;
		int score;


		in >> name;

		if (in.eof()) {
			break;
		}

		in >> score;

		Highscore h{ name, score };


		this->highscores.push_back(h);//we know that the file has at most 10 highscores
	}
	in.close();
}


void Repo::writeToFile(string fName) {
	ofstream out(fName);
	if (!out.is_open()) {
		throw MyException{ "CANNOT OPEN STREAM" };
	}

	for (const auto& h : highscores) {
		out << h.getName();
		out << '\n';
		out << h.getScore();
		out << '\n';
	}
	out.close();
}