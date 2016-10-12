#ifndef SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DRAWOBJECTMAP_H_
#define SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DRAWOBJECTMAP_H_
#include "class/display/draw/drawObject/DrawObject.h"
#include "class/tim/map/MapContainer.h"
#include "class/tim/parser/Parser.h"
namespace Display{
class DrawObjectMap : public Tim::Parser{
public:
	DrawObjectMap();
	DrawObjectMap(std::string path,std::string folder_path="");
	virtual ~DrawObjectMap();

	std::string get_name()const;
	void set_name(std::string name);
	void push(DrawObject* obj);
	DrawObject* get(std::string name);
	std::string folder_path,path;
protected:
	virtual inline std::string Script_name()const{
		return "#LOAD_DRAWOBJECTMAP_SCRIPT";
	}
	virtual void Parse_Script(std::istream &is,std::string &line);
	virtual void Parse_Script(std::ostream &os);

	virtual void Parse_Header(std::istream &is,std::string &line);
	virtual void Parse_Header(std::ostream &os);
	//void Parse_DrawObject(std::istream &is);
	Tim::MapContainer<std::string,DrawObject>objs;
	std::string name;

};
}
#endif /* SOURCE_CLASS_DISPLAY_DRAW_DRAWOBJECT_DRAWOBJECTMAP_H_ */
