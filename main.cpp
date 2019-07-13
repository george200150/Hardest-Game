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




int main(int argc, char *argv[])
{
	QApplication a(argc, argv);


	GameEngine engine{ 10000 };
	GAME* view = new GAME{ engine,	800,600,	30,30,	50,50,	30,	true };
	view->show();

	engine.startGame();

	return a.exec();

}