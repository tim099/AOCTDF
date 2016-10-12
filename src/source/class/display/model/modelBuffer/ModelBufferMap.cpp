#include "class/display/model/modelBuffer/ModelBufferMap.h"
#include "class/tim/string/String.h"
namespace Display{
ModelBufferMap::ModelBufferMap() {

}
ModelBufferMap::ModelBufferMap(std::string _path,std::string folder_path){
	path=_path;
	Load_script(folder_path+path);
}
ModelBufferMap::~ModelBufferMap() {

}
std::string ModelBufferMap::get_name() const {
	return name;
}
void ModelBufferMap::set_name(std::string _name) {
	name = _name;
}
void ModelBufferMap::push(std::string name,ModelBuffer* buffer){
	mbuffer_map.push(name,buffer);
}
ModelBuffer* ModelBufferMap::get(std::string name){
	return mbuffer_map.get(name);
}
void ModelBufferMap::Parse_Header(std::istream &is, std::string &line) {
	if (line == "FolderPath:") {
		Tim::String::get_line(is, folder_path, true, true);
	} else if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(std::string(line));
	}
}
void ModelBufferMap::Parse_Header(std::ostream &os){
	os << "FolderPath:" << std::endl;
	os << "    "+folder_path << std::endl;
	os << "Name:" << std::endl;
	os << "    "+name << std::endl;
}
void ModelBufferMap::Parse_Script(std::istream &is,std::string &line){
	if(line=="ModelBuffer:"){
		ModelBuffer* m=new ModelBuffer();
		m->load(is,folder_path);
		push(m->get_name(),m);
	}
}
void ModelBufferMap::Parse_Script(std::ostream &os){
	std::map<std::string,ModelBuffer*>*all_maps=mbuffer_map.get_map();
	typename std::map<std::string,ModelBuffer*>::iterator it = all_maps->begin();
	ModelBuffer* model;
	while (it != all_maps->end()) {
		model=it->second;
		os<<"ModelBuffer:"<<std::endl;
		model->save(os);

		it++;
	}
}
}

