#pragma once
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMessageBox>
#include "Player.h"
#include "Wall.h"
#include <vector>
#include "GameEngine.h"
//#include <qdialogbuttonbox.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>


#include <qcursor.h>



#include "Commander.h"


/*
The Communicate class consists of a window through which the user submits his highscore.
It has a message for the user, a "Name:" label and a text field associated in which the
user should insert his name. When the button "SUBMIT" is pressed, the information (name+score)
will be sent to the commander/service which will process that information

The class receives as parameters through the constructor the Commander(Service) and the score.
*/
class Communicate : public QWidget {
private:
	int current_score;
	Commander* commander;
	QPushButton* btnSubmit = new QPushButton{ "SUBMIT HIGHSCORE" };
	QLabel* labName = new QLabel{ "Name:" };

	QLineEdit* txtName = new QLineEdit;

	void GUIsetup() {
		QFormLayout* linit = new QFormLayout;
		this->setLayout(linit);
		linit->addRow(new QLabel{ "YOUR GAME WAS GREAT! TELL US WHO YOU ARE!" });
		linit->addRow(labName, txtName);
		linit->addRow(btnSubmit);
	}

	void initSignalSlots() {

		QObject::connect(btnSubmit, &QPushButton::clicked, this, [&]() {
			string you = this->txtName->text().toStdString();
			
			if (you == "")//if user left the field empty, a token (*unknown*) is assigned to the name instead of being empty
				you = "*unknown*";

			Highscore h{ you,this->current_score };
			this->commander->addHighscore(h);
			this->close();
		});
	}

	void initialState() {}

public:
	Communicate(Commander* commander, int current_score) : commander{ commander }, current_score{ current_score } {
		GUIsetup();
		initSignalSlots();
		initialState();
	}
};



/*
we choose that the level *ALWAYS* starts in the bottom left and ends in bottom right
consequently, we made the coordinates easier to write for each situation
*/
class GAME : public QGraphicsView {
private:

	Commander* commander;

	GameEngine* engine;


	QGraphicsScene* scene;
	int sceneWidth, sceneHeight;

	Player* player;
	int playerWidth, playerHeight;

	Wall* winObjective;
	int winObjectiveWidth, winObjectiveHeight;

	int move_distance_on_grid;


	std::vector<Player*> playerSnaps;

	Communicate* comm;

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
	Create the player model at starting point (default: 30 30 50 50)
		
	it is calculated from the bottom left corner (x,y positive - mathematically)
	*/
	void createPlayer(int player_size_x, int player_size_y, int player_start_x, int player_start_y) {
		player = new Player;
		player->setRect(0, 0, player_size_x, player_size_y);
		player->setPos(player_start_x, height() - player_start_y);
		scene->addItem(player);
		playerSnaps.push_back(player);
	}

	/*
	Create the win objective model on the board (default: 50 50 65 70)

	it is calculated from the bottom right corner (x negative, y positive - mathematically)
	*/
	void createWinObjective(int win_size_x, int win_size_y, int start_x, int start_y) {
		winObjective = new Wall{ win_size_x, win_size_y , Qt::green };
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
	signal:	-wallCreated - adds a wall on the board @ (x,y);(x+wallW,y+WallH)
			-advanceBoard - treats all the collisions in real time
			-gameFinished - stops the game clock and shows message whether win, highscore, or lose
	*/
	void initSignalSlots() {

		QObject::connect(engine, &GameEngine::wallCreated, [&](int x, int y, int wallW, int wallH) {
			addWall(x, y, wallW, wallH);
		});

		//advanceGame invoked every time  
		QObject::connect(engine, &GameEngine::advanceBoard, this, &GAME::advanceGame);

		QObject::connect(engine, &GameEngine::gameFinished, [&](bool win) {
			
			this->releaseMouse();

			if (win) {
				QMessageBox::information(this, "Info", "You win!!!");

				try {

					int number_of_highscores = this->engine->getNumberOfHighScores();
					int low = this->engine->getLowestHighscore();//THIS IS THE LOWEST HIGHSCORE

					int time = this->engine->getTimeLeft();
					int difficulty = this->engine->getDifficulty();



					
					int score = 0;//WE CALCULATE THE SCORE OF THE CURRENT SESSION (using a score system which we may separately define later...)
					
					if (difficulty == 1)
						score = time;
					else if (difficulty == 2)
						score = time * 100;
					else if (difficulty == 3)//score system could get better
						score = time * 10000;


					
					
					if (number_of_highscores == 10 && score < low)//COMPARE SCORES TO CHECK IF WE REACHED THE TOP 10
						throw MyException("SCORE IS NOT HIGH ENOUGH!");


					QMessageBox::information(this, "Info", "You are in top 10!!!");//IF WE REACH THIS POINT, IT MEANS WE MADE IT IN TOP 10


					comm = new Communicate{ commander, score };//the communication window will submit the highscore
					comm->show();

				}
				catch (MyException&) {/*ignore*/};
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
		else if (ev->key() == Qt::Key_Right) {//THIS PART COULD BE PARAMETERISED AND THE KEYS COULD BE ASSIGNED IN THE SETTINGS
			player->moveX(move_distance_on_grid);
		}
		else if (ev->key() == Qt::Key_Up) {
			player->moveY(-move_distance_on_grid);
		}
		else if (ev->key() == Qt::Key_Down) {
			player->moveY(move_distance_on_grid);
		}
		else if (ev->key() == Qt::Key_Escape) {
			this->releaseMouse();
			QMessageBox::information(this, "Info", "You gave up!");
			this->close();
		}
	}


	/*
	Defines the gameplay itself - the collisions, the win objective
	*/
	void advanceGame() {

		auto collides = player->collidingItems();

		for (auto el : collides) {
			if (el == winObjective) {//reach the goal
				engine->goalHit();
			}
			else {//hit a wall
				engine->wallHit();
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
		setBackgroundBrush(QBrush(QColor(170, 230, 255, 127)));//lightblue

	}


	//void GAME::MouseButtonPress(QMouseEvent* ev) {
	//	ev->ignore();
	//}
	//this should have disabled mouse on screen.... it did not work...

public:

	GAME(Commander* commander, GameEngine* engine, bool mouse_tracking) :
		commander{ commander }, engine { engine }, sceneWidth{ this->commander->getSceneW() }, sceneHeight{ this->commander->getSceneH() }, playerWidth{ this->commander->getPlayerW() },
		playerHeight{ this->commander->getPlayerH() }, winObjectiveWidth{ this->commander->getWinObjW() }, winObjectiveHeight{ this->commander->getWinObjH() },
		move_distance_on_grid{ this->commander->getMoveDistanceOnGrid() } {
		


		setMouseTracking(mouse_tracking);
		
		if (mouse_tracking) {//we create a pause so that the player puts their mouse arrow right on the red square
			//we should create an itermediate class all above the others so that it knows everything and it can transmit that information whenever is needed
			//(like now, when I'm trying to use player coordinates in GameEngine, and whether mouse is trackable)
		}




		initScene(sceneWidth, sceneHeight);
		initEnclosingWals();
		createPlayer(playerWidth, playerHeight, 3 * playerWidth / 2, 3 * playerHeight / 2);// 50 50
		createWinObjective(winObjectiveWidth, winObjectiveHeight, 3 * winObjectiveWidth / 2, 3 * winObjectiveHeight / 2);//65 70
		//objective could be moved upwards in some cases...


		initSignalSlots();

		this->move(0,0);

		//QCursor::setPos(QWidget::mapFromGlobal(QPoint(width(), height())));//horrifyingly unexplainable behaviour...
		if (mouse_tracking) {
			QCursor::setPos(0 + playerWidth, height() - playerHeight);
		}
		else {
			this->grabMouse();
			//this->underMouse() - this could be useful later...
		}
		

		//QCursor::setPos(QWidget::mapFromGlobal(QPoint(width(), 600)));
	}

};