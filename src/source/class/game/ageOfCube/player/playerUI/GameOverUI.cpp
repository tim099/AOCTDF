/*
 * GameOverUI.cpp
 *
 *  Created on: 2016�~7��30��
 *      Author: LukeWu
 */

#include <iostream>
#include "class/tim/string/String.h"
#include "class/game/ageOfCube/player/playerUI/GameOverUI.h"

namespace UI {


GameOverUI::GameOverUI() {
	inited = false;

}

GameOverUI::~GameOverUI() {
	// TODO Auto-generated destructor stub
}

void GameOverUI::init_gameOverUI(){

	inited = true;
}

bool GameOverUI::check_script(){
	return true;
}


}
