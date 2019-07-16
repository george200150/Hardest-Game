#pragma once
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QTime>

#include "Service.h"

#include <qdebug.h>
//#include <qdesktopwidget.h>

#include "Commander.h"




/*
Controlls the whole game (start/end/signals for events)
*/
class GameEngine : public QObject {
	Q_OBJECT;

	Commander* comm;

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
	//this signal is created to transmit the time to the gui
	void tickTock(int time);
	//this signal is declared so that walls are created when needed
	void wallCreated(int x, int y, int wallW, int wallH);
	//this signal is created to notify any changings that occur during the game
	void gameFinished(bool win);

public:
	GameEngine(Commander* comm, int timer_miliseconds) : comm{ comm }, time_left { timer_miliseconds } {
		reached_objective = false;
		wall_hit = false;
		
		/*QDesktopWidget widget;
		int width = widget.screenGeometry().width();
		int height = widget.screenGeometry().height();
		qDebug() << width;
		qDebug() << height;*/

	}

	int getNumberOfHighScores() const {
		auto all = this->comm->getHighscores();
		return all.size();
	}

	int getLowestHighscore() const {
		auto all = this->comm->getHighscores();
		if (all.size() == 0)
			return -1;
		else
			return all.at(all.size() - 1).getScore();
	}


	string getName() const {
		return this->comm->getName();
	}

	int getTimeLeft() const {
		return this->time_left;
	}

	int getDifficulty() const {
		return this->comm->getDifficulty();
	}

	vector<Highscore>& getHighscores() {
		comm->getHighscores();
	}

	void addHighScore(Highscore h) {
		comm->addHighscore(h);
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

		int wallW = this->comm->getWallW(); 
		int wallH = this->comm->getWallH();
		
		int screenW = this->comm->getSceneW();
		int screenH = this->comm->getSceneH();


		int pathW = this->comm->getPlayerW() * 3 + this->comm->getWallW();
		int pathH = this->comm->getPlayerH() * 3 + this->comm->getWallW();


		int x = 0;
		int y = 0;


		//it makes no sense to create an additional wall with an additional path if not used
		if (screenW / 115 % 2 == 0) {
			//do not create the last wall / move the win objective up (hobj = h-hobj)
		}
		else {
			//create the last wall / do not move the win objective
		}

		for (int x = 1; x <= screenW / pathW; x++) {

			if (screenW / pathW % 2 == 1 && x == screenW / pathW)
				continue;

			if (x % 2 == 0) {
				y = 0;
				emit wallCreated(pathW * x, y, wallW, wallH);
			}
			else {
				y = pathH;
				emit wallCreated(pathW * x, y, wallW, wallH);
			}
			
		}


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
			emit tickTock(this->time_left);
			if (isGameFinished()) {
				timer.stop();
				emit gameFinished(time_left != 0 && !wall_hit);
			}
			if (this->comm->escWasPressed())
				timer.stop();
		});
		//generate timeout signal every 10 ms
		timer.start(10);
	}
};