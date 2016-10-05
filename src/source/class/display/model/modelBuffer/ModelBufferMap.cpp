#include "class/display/model/modelBuffer/ModelBufferMap.h"
#include "class/tim/string/String.h"
namespace Display{
ModelBufferMap::ModelBufferMap() {

}
ModelBufferMap::ModelBufferMap(std::string script_path){
	Load_script(script_path);
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
void ModelBufferMap::Parse_Script(std::istream &is,std::string &line){
	if(line=="ModelBuffer:"){
		ModelBuffer* m=new ModelBuffer();
		m->load(is,folder_path);
		push(m->get_name(),m);
	}
}
}

