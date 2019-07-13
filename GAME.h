#pragma once
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMessageBox>
#include "Player.h"
#include "Wall.h"
#include <vector>
#include "GameEngine.h"
/*
we choose that the level *ALWAYS* starts in the bottom left and ends in bottom right
consequently, we made the coordinates easier to write for each situation
*/
class GAME : public QGraphicsView {
private:
	GameEngine& engine;
	
	QGraphicsScene* scene;
	int sceneWidth, sceneHeight;

	Player* player;
	int playerWidth, playerHeight;

	Wall* winObjective;
	int winObjectiveWidth, winObjectiveHeight;

	int move_distance_on_grid;


	std::vector<Player*> playerSnaps;


	QGraphicsRectItem* leftWall;
	QGraphicsRectItem* rightWall;
	QGraphicsRectItem* topWall;
	QGraphicsRectItem* bottomWall;

	/*
	Define the scene borders
	relative definition according to the size of the window
	*/
	void initEnclosingWals() {
		int wallTickness = 5;
		auto br = QBrush(Qt::gray);

		leftWall = new QGraphicsRectItem(0, 0, wallTickness, height());
		leftWall->setBrush(br);

		rightWall = new QGraphicsRectItem(width() - wallTickness - 1, 0, wallTickness, height());
		rightWall->setBrush(br);

		topWall = new QGraphicsRectItem(0, 0, width(), wallTickness);
		topWall->setBrush(br);

		bottomWall = new QGraphicsRectItem(0, height() - wallTickness - 1, width(), wallTickness);
		bottomWall->setBrush(br);

		scene->addItem(leftWall);
		scene->addItem(rightWall);
		scene->addItem(topWall);
		scene->addItem(bottomWall);

	}

	/*
	Create the player model at starting point

					(TODO ALLOW CHANGEABLE COORDINATES FOR START)

					(TODO - on function call, the dimensions of the PLAYER object should be PROPORTIONAL to the dimensions of the PATH to the objective)

		//function call: 30 30 50 50
		// 50 50     30 30
		// x  h()-y  w  h
		it is calculated from the bottom left corner (x,y positive - mathematically)
	*/
	void createPlayer(int player_size_x, int player_size_y, int player_start_x, int player_start_y) {
		player = new Player;
		player->setRect(0, 0, player_size_x, player_size_y);//	W	H	Y		don't we just use the rectangle directly in the scene?
		player->setPos(player_start_x, height() - player_start_y);
		scene->addItem(player);
		playerSnaps.push_back(player);
	}

	/*
	Create the win objective model on the board
	
		//function call: 50 50 65 70
		// 65     70     50 50
		// w()-x  h()-y  w  h
		it is calculated from the bottom right corner (x negative, y positive - mathematically)
	*/
	void createWinObjective(int win_size_x, int win_size_y, int start_x, int start_y) {
		winObjective = new Wall{ win_size_x, win_size_y , Qt::green};
		winObjective->setPos(width() - start_x, height() - start_y);
		scene->addItem(winObjective);
	}


	/*
	Create the collidable objects that would eventually end the game when hit

	we consider the default coodrinate system when typing in values
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
		player->setPos(x - playerWidth / 2, y - playerHeight / 2);//CENTER THE PLAYER ICON RELATIVE TO THE ARROW ON SCREEN (also relative to the dimensions of the player)
	}


	/*
	Keboard-controlled player is allowed
	*/
	void keyPressEvent(QKeyEvent* ev) override {//KEY-BASED MOVEMENT DISTANCE SHOULD BE PROPORTIONAL TO THE DIMENSIONS OF THE WINDOW / PATH
		if (ev->key() == Qt::Key_Left) {
			player->moveX(-move_distance_on_grid);
		}
		else if (ev->key() == Qt::Key_Right) {
			player->moveX(move_distance_on_grid);
		}
		else if (ev->key() == Qt::Key_Up) {
			player->moveY(-move_distance_on_grid);
		}
		else if (ev->key() == Qt::Key_Down) {
			player->moveY(move_distance_on_grid);
		}
	}


	/*
	Defines the gameplay itself - the collisions, the win objective
	*/
	void advanceGame() {

		auto collides = player->collidingItems();

		for(auto el : collides){
			if (el == winObjective) {//reach the goal
				engine.goalHit();
			}
			else {//hit a wall
				engine.wallHit();
			}
		}
	}




	/*
	Create the scene
	*/
	void initScene(int size_x, int size_y) {
		scene = new QGraphicsScene;
		setScene(scene);

		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setFixedSize(size_x, size_y);
		scene->setSceneRect(0, 0, size_x, size_y);//define the scene as the whole window
		setBackgroundBrush(QBrush(QColor(170,230,255,127)));//lightblue

	}

public:
	GAME(GameEngine& engine, int sceneWidth, int sceneHeight, int playerWidth, int playerHeight, int winObjectiveWidth, int winObjectiveHeight, int move_distance_on_grid, bool mouse_tracking) :
		engine{ engine }, sceneWidth{ sceneWidth }, sceneHeight{ sceneHeight }, playerWidth{ playerWidth }, playerHeight{ playerHeight }, winObjectiveWidth{ winObjectiveWidth }, winObjectiveHeight{ winObjectiveHeight },
		move_distance_on_grid{ move_distance_on_grid } {
		//move distance on grid <- 30 (same value as the size of player)
			setMouseTracking(mouse_tracking);
			initScene(sceneWidth, sceneHeight);
			initEnclosingWals();
			createPlayer(playerWidth, playerHeight,50,50);//starting coordinates should be relative to the window size 
			createWinObjective(winObjectiveWidth, winObjectiveHeight,65,70);//finish coordinates should be relative to the window size 
			initSignalSlots();
		}
};

