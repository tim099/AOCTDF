#include "class/display/draw/drawObject/DrawObjectMap.h"
#include "class/tim/string/String.h"
#include "class/display/draw/Draw.h"
namespace Display{
DrawObjectMap::DrawObjectMap() {

}
DrawObjectMap::DrawObjectMap(std::string _path,std::string folder_path) {
	path=_path;
	Load_script(folder_path+path);
}
DrawObjectMap::~DrawObjectMap() {
	Display::Draw* cur_draw=Display::Draw::get_cur_object();

	if(!cur_draw){
		std::cerr<<"DrawObjectMap::~DrawObjectMap(), cur Draw is not exist!!"<<std::endl;
		return;
	}
	std::map<std::string, DrawObject*> *map=objs.get_map();
	std::map<std::string, DrawObject*>::iterator it = map->begin();
	while (it != map->end()) {
		cur_draw->remove((it->second));
		it++;
	}
}
std::string DrawObjectMap::get_name()const{
	return name;
}
void DrawObjectMap::set_name(std::string _name){
	name=_name;
}
void DrawObjectMap::push(DrawObject* obj){
	objs.push(obj->get_name(),obj);
}
bool DrawObjectMap::find(std::string name){
	return objs.find(name);
}
DrawObject* DrawObjectMap::get(std::string name){
	return objs.get(name);
}
void DrawObjectMap::Parse_Header(std::istream &is, std::string &line) {
	if (line == "FolderPath:") {
		Tim::String::get_line(is, line, true, true);
		folder_path = std::string(line);
	} else if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}
}
void DrawObjectMap::Parse_Header(std::ostream &os){
	os << "FolderPath:" << std::endl;
	os << "    "+folder_path << std::endl;
	os << "Name:" << std::endl;
	os << "    "+name << std::endl;
}

void DrawObjectMap::Parse_Script(std::istream &is,std::string &line){
	if(line=="DrawObject:"){
		DrawObject* d_obj=new DrawObject();
		d_obj->load(is);

		push(d_obj);
		Display::Draw::get_cur_object()->push(d_obj);
	}
}
void DrawObjectMap::Parse_Script(std::ostream &os){
	std::map<std::string,DrawObject*>*all_maps=objs.get_map();
	typename std::map<std::string,DrawObject*>::iterator it = all_maps->begin();
	DrawObject* obj;
	while (it != all_maps->end()) {
		obj=it->second;
		os<<"DrawObject:"<<std::endl;
		obj->save(os);

		it++;
	}
}
}
