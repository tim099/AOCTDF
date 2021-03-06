#include "class/display/UI/button/Button.h"
#include "class/input/mouse/Mouse.h"
#include "class/tim/geometry/2D/RectP2D.h"
#include "class/input/signal/Signal.h"
#include "class/audio/AudioController.h"

#include "class/input/Input.h"
#include <iostream>
//#include "class/tim/math/Math.h"

namespace UI {
Button* Button::cur_selected_but=0;
Button::Button() {
	signal=0;
}
Button::~Button() {
	if(signal)delete signal;
	if(cur_selected_but==this){
		cur_selected_but=0;
	}
}
void Button::selected(Input::Mouse* mou){
	if(check_mode(UI::Mode::EDIT)){
		return;
	}
	cur_selected_but=this;
	Input::Signal *sig=get_signal();
	if(sig){
		sig->sent();
	}else{
		std::cerr<<"Button::selected: sig not set"<<std::endl;
	}
	Audio::AudioController::get_cur_object()->play("default_sound_effect/QQ.wav");
	//std::cout<<"selected : "<<get_type()<<std::endl;
}
void Button::set_signal(Input::Signal* _signal){
	if(signal)delete signal;
	signal=_signal;
}
Input::Signal* Button::get_signal()const{
	return signal;
}
void Button::update(){
	update_button();
}
void Button::update_button(){

}
} /* namespace UI */
