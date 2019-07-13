#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Hardest_Game.h"

class Hardest_Game : public QMainWindow
{
	Q_OBJECT

public:
	Hardest_Game(QWidget *parent = Q_NULLPTR);

private:
	Ui::Hardest_GameClass ui;
};
