#pragma once
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QTime>



#include "Service.h"

#include <qpoint.h>
#include <qcursor.h>

/*
Controlls the whole game (start/end/signals for events)
*/
class GameEngine : public QObject {
	Q_OBJECT;

	Service& ctrl;
	//int score;

	bool reached_objective, wall_hit;
	
	QTimer timer;
	QTimer getReady;
	QTime getReadyElapsed;

	int time_left;// (1 unit = 1 milisecond)

signals:

	//signal for start_game when mouse is over the rectangle
	void isReady();
	//this signal is responsible with the correct start of the game (when mouse is trackable)
	void notReady();
	//this signal is declared to deal with the player moving through the board, so that we can detect colisions
	void advanceBoard();
	//this signal is declared so that walls are created when needed
	void wallCreated(int x, int y, int wallW, int wallH);
	//this signal is created to notify any changings that occur during the game
	void gameFinished(bool win);

public:
	GameEngine(Service& ctrl, int timer_miliseconds) : ctrl{ ctrl }, time_left { timer_miliseconds } {
		reached_objective = false;
		wall_hit = false;
		QCursor::setPos(600, 800);//unfortunatelly, this is ABSOLUTE SCREEN (laptop/pc/whatever) COORDINATES
		//QCursor::setPos();
		//cursor->setPos(0, 0);
	}

	int getNumberOfHighScores() const {
		auto all = this->ctrl.getHighscores();
		return all.size();
	}

	int getLowestHighscore() const {
		auto all = this->ctrl.getHighscores();
		if (all.size() == 0)
			return -1;
		else
			return all.at(all.size() - 1).getScore();
	}

	Service& getCtrl() {
		return this->ctrl;
	}

	string getName() const {
		return this->ctrl.getName();
	}

	int getTimeLeft() const {
		return this->time_left;
	}

	int getDifficulty() const {
		return this->ctrl.getDifficulty();
	}

	vector<Highscore>& getHighscores() {
		ctrl.getHighscores();
	}

	void addHighScore(Highscore h) {
		ctrl.addHighscore(h);
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


		//it makes no sense to create an additional wall with an additional path if not used
		if (800 / 115 % 2 == 0) {
			//do not create the last wall / move the win objective up (hobj = h-hobj)
		}
		else {
			//create the last wall / do not move the win objective
		}

		for (int x = 0; x <= 800 / 115; x++) {
			if (x == 0) continue;
			if (x % 2 == 0) {
				y = 0;
				emit wallCreated(115 * x, y, wallW, wallH);
			}
			else {
				y = 115;
				emit wallCreated(115 * x, y, wallW, wallH);
			}
			
		}//THESE VALUES MUST BE PARAMETERS, NOT CONSTANT VALUES


	}																		//TODO messy job with mouse over and/or pre start timer...

	bool mouseOnPlayer() {
		
//		setMouseTracking(true); // E.g. set in your constructor of your widget.
//
//// Implement in your widget
//		void MainWindow::mouseMoveEvent(QMouseEvent *event) {
//			qDebug() << event->pos();
//		}

		//QPoint globalCursorPos = QCursor::pos();
		//int x = globalCursorPos.x;
		//int y = globalCursorPos.y;
		//qDebug << x<< " AND " << y;
		//int mouseScreen = qApp->desktop()->screenNumber(globalCursorPos);;

		//QPoint pos = cursorPosToNative(QCursor::pos());
		if (this->getReadyElapsed.elapsed() == 5000)//sadly...
			return true;
		return false;
	}

	bool isGameFinished() {
		return time_left == 0 || reached_objective || wall_hit;
	}

	void prepareStart() {
		getReadyElapsed.start();
		
		QObject::connect(&getReady, &QTimer::timeout, [&]() {
			emit notReady();
		});
		if (!mouseOnPlayer()) {
			getReady.stop();
			
			//emit isReady();
		}
		else {
			startGame();
		}
		getReady.start(1000);
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
