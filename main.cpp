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


	GameEngine engine;
	GAME* view = new GAME{ engine };
	view->show();

	engine.startGame();

	return a.exec();

}