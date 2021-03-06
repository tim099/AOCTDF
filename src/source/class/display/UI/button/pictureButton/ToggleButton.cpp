#include <iostream>
#include "class/display/UI/button/pictureButton/ToggleButton.h"
#include "class/audio/AudioController.h"

namespace UI {

ToggleButton::ToggleButton(math::vec2<float> pos,std::string tex_path,float _width,float _height)
	:PictureButton(pos, tex_path, _width, _height){
	hide_children=true;
	height= 10;
	//std::cout<<"construct toggle button"<<std::endl;

}

ToggleButton::ToggleButton()
	:PictureButton(){
	hide_children=true;
}
ToggleButton::~ToggleButton() {
}

void ToggleButton::selected(Input::Mouse* mou){
	if(check_mode(UI::Mode::EDIT)){
		return;
	}
	Input::Signal *sig=get_signal();
	if(sig){
		sig->sent();
	}
	Audio::AudioController::get_cur_object()->play("default_sound_effect/Pickup_Coin2.wav");
	hide_children^=1;
}
void ToggleButton::update(){
	for (unsigned int i=0; i<childs.size(); i++) {
		childs[i]->hide = hide_children;
	}
}
UIObject* ToggleButton::create_UIObject(){
	return new ToggleButton();
}

} /* namespace AOC */
