#pragma once
class ScoreSystem{
private:
	int difficulty;
	int time;
	int score;
	void compute_score() {

		if (difficulty == 1)
			score = time;
		else if (difficulty == 2)
			score = time * 100;
		else if (difficulty == 3)//score system could get better
			score = time * 10000;
	}
public:
	ScoreSystem(int difficulty) : difficulty{ difficulty }, time{ 0 }, score{ 0 } {}
	ScoreSystem(int difficulty, int time) : difficulty{ difficulty }, time{ time }, score{ 0 }{ compute_score(); }

	void setTime(int newTime) {
		this->time = newTime;
	}

	int getScore() const {
		return this->score;
	}
};

