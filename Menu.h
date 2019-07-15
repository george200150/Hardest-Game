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
			item->setText(QString::fromStdString(std::to_string(top) + ". " + el.toString()));
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


	//here, there should be another setting to assign keys for the game functions
	QLabel* labKeys = new QLabel{ "SELECT KEYS:" };
	QLabel* labMoveUp = new QLabel{ "MOVE UP:" };
	QLabel* labMoveDown = new QLabel{ "MOVE DOWN:" };
	QLabel* labMoveLeft = new QLabel{ "MOVE LEFT:" };
	QLabel* labMoveRight = new QLabel{ "MOVE RIGHT:" };

	QPushButton* btnMU = new QPushButton{ "CHANGE (assign another key)" };
	QPushButton* btnMD = new QPushButton{ "CHANGE (assign another key)" };
	QPushButton* btnML = new QPushButton{ "CHANGE (assign another key)" };
	QPushButton* btnMR = new QPushButton{ "CHANGE (assign another key)" };



	void GUIsetup() {

		//QWidget* wdg_key = new QWidget;
		//QFormLayout* flay = new QFormLayout;
		//wdg_key->setLayout(flay);
		//flay->addRow(labKeys);
		//flay->addRow(labMoveUp, btnMU);
		//flay->addRow(labMoveDown, btnMD);
		//flay->addRow(labMoveLeft, btnML);
		//flay->addRow(labMoveRight, btnMR);


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
		//lform->addRow(labKeys, wdg_key);
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

		/*

		M	U	S	T		U	S	E		A		V	E	C	T	O	R		F	O	R		K	E	Y	S	!!!


		WELL, AS YOU CAN SEE, THINGS GOT MESSY.
		THEREFORE, I WILL GET A CLASS ATTRIBUTE WHICH REPRESENTS THE CHOSEN BUTTON TO BE ASSIGNED A NEW KEY.
		THAT BUTTON STAYS *null* BEFORE AND AFTER THE ASSIGNMENT (THE CLASS ATTRIBUTE REFFERING THE BUTTON WILL BE RESET AFTER KeyPress Event)

		WE SHOULD ALSO CONSIDER NOT ASSIGNING ANY KEY TO THE BUTTON... IN THIS CASE, THE BUTTON SHOULD BE SET TO *null* OR ASSIGNED ITS DEFAULT VALUE.
		HOW - well after a given time runs out



		..............or..............

		*I could create a virtual keyboard to ease everything... ( it seems cooler, but less user friendly...I guess...)


		..............else..............


		create a line edit for each command, create a map of assignable keys and ensure that each command has a key and only one assigned
		*/

		
		//QKeyEvent::KeyPress
		//QObject::connect();
		//QObject::connect(btnMU, &QPushButton::clicked, this, [&]() {
		//	QKeyEvent* ev;
		//	//int assignment = ev->KeyPress(); - won't work like this, it's a signal or something...
		//	int new_key_assignment = ev->key();
		//	auto keys = this->ctrl.getAssignedKeys();
		//	keys[0] = new_key_assignment;
		//	this->labMoveUp->setText("MOVE UP: " + ev->key());
		//});
		//QObject::connect(btnMU, &QPushButton::clicked, this, [&]() {
		//	QKeyEvent* ev;
		//	int new_key_assignment = ev->key();
		//	auto keys = this->ctrl.getAssignedKeys();
		//	keys[1] = new_key_assignment;
		//	this->labMoveDown->setText("MOVE DOWN: " + ev->key());
		//});
		//QObject::connect(btnMU, &QPushButton::clicked, this, [&]() {
		//	QKeyEvent* ev;
		//	int new_key_assignment = ev->key();
		//	auto keys = this->ctrl.getAssignedKeys();
		//	keys[2] = new_key_assignment;
		//	this->labMoveLeft->setText("MOVE LEFT: " + ev->key());
		//});
		//QObject::connect(btnMU, &QPushButton::clicked, this, [&]() {
		//	QKeyEvent* ev;
		//	int new_key_assignment = ev->key();
		//	auto keys = this->ctrl.getAssignedKeys();
		//	keys[0] = new_key_assignment;
		//	this->labMoveRight->setText("MOVE RIGHT: " + ev->key());
		//});
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

		//auto assigned_keys = this->ctrl.getAssignedKeys();
		//int key_up = assigned_keys.at(0);
		//int key_down = assigned_keys.at(1);
		//int key_left = assigned_keys.at(2);
		//int key_right = assigned_keys.at(3);
		//labMoveUp->setText(labMoveUp->text() + " " + QString::fromStdString(std::to_string(key_up)));
		//labMoveDown->setText(labMoveDown->text() + " " + QString::fromStdString(std::to_string(key_down)));
		//labMoveLeft->setText(labMoveLeft->text() + " " + QString::fromStdString(std::to_string(key_left)));
		//labMoveRight->setText(labMoveRight->text() + " " + QString::fromStdString(std::to_string(key_right)));
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

	Commander* commander = nullptr;
	GameEngine* engine = nullptr;
	GAME* view = nullptr;


	QPushButton* btnPlay = new QPushButton{ "PLAY" };
	QPushButton* btnHigh = new QPushButton{ "HIGHSCORES" };
	QPushButton* btnSett = new QPushButton{ "SETTINGS" };
	QPushButton* btnExit = new QPushButton{ "EXIT" };

	void createGameAccordingToSettings() {

		//set the control mode
		bool trackable = false;
		if (this->ctrl.getCommandType() == 1)
			trackable = false;
		else if (this->ctrl.getCommandType() == 2)
			trackable = true;

		//----------------------------------------
		int wall_w, wall_h;
		wall_w = 25;
		wall_h = 600 - 60;// THIS MAY BE CHANGED...
		//----------------------------------------

		//set the timer and path length according to the difficulty (maybe)
		if (this->ctrl.getDifficulty() == 1) {
			commander = new Commander{ ctrl,30, 30,wall_w,wall_h,50, 50, 600, 600, 30};
			engine = new GameEngine{ commander, 60000 };//60 seconds
			view = new GAME{ commander, engine,	trackable };
		}
		else if (this->ctrl.getDifficulty() == 2) {
			commander = new Commander{ ctrl,30, 30,wall_w,wall_h,50, 50, 800, 600, 30 };
			engine = new GameEngine{ commander, 15000 };//15 seconds
			view = new GAME{ commander, engine,	trackable };
		}
		else if (this->ctrl.getDifficulty() == 3) {
			commander = new Commander{ ctrl,30, 30,wall_w,wall_h,50, 50, 1150, 600, 30 };
			engine = new GameEngine{ commander, 10000 };//10 seconds
			view = new GAME{ commander, engine,	trackable };
		}

		//view->showFullScreen(); this is going to be messy. Now, I can map global resolution coordinates into the window (maybe not neccessary)
		//that's the part when absolute(x,y) / 2 - window(x,y) comes in...
		//- anyways, there are too many problems and a single me...

		view->show();
		engine->startGame();
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
	Menu(Service& ctrl) : ctrl{ ctrl} {
		GUIsetup();
		setSignalSlots();
		initialGUIstate();
	}
	~Menu() {
		if (engine != nullptr)
			delete engine;
		if (view != nullptr)
			delete view;
		if (commander != nullptr)
			delete commander;
	}
};
