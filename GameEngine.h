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

	
	QTimer timer;

	int time_left = 10000;//10 seconds (1 unit = 1 milisecond)

signals:

	void advanceBoard();
	void wallCreated(int x, int y, int wallW, int wallH);
	void gameFinished(bool win);

public:
	GameEngine() {}



	void wallHit() {
		emit gameFinished(false);
	}

	/*
	Create the level layout. (walls,paths...)
	*/
	void loadLevel() {


		int wallW = 25;
		int wallH = 600-60;
		int x = 0;
		int y = 0;

		// HERE, THERE SHOULD BE A SEGMENTATION OF THE LEVEL DEPENDING ON THE
		// WINDOW DIMENSION. THE COORDINATES *MUST NOT* BE ACTUAL NUMBERS!!!
		for (int x = 0; x < 800 / 25; x++) {
			if (x % 2 == 0) {
				y = 0;
				emit wallCreated(140 * x, y, wallW, wallH);
			}
			else {
				y = 60;
				emit wallCreated(140 * x, y, wallW, wallH);
			}
			
		}


	}

	bool isGameFinished() {
		return time_left == 0;
	}

	void startGame() {
		loadLevel();

		//TODO probabil ca voi avea de setat semnalele chestiilor care se misca pe ecran..

		QObject::connect(&timer, &QTimer::timeout, [&]() {
			this->time_left--;
			emit advanceBoard();
			if (isGameFinished()) {
				timer.stop();
				emit gameFinished(time_left != 0);
			}
		});
		//generate timeot signal every ms
		timer.start(1);
	}
};
