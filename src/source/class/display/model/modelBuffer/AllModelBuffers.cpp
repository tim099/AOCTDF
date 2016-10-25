#include "class/display/model/modelBuffer/AllModelBuffers.h"
namespace Display{
AllModelBuffers::AllModelBuffers() {

}
AllModelBuffers::AllModelBuffers(std::string _path,std::string folder_path) {
	path=_path;
	Load_script(folder_path+path);
}
AllModelBuffers::~AllModelBuffers() {

}
ModelBuffer *AllModelBuffers::get_cur_model(std::string obj_path){
	return AllModelBuffers::get_cur_object()->get(obj_path);
}
void AllModelBuffers::Parse_map(std::istream &is){
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		ModelBufferMap* map=new ModelBufferMap(scriptPath,folder_path);
		push_map(map);
	}
}
void AllModelBuffers::Parse_dir(std::istream &is){
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		AllModelBuffers* dir=new AllModelBuffers(scriptPath,folder_path);
		push_dir(dir);
	}
}
void AllModelBuffers::Parse_Script(std::istream &is, std::string &line){
	if (line=="Map:") {
		Parse_map(is);
	}else if(line=="Dir:"){
		Parse_dir(is);
	}
}
void AllModelBuffers::Parse_Script(std::ostream &os){
	{
	std::map<std::string,ModelBufferMap*>*all_maps=maps.get_map();
	typename std::map<std::string,ModelBufferMap*>::iterator it = all_maps->begin();
	ModelBufferMap* map;
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
	std::map<std::string,MapTree<ModelBufferMap, ModelBuffer>* >*all_dirs=dirs.get_map();
	typename std::map<std::string,MapTree<ModelBufferMap, ModelBuffer>* >::iterator it=all_dirs->begin();
	AllModelBuffers* dir;
	while (it != all_dirs->end()) {
		dir=dynamic_cast<AllModelBuffers*>(it->second);
		dir->Save_script(folder_path+dir->path);

		os<<"Dir:"<<std::endl;
		os<<"	ScriptPath:"<<std::endl;
		os<<"		"+dir->path<<std::endl;

		it++;
	}
	}
}
void AllModelBuffers::Parse_Header(std::istream &is, std::string &line){
	if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}else if (line == "FolderPath:") {
		Tim::String::get_line(is, line, true, true);
		folder_path = std::string(line);
	}
}
void AllModelBuffers::Parse_Header(std::ostream &os){
	os << "FolderPath:" << std::endl;
	os << "    "+folder_path << std::endl;
	os << "Name:" << std::endl;
	os << "    "+name << std::endl;
}
}
