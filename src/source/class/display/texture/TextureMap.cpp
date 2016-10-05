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
TextureMap::TextureMap(std::string script_path) {
	if (script_path != std::string("NULL")) {
		Load_script(script_path);
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
		set_name(std::string(line));
	}
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
