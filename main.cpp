#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/qpushbutton.h>
#include <stdlib.h>
#include "GAME.h"
#include "GameEngine.h"
#include "Menu.h"



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Repo repo{ "highscores.txt" };
	Service ctrl{ repo };
	Menu* menu = new Menu{ ctrl };
	menu->show();


	/*GameEngine engine{ 10000 };//game engine used to be just A REFERENCE BACK IN THOSE DAYS...
	GAME* view = new GAME{ engine,	800,600,	30,30,	50,50,	30,	true };
	view->show();

	engine.startGame();*/

	return a.exec();


	/*
	Class creates a menu with <play>, <highscores>, <settings: <mouse/keyboard>, <difficulty - idk what should it consist of... (e.g. narrower paths, longer path, shorter time)>, <...>>
	(a GameEngine as with or without the trackable mouse)
	*/

}