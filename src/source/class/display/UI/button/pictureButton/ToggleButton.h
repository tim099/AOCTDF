/*
 * ToggleButton.h
 *
 *  Created on: 2016�~5��16��
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_DISPLAY_UI_BUTTON_PICTUREBUTTON_TOGGLEBUTTON_H_
#define SOURCE_CLASS_DISPLAY_UI_BUTTON_PICTUREBUTTON_TOGGLEBUTTON_H_

#include "class/display/UI/button/pictureButton/PictureButton.h"

namespace UI {

class ToggleButton: public PictureButton {
public:
	ToggleButton(math::vec2<float> pos,std::string tex_path,float width,float height=AutoHeight);
	ToggleButton();
	virtual ~ToggleButton();
	virtual void selected(Input::Mouse* mou);
	virtual std::string get_type()const {
		return "ToggleButton";
	}
	virtual UIObject* create_UIObject();
protected:
	virtual void update();
	bool hide_children;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_DISPLAY_UI_BUTTON_PICTUREBUTTON_TOGGLEBUTTON_H_ */
