#include "class/display/texture/TextureMap.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/texture/texture3D/Texture2DArr/Texture2DArr.h"
#include "class/display/texture/texture3D/cubemap/TextureCubeMap.h"
#include "class/tim/file/File.h"
#include "class/tim/string/String.h"
#include "class/display/texture/TextureCreator.h"

#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
namespace Display{
TextureMap::TextureMap(std::string _path,std::string folder_path) {
	if (_path != std::string("NULL")) {
		path=_path;
		Load_script(folder_path+path);
	}
}
TextureMap::~TextureMap() {

}
std::string TextureMap::get_name() const {
	return name;
}
void TextureMap::set_name(std::string _name) {
	name = _name;
}
void TextureMap::push(std::string tex_name, Texture* tex) {
	textures.push(tex_name,tex);
}
Texture* TextureMap::get(std::string tex_name) {
	return textures.get(tex_name);
}
void TextureMap::Parse_Header(std::istream &is, std::string &line) {
	if (line == "FolderPath:") {
		Tim::String::get_line(is, line, true, true);
		folder_path = std::string(line);
	} else if (line == "Name:") {
		Tim::String::get_line(is, line, true, true);
		set_name(line);
	}
}
void TextureMap::Parse_Header(std::ostream &os){
	os << "FolderPath:" << std::endl;
	os << "    "+folder_path << std::endl;
	os << "Name:" << std::endl;
	os << "    "+name << std::endl;
}
void TextureMap::Parse_Script(std::ostream &os){
	std::map<std::string,Texture*>*all_maps=textures.get_map();
	typename std::map<std::string,Texture*>::iterator it = all_maps->begin();
	Texture* tex;
	while (it != all_maps->end()) {
		tex=it->second;
		os<<tex->get_type()+":"<<std::endl;
		tex->save(os);
		it++;
	}
}
void TextureMap::load_folder_to_tex2D(std::string path){
	std::vector<std::string> names=Tim::File::get_all_files(path);
	for(unsigned i=0;i<names.size();i++){
		Texture2D* tex=new Texture2D();
		tex->load(path+names.at(i));
		tex->name=names.at(i);
		push(tex->name,tex);
	}
}
int TextureMap::load_folder_to_tex2DArr(std::string path,std::string name,unsigned sx,unsigned sy){
	std::vector<std::string> names=Tim::File::get_all_files(path);
	std::string new_path;
	for(unsigned i=0;i<names.size();i++){
		new_path=path+names.at(i);
		names.at(i)=new_path;
	}
	Texture2DArr* tex=new Texture2DArr();
	tex->load(names,glm::ivec3(sx,sy,names.size()));
	tex->name=name;
	push(tex->name,tex);
	return names.size();
}
void TextureMap::Parse_Script(std::istream &is, std::string &line) {
	if (line=="Texture:"||line=="Texture2DArr:"||line=="TextureCubeMap:") {
		line=line.substr(0,line.length()-1);
		Texture* tex=TextureCreator::get_cur_object()->create(line);
		tex->load(is,folder_path);
		push(tex->name,tex);
	}
}
}
