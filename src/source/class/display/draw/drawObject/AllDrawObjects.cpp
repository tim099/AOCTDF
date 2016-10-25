#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace Display{
AllDrawObjects::AllDrawObjects() {

}
AllDrawObjects::AllDrawObjects(std::string _path,std::string folder_path) {
	path=_path;
	Load_script(path+folder_path);
}
AllDrawObjects::~AllDrawObjects() {

}
void AllDrawObjects::Parse_map(std::istream &is){
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		DrawObjectMap* map=new DrawObjectMap(scriptPath,folder_path);
		push_map(map);
	}
}
void AllDrawObjects::Parse_dir(std::istream &is){
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		AllDrawObjects* dir=new AllDrawObjects(scriptPath,folder_path);
		push_dir(dir);
	}
}
void AllDrawObjects::Parse_Script(std::istream &is, std::string &line){
	if (line=="Map:") {
		Parse_map(is);
	}else if(line=="Dir:"){
		Parse_dir(is);
	}
}
void AllDrawObjects::Parse_Script(std::ostream &os){
	{
	std::map<std::string,DrawObjectMap*>*all_maps=maps.get_map();
	typename std::map<std::string,DrawObjectMap*>::iterator it = all_maps->begin();
	DrawObjectMap* map;
	while (it != all_maps->end()) {
		map=it->second;
		map->Save_script(folder_path+map->path);

		os<<"Map:"<<std::endl;
		os<<"	ScriptPath:"<<std::endl;
		os<<"		"+map->path<<std::endl;

		it++;
	}
	}
	{
	std::map<std::string,MapTree<DrawObjectMap, DrawObject>* >*all_dirs=dirs.get_map();
	typename std::map<std::string,MapTree<DrawObjectMap, DrawObject>* >::iterator it=all_dirs->begin();
	AllDrawObjects* dir;
	while (it != all_dirs->end()) {
		dir=dynamic_cast<AllDrawObjects*>(it->second);
		dir->Save_script(folder_path+dir->path);

		os<<"Dir:"<<std::endl;
		os<<"	ScriptPath:"<<std::endl;
		os<<"		"+dir->path<<std::endl;

		it++;
	}
	}
}
void AllDrawObjects::Parse_Header(std::istream &is, std::string &line){
	if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}else if (line == "FolderPath:") {
		Tim::String::get_line(is, line, true, true);
		folder_path = std::string(line);
	}
}
void AllDrawObjects::Parse_Header(std::ostream &os){
	os << "FolderPath:" << std::endl;
	os << "    "+folder_path << std::endl;
	os << "Name:" << std::endl;
	os << "    "+name << std::endl;
}
}
