#ifndef SOURCE_CLASS_DISPLAY_UI_STRING_UISTRING_H_
#define SOURCE_CLASS_DISPLAY_UI_STRING_UISTRING_H_

#include "class/display/UI/UIObject.h"

namespace UI {

class UIString: public UIObject {
public:
	UIString();
	void initialize(std::string* str,float font_size);
	virtual ~UIString();

	virtual UIObject* create_UIObject(){
		return new UIString();
	}
	virtual std::string get_type()const{
		return "UIString";
	}
	void set_string(std::string str);
	std::string get_string();
	//if input_mode==true then this string will get the keyboard input
	bool input_mode;
	int insert_at;
protected:
	static UIString* cur_input_str;

	virtual void Parse_UIScript(std::istream &is,std::string &line);
	virtual void Parse_UIScript(std::ostream &os);

	virtual void Parse_UIString(std::istream &is,std::string &line){}
	virtual void Parse_UIString(std::ostream &os){}
	virtual void update();
	virtual void start_draw(Display::Draw* draw);
	virtual void draw_UIString(Display::Draw* draw){}
	inline void enable_input(){
		cur_input_str=this;
	}
	inline void disable_input(){
		if(cur_input_str==this){
			cur_input_str=0;
		}
	}
	std::string* str;
	int cur_insert_at;
	float font_size;
	int blink;
	//bool edit_on;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_STRING_UISTRING_H_ */
