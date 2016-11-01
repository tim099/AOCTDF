#include "class/display/UI/string/EnterString.h"

#include "class/display/draw/Draw.h"
#include "class/display/font/RenderString.h"
#include "class/input/signal/Receiver.h"
#include "class/input/Input.h"
#include "class/input/mouse/Mouse.h"
#include "class/display/texture/texture2D/drawDataEX/ColorAlter.h"
#include "class/display/draw/Draw.h"
#include "class/display/texture/AllTextures.h"
#include <iostream>
namespace UI {

EnterString::EnterString() {
	input_mode=false;
	//cur_input_str=this;
	tex_path="UI/UI/button2";
	width=0.2;
}
EnterString::~EnterString() {

}
void EnterString::update(){
	//input_mode=true;
	if(receiver){
		Input::Signal *sig=receiver->get_signal();
		if(sig){
			str=sig->get_data();
		}
	}
	if(cur_insert_at<0)cur_insert_at=0;
	if(cur_insert_at>=(int)str.size())cur_insert_at=str.size();

	if(Input::Input::get_cur_object()->mouse->left_clicked()){
		if (get_state() == state_select) {
			enable_input();
			Input::Mouse *mou=Input::Input::get_cur_object()->mouse;
			double dx=(mou->get_tex_space_pos().x-get_pos().x);

			cur_insert_at=((dx/Display::RenderString::font_size(font_size).x)+0.5);
			if(cur_insert_at<0)cur_insert_at=0;
			if(cur_insert_at>=(int)str.size())cur_insert_at=str.size();
		}else{
			disable_input();
		}
	}
	if(cur_input_str==this){
		Input::KeyBoard* keyboard=Input::Input::get_cur_object()->keyboard;
		if(keyboard->get(Input::KeyCode::Left)){
			if(cur_insert_at>0)cur_insert_at--;
		}else if(keyboard->get(Input::KeyCode::Right)){
			if(cur_insert_at<(int)str.size())cur_insert_at++;
		}else if(keyboard->get(Input::KeyCode::BackSpace)){
			if(str.size()>0&&cur_insert_at>0){
				std::string tmp=str.substr(cur_insert_at,str.size());
				str.resize(cur_insert_at-1);
				//str->erase(cur_insert_at-1);
				str+=tmp;
				cur_insert_at--;
				size = math::vec2<float>(1,2)*Display::RenderString::string_size(&str,font_size);
			}
		}else{
			unsigned c=keyboard->get_char();
			if(c!=0&&c<256){
				std::string tmp=str.substr(cur_insert_at,str.size());
				//str->erase(cur_insert_at);
				str.resize(cur_insert_at);
				str.push_back((char)c);
				str+=tmp;
				cur_insert_at++;
				size=math::vec2<float>(1,2)*Display::RenderString::string_size(&str,font_size);
			}
		}
		keyboard->clear_keys();
		keyboard->clear_chars();

		if(blink>60){
			blink=0;
		}else{
			blink++;
		}
		if(blink<40){
			insert_at=cur_insert_at;
		}else{
			insert_at=-1;
		}
	}
	size.x=width;
}
void EnterString::draw_UIString(Display::Draw* draw){
	Display::Texture*tex2D=Display::AllTextures::get_cur_tex(tex_path);
	Display::DrawData* data = new Display::DrawData2D(1.0, get_pos(),size.x,0.5*(size.y/size.x)
			*tex2D->get_aspect());
	if(check_mode(UI::Mode::EDIT)){
		if (state == Selectable::state_on) {
			data->ex_datas.push_back(
					new Display::drawDataEX::ColorAlter(glm::vec3(0.3, 0.3, 0.3)));
		} else if (state == Selectable::state_selected) {
			data->ex_datas.push_back(
					new Display::drawDataEX::ColorAlter(glm::vec3(0.7, 0.7, 0.7)));
		}
	}else{
		data->ex_datas.push_back(
				new Display::drawDataEX::ColorAlter(glm::vec3(-0.3,-0.3,-0.3)));
	}
	draw->push(new Display::DrawTexture(tex2D, data));
}
void EnterString::Parse_UIString(std::istream &is,std::string &line){
	if (line == "Texture:") {
		Tim::String::get_line(is, tex_path, true, true);
	}else if(line == "Width:"){
		is>>width;
	}
}
void EnterString::Parse_UIString(std::ostream &os){
	os<<"	"<<"Texture:"<<std::endl;
	os<<"		"<<tex_path<<std::endl;
}
} /* namespace UI */
