#include "class/display/texture/AllTextures.h"
#include "class/tim/file/File.h"
#include "class/tim/string/String.h"
#include <iostream>
#include <fstream>
namespace Display{
AllTextures::AllTextures(std::string _path,std::string folder_path){
	path=_path;
	Load_script(folder_path+path);
}
AllTextures::~AllTextures() {

}
Texture* AllTextures::get_cur_tex(std::string tex_path) {
	return get_cur_object()->get(tex_path);
}
void AllTextures::Parse_Script(std::istream &is, std::string &line) {
	if (line=="TextureMap:") {
		Parse_textureMap(is);
	}else if(line=="TextureDir:"){
		Parse_textureDir(is);
	}
}
void AllTextures::Parse_Script(std::ostream &os){
	{
	std::map<std::string,TextureMap*>*all_maps=maps.get_map();
	typename std::map<std::string,TextureMap*>::iterator it = all_maps->begin();
	TextureMap* map;
	while (it != all_maps->end()) {
		map=it->second;
		map->Save_script(folder_path+map->path);

		os<<"TextureMap:"<<std::endl;
		os<<"	ScriptPath:"<<std::endl;
		os<<"		"+map->path<<std::endl;

		it++;
	}
	}
	{
	std::map<std::string,MapTree<TextureMap, Texture>* >*all_dirs=dirs.get_map();
	typename std::map<std::string,MapTree<TextureMap, Texture>* >::iterator it=all_dirs->begin();
	AllTextures* dir;
	while (it != all_dirs->end()) {
		dir=dynamic_cast<AllTextures*>(it->second);
		dir->Save_script(folder_path+dir->path);

		os<<"TextureDir:"<<std::endl;
		os<<"	ScriptPath:"<<std::endl;
		os<<"		"+dir->path<<std::endl;

		it++;
	}
	}
}
void AllTextures::Parse_Header(std::ostream &os){
	os << "FolderPath:" << std::endl;
	os << "    "+folder_path << std::endl;
	os << "Name:" << std::endl;
	os << "    "+name << std::endl;
}
void AllTextures::Parse_Header(std::istream &is, std::string &line) {
	if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(line);
	}else if (line == "FolderPath:") {
		Tim::String::get_line(is, folder_path, true, true);
	}
}
void AllTextures::Parse_textureDir(std::istream &is){
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		AllTextures* dir=new AllTextures(scriptPath,folder_path);
		push_dir(dir);
	}
}
void AllTextures::Parse_textureMap(std::istream &is) {
	std::string line;
	std::string scriptPath;
	Tim::String::get_line(is, line, true, true);
	if (line == "ScriptPath:") {
		Tim::String::get_line(is, line, true, true);
		scriptPath = std::string(line);
		TextureMap* map=new TextureMap(scriptPath,folder_path);
		push_map(map);
	}
}
}
