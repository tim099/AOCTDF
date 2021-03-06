/*
 * PlayerUI.h
 *
 *  Created on: 2016�~6��9��
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_DISPLAY_UI_PLAYERUI_PLAYERUI_H_
#define SOURCE_CLASS_DISPLAY_UI_PLAYERUI_PLAYERUI_H_

#include <string>
#include "class/display/UI/UI.h"
#include "class/display/UI/string/UIString.h"
//#include "class/display/UI/UI3D/HealthCube3D.h"
#include "class/display/camera/Camera.h"

namespace AOC{
	class Player;
}

namespace UI {

class PlayerUI :public UI {
public:
	PlayerUI();
	virtual ~PlayerUI();
	virtual UIObject* create_UIObject(){
		return new PlayerUI();
	}
	virtual std::string get_type()const{
		return "PlayerUI";
	}
	bool check_script();
	void init_playerUI();
	void set_resource_amount(int value);
	void set_score(int score);
protected:
	virtual void start_draw(Display::Draw* draw);
private:
	UIString *health_string;
	UIString *resource_amount_string;
	UIString *score_string;
	bool inited;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_DISPLAY_UI_PLAYERUI_PLAYERUI_H_ */
