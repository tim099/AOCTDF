/*
 * GameOverUI.h
 *
 *  Created on: 2016¦~7¤ë30¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_PLAYERUI_GAMEOVERUI_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_PLAYERUI_GAMEOVERUI_H_

#include <string>
#include "class/display/UI/UI.h"
#include "class/display/UI/string/UIString.h"

namespace UI {

class GameOverUI :public UI {
public:
	GameOverUI();
	virtual ~GameOverUI();
	virtual UIObject* create_UIObject(){
		return new GameOverUI();
	}
	virtual std::string get_type()const{
		return "GameOverUI";
	}
	bool check_script();
	void init_gameOverUI();
private:
	bool inited;
};

} /* namespace AOC */


#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_PLAYER_PLAYERUI_GAMEOVERUI_H_ */
