#ifndef SOURCE_CLASS_DISPLAY_UI_STRING_ENTERSTRING_H_
#define SOURCE_CLASS_DISPLAY_UI_STRING_ENTERSTRING_H_
#include "class/display/UI/string/UIString.h"
#include "class/input/mouse/selectable/rectangle/SelectableRec.h"
namespace UI {

class EnterString : public UIString{
public:
	EnterString();
	virtual ~EnterString();
	virtual UIObject* create_UIObject(){
		return new EnterString();
	}
	virtual std::string get_type()const{
		return "EnterString";
	}
protected:
	virtual void update();
	virtual void Parse_UIString(std::istream &is,std::string &line);
	virtual void Parse_UIString(std::ostream &os);
	virtual void draw_UIString(Display::Draw* draw);
	std::string tex_path;
};

} /* namespace UI */

#endif /* SOURCE_CLASS_DISPLAY_UI_STRING_ENTERSTRING_H_ */
