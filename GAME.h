/*
int wallTickness = 5;
		auto br = QBrush(Qt::gray);

		leftWall = new Wall(0, 0, wallTickness, 800);

		rightWall = new Wall(600 - wallTickness - 1, 0, wallTickness, 800);

		topWall = new Wall(0, 0, 600, wallTickness);

		bottomWall = new Wall(0, 800 - wallTickness - 1, width(), wallTickness);

		scene->addItem(leftWall);
		scene->addItem(rightWall);
		scene->addItem(topWall);
		scene->addItem(bottomWall);
*/

#pragma once
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMessageBox>
#include "Player.h"
#include "Wall.h"
//#include "padle.h"
//#include "brick.h"
//#include "ball.h"
//#include "MyText.h"
#include <vector>
#include "GameEngine.h"
class GAME : public QGraphicsView {
private:
	GameEngine& engine;
	QGraphicsScene* scene;
	Player* player;
	Wall* winObjective;


	std::vector<Player*> playerSnaps;


	QGraphicsRectItem* leftWall;
	QGraphicsRectItem* rightWall;
	QGraphicsRectItem* topWall;
	QGraphicsRectItem* bottomWall;

	/*
	Define the scene borders
	*/
	void initEnclosingWals() {
		int wallTickness = 5;
		auto br = QBrush(Qt::gray);

		leftWall = new QGraphicsRectItem(0, 0, wallTickness, height()-50);
		leftWall->setBrush(br);

		rightWall = new QGraphicsRectItem(width() - wallTickness - 1, 0, wallTickness, height());
		rightWall->setBrush(br);

		topWall = new QGraphicsRectItem(0, 0, width(), wallTickness);
		topWall->setBrush(br);

		bottomWall = new QGraphicsRectItem(100, height() - wallTickness - 1, width(), wallTickness);
		bottomWall->setBrush(br);

		scene->addItem(leftWall);
		scene->addItem(rightWall);
		scene->addItem(topWall);
		scene->addItem(bottomWall);

	}

	/*
	Create the player model at starting point

					(TODO ALLOW CHANGEABLE COORDINATES FOR START)

	*/
	void createPlayer() {
		player = new Player;
		player->setRect(0, 0, 30, 30);
		player->setPos(50, height() - 50);
		scene->addItem(player);
		playerSnaps.push_back(player);
	}

	
	void createWinObjective() {
		winObjective = new Wall{ 50, 50 , Qt::green};
		winObjective->setPos(width()-65,height()-70);
		scene->addItem(winObjective);
	}


	/*
	Create the collidable objects that would eventually end the game
	*/
	void addWall(int x, int y, int wallW, int wallH) {
		Wall* wall = new Wall{ wallW, wallH, Qt::gray };
		wall->setPos(x, y);
		scene->addItem(wall);
	}

	/*
	Connect signals and slots (Qt responsible)
	*/
	void initSignalSlots() {

		QObject::connect(&engine, &GameEngine::wallCreated, [&](int x, int y, int wallW, int wallH) {
			addWall(x, y, wallW, wallH);
		});

		//advanceGame invoked every time  
		QObject::connect(&engine, &GameEngine::advanceBoard, this, &GAME::advanceGame);

		QObject::connect(&engine, &GameEngine::gameFinished, [&](bool win) {
			if (win) {
				QMessageBox::information(this, "Info", "You win!!!");
			}
			else {
				QMessageBox::information(this, "Info", "You lose!!!");
			}
		});
	}


	/*
	Mouse-controlled player is allowed
	*/
	void mouseMoveEvent(QMouseEvent* ev) override {
		//works only if setMouseTracking(true);
		auto x = ev->pos().x();
		auto y = ev->pos().y();
		player->setPos(x - 15, y - 15);
	}


	/*
	Keboard-controlled player is allowed
	*/
	void keyPressEvent(QKeyEvent* ev) override {
		if (ev->key() == Qt::Key_Left) {
			player->moveX(-30);
		}
		else if (ev->key() == Qt::Key_Right) {
			player->moveX(30);
		}
		else if (ev->key() == Qt::Key_Up) {
			player->moveY(-30);
		}
		else if (ev->key() == Qt::Key_Down) {
			player->moveY(30);
		}
	}


	/*
	Defines the gameplay itself - the collisions, the win objective...
	*/
	void advanceGame() {
		//for (auto pl : playerSnaps) {
		//	auto collides = pl->collidingItems();

			//pl->hit();
			//player->hit();
		auto collides = player->collidingItems();

		/*if (player->collidesWithItem(leftWall) ||
			player->collidesWithItem(rightWall) ||
			player->collidesWithItem(bottomWall) ||
			player->collidesWithItem(topWall)) {
			engine.wallHit();
			//etc...
		}*/

		for(auto el : collides){
			if (el == winObjective) {
				engine.gameFinished(true);
			}
			else {
				engine.gameFinished(false);
			}
		}
	}




	/*
	Create the scene
	*/
	void initScene() {
		scene = new QGraphicsScene;
		setScene(scene);

		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setFixedSize(800, 600);
		scene->setSceneRect(0, 0, 800, 600);
		setBackgroundBrush(QBrush(QColor(170,230,255,127)));

	}

public:
	GAME(GameEngine& engine) :engine{ engine } {
			setMouseTracking(true);
			initScene();
			initEnclosingWals();
			createPlayer();
			createWinObjective();
			initSignalSlots();
		}
};

