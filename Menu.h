#pragma once
#include <qwidget.h>
#include <QtWidgets\qformlayout.h>
#include <qradiobutton.h>
#include <QtWidgets/qpushbutton.h>
#include <QLabel>
#include <QtWidgets/qboxlayout.h>
#include <qlistwidget.h>

#include "GameEngine.h"
#include "GAME.h"
#include "Service.h"


class Highscores : public QWidget {
private:
	Service& ctrl;

	QListWidget* lst = new QListWidget;
	
	void reloadList(vector<Highscore> elems) {
		int top = 1;
		for (const auto& el : elems) {
			QListWidgetItem* item = new QListWidgetItem;
			item->setText(QString::fromStdString(std::to_string(top) + " " + el.toString()));
			top++;
			lst->addItem(item);
		}
	}

	void GUIsetup() {
		QVBoxLayout* linit = new QVBoxLayout;
		this->setLayout(linit);
		linit->addWidget(new QLabel{ "HIGHSCORES" });
		linit->addWidget(lst);
	}
	void setSignalSlots() {}
	void initialGUIstate() { reloadList(this->ctrl.getHighscores()); }
public:
	Highscores(Service& ctrl) : ctrl{ ctrl } {
		GUIsetup();
		setSignalSlots();
		initialGUIstate();
	}
};

class Settings : public QWidget {
private:


	Service& ctrl;


	QPushButton* btnReset = new QPushButton{ "RESET TO DEFAULT SETTINGS" };
	QPushButton* btnSave = new QPushButton{ "SAVE THE CHANGES MADE" };


	QLabel* labK_M = new QLabel{ "SELECT MOVEMENT USING KEYBOARD/MOUSE:" };
	QRadioButton* radioK = new QRadioButton;
	QRadioButton* radioM = new QRadioButton;


	QLabel* labDif = new QLabel{ "SELECT DIFFICULTY (easy/normal/hard):" };
	QRadioButton* radioDif1 = new QRadioButton;
	QRadioButton* radioDif2 = new QRadioButton;
	QRadioButton* radioDif3 = new QRadioButton;




	void GUIsetup() {


		QWidget* wdgk_m = new QWidget;
		QHBoxLayout* hk_m = new QHBoxLayout;
		wdgk_m->setLayout(hk_m);
		hk_m->addWidget(radioK);
		hk_m->addWidget(radioM);


		QWidget* wdgd = new QWidget;
		QHBoxLayout* hd = new QHBoxLayout;
		wdgd->setLayout(hd);
		hd->addWidget(radioDif1);
		hd->addWidget(radioDif2);
		hd->addWidget(radioDif3);



		QVBoxLayout* linit = new QVBoxLayout;
		this->setLayout(linit);
		linit->addWidget(new QLabel{ "SETTINGS" });

		QWidget* wdgLst = new QWidget;
		QFormLayout* lform = new QFormLayout;
		wdgLst->setLayout(lform);
		lform->addRow(labK_M, wdgk_m);
		lform->addRow(labDif, wdgd);
		lform->addRow(btnReset, btnSave);


		linit->addWidget(wdgLst);

	}


	void setSignalSlots() {

		QObject::connect(btnReset, &QPushButton::clicked, this, [&]() {
			this->ctrl.setCommandType(1);
			this->ctrl.setDifficulty(2);
			this->close();
		});

		QObject::connect(btnSave, &QPushButton::clicked, this, [&]() {this->close(); });

		QObject::connect(radioK, &QRadioButton::clicked, this, [&]() {this->ctrl.setCommandType(1); });
		QObject::connect(radioM, &QRadioButton::clicked, this, [&]() {this->ctrl.setCommandType(2); });



		QObject::connect(radioDif1, &QRadioButton::clicked, this, [&]() {this->ctrl.setDifficulty(1); });
		QObject::connect(radioDif2, &QRadioButton::clicked, this, [&]() {this->ctrl.setDifficulty(2); });
		QObject::connect(radioDif3, &QRadioButton::clicked, this, [&]() {this->ctrl.setDifficulty(3); });
	}


	void initialGUIstate() {
		if(ctrl.getDifficulty() == 1)
			this->radioDif1->setChecked(true);
		else if(ctrl.getDifficulty() == 2)
			this->radioDif2->setChecked(true);
		else if(ctrl.getDifficulty() == 3)
			this->radioDif3->setChecked(true);

		if(ctrl.getCommandType() == 1)
			this->radioK->setChecked(true);
		else if(ctrl.getCommandType() == 2)
			this->radioM->setChecked(true);
	}

public:
	Settings(Service& ctrl) : ctrl{ ctrl } {
		GUIsetup();
		setSignalSlots();
		initialGUIstate();
	}
};











class Menu : public QWidget {
private:

	Service& ctrl;

	GameEngine* engine = nullptr;
	GAME* view = nullptr;

	QPushButton* btnPlay = new QPushButton{ "PLAY" };
	QPushButton* btnHigh = new QPushButton{ "HIGHSCORES" };
	QPushButton* btnSett = new QPushButton{ "SETTINGS" };
	QPushButton* btnExit = new QPushButton{ "EXIT" };

	void createGameAccordingToSettings() {
		//in further updates, th game itself could be more personalised

		//set the control mode
		bool trackable = false;
		if (this->ctrl.getCommandType() == 1)
			trackable = false;
		else if (this->ctrl.getCommandType() == 2)
			trackable = true;


		//set the timer and path length according to the difficulty
		if (this->ctrl.getDifficulty() == 1) {
			engine = new GameEngine{ ctrl, 999999999 };
			view = new GAME{ engine,	600,600,	30,30,	50,50,	30,	trackable };
		}
		else if (this->ctrl.getDifficulty() == 2) {
			engine = new GameEngine{ ctrl, 15000 };
			view = new GAME{ engine,	800,600,	30,30,	50,50,	30,	trackable };
		}
		else if (this->ctrl.getDifficulty() == 3) {
			engine = new GameEngine{ ctrl, 10000 };
			view = new GAME{ engine,	1200,600,	30,30,	50,50,	30,	trackable };
		}
		view->show();
		engine->startGame();
		//TODO prepare start should ensure fair-play (teleportation-proof)//engine->prepareStart();
	}

	void GUIsetup() {
		QVBoxLayout* linit = new QVBoxLayout;
		this->setLayout(linit);

		linit->addWidget(new QLabel{ "!!!HARDEST GAME EVER!!!" });
		linit->addWidget(btnPlay);
		linit->addWidget(btnHigh);
		linit->addWidget(btnSett);
		linit->addWidget(btnExit);
	}
	
	void setSignalSlots() {

		QObject::connect(btnPlay, &QPushButton::clicked, this, &Menu::createGameAccordingToSettings);


		QObject::connect(btnHigh, &QPushButton::clicked, this, [&]() {
			Highscores* high = new Highscores{ ctrl };
			high->show();
		});


		QObject::connect(btnSett, &QPushButton::clicked, this, [&]() {
			Settings* wndw = new Settings{ ctrl };
			wndw->show();
		});


		QObject::connect(btnExit, &QPushButton::clicked, this, [&]() {this->close(); });
	}
	
	void initialGUIstate() {

	}

public:
	Menu(Service& ctrl) : ctrl{ ctrl } {
		GUIsetup();
		setSignalSlots();
		initialGUIstate();
	}
	~Menu() {
		if (engine != nullptr)
			delete engine;
		if (view != nullptr)
			delete view;
	}
};




