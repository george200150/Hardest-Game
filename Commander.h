#pragma once

#include "Service.h"

class Commander {
private:

	Service& ctrl;

	int player_w, player_h;

	int win_obj_w, win_obj_h;

	int scene_w, scene_h;

	int wall_w, wall_h;

	int move_distance_on_grid;

	bool ESC_press;

public:

	Commander(Service& ctrl, int player_w, int player_h, int wall_w, int wall_h, int win_obj_w, int win_obj_h, int scene_w, int scene_h, int move_distance_on_grid) : ctrl{ ctrl },
		player_w{ player_w }, player_h{ player_h }, wall_w{ wall_w }, wall_h{ wall_h }, win_obj_w{ win_obj_w }, win_obj_h{ win_obj_h }, scene_w{ scene_w }, scene_h{ scene_h },
		move_distance_on_grid{ move_distance_on_grid }{ ESC_press = false; }


	//Service& getService() {
	//	return this->ctrl;
	//} - this is inexplicably wrong

	int getCommandType() const {
		return this->ctrl.getCommandType();
	}

	int getDifficulty() const {
		return this->ctrl.getDifficulty();
	}

	vector<Highscore>& getHighscores() {
		return this->ctrl.getHighscores();
	}

	string getName() const {
		return this->ctrl.getName();
	}

	void setCommandType(int newCommandType) {
		this->ctrl.setCommandType(newCommandType);
	}
	void setDifficulty(int newDifficulty) {
		this->ctrl.setDifficulty(newDifficulty);
	}
	void setName(string newYou) {
		this->ctrl.setName(newYou);
	}

	void addHighscore(Highscore h) {
		this->ctrl.addHighscore(h);
	}
	// ^ Service inherited functions ^ //



	int getPlayerW() const {
		return this->player_w;
	}

	int getPlayerH() const {
		return this->player_h;
	}



	int getWinObjW() const {
		return this->win_obj_w;
	}

	int getWinObjH() const {
		return this->win_obj_h;
	}



	int getSceneW() const {
		return this->scene_w;
	}

	int getSceneH() const {
		return this->scene_h;
	}



	int getWallW() const {
		return this->wall_w;
	}

	int getWallH() const {
		return this->wall_h;
	}

	int getMoveDistanceOnGrid() const {
		return this->move_distance_on_grid;
	}

	bool escWasPressed() const {
		return this->ESC_press;
	}

	void setEscPress() {
		this->ESC_press = true;
	}
};

