#pragma once
#include <QObject>
#include <QDebug>
#include <QTimer>

/*
Controlls the whole game (start/end/signals for events)
*/
class GameEngine : public QObject {
	Q_OBJECT;
	int score;

	bool reached_objective, wall_hit;
	
	QTimer timer;

	int time_left;// (1 unit = 1 milisecond)

signals:

	//+signal for start_game when mouse is over the rectangle

	//

	//this signal is declared to deal with the player moving through the board, so that we can detect colisions
	void advanceBoard();
	//this signal is declared so that walls are created when needed
	void wallCreated(int x, int y, int wallW, int wallH);
	//this signal is created to notify any changings that occur during the game
	void gameFinished(bool win);

public:
	GameEngine(int timer_miliseconds) : time_left{ timer_miliseconds } {
		reached_objective = false;
		wall_hit = false;
	}


	/*
	define the collision event:
	if we hit any wall, the game ends.
	*/
	void wallHit() {
		wall_hit = true;
	}


	/*
	define the goal event:
	if we reach it, the game ends.
	*/
	void goalHit() {
		reached_objective = true;
	}


	/*
	Create the level layout. (walls,paths...)

		-TODO-
	make the window parameters changeable, and the distances must depend on those dimensions
	*/
	void loadLevel() {

		int wallW = 25;
		int wallH = 600-60;
		int x = 0;
		int y = 0;

		// HERE, THERE SHOULD BE A SEGMENTATION OF THE LEVEL DEPENDING ON THE
		// WINDOW DIMENSION. THE COORDINATES *MUST NOT* BE ACTUAL NUMBERS!!!
		for (int x = 0; x <= 800 / 115; x++) {
			if (x % 2 == 0) {
				y = 0;
				emit wallCreated(115 * x, y, wallW, wallH);
			}
			else {
				y = 115;
				emit wallCreated(115 * x, y, wallW, wallH);
			}
			
		}//THESE VALUES MUST BE PARAMETERS, NOT CONSTANT VALUES


	}

	bool isGameFinished() {
		return time_left == 0 || reached_objective || wall_hit;
	}

	void startGame() {
		loadLevel();

		//TODO probabil ca voi avea de setat semnalele chestiilor care se misca pe ecran..

		QObject::connect(&timer, &QTimer::timeout, [&]() {
			this->time_left--;
			emit advanceBoard();
			if (isGameFinished()) {
				timer.stop();
				emit gameFinished(time_left != 0 && !wall_hit);
			}
		});
		//generate timeout signal every ms
		timer.start(1);
	}
};
