#include "class/display/texture/texture3D/cubemap/TextureCubeMap.h"

#include "class/tim/string/String.h"
namespace Display{
TextureCubeMap::TextureCubeMap(){

}
TextureCubeMap::TextureCubeMap(glm::ivec2 size,GLint _internalformat,GLenum _format,
		GLenum _type,int Parameteri){
	init(size,_internalformat,_format,_type,Parameteri);
}
TextureCubeMap::TextureCubeMap(std::vector<std::string>&path,glm::ivec2 _size,GLint _internalformat,
		GLenum _format,GLenum _type,int Parameteri){
	load(path,_size,_internalformat,_format,_type,Parameteri);
}
TextureCubeMap::~TextureCubeMap() {

}
void TextureCubeMap::init(glm::ivec2 _size,GLint _internalformat,GLenum _format,
		GLenum _type,int Parameteri){
	size=_size;
	glGenTextures(1,&TexID);
	glBindTexture(GL_TEXTURE_CUBE_MAP,TexID);
	Texture::init(TexID,GL_TEXTURE_CUBE_MAP,_type,_format,_internalformat);

	glTexImage3D(GL_TEXTURE_CUBE_MAP,0,internalformat,size.x,size.y,6,0,format,type,NULL);//0=level,0=border

	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	TexFilterParameteri(GL_TEXTURE_CUBE_MAP,Parameteri);
	for (int i=0;i<6;i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,internalformat,size.x,size.y,0,format,type,0);
	}
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}
void TextureCubeMap::load(std::istream &is,std::string folder_path){
	std::string line;
	Tim::String::get_line(is, line, true, true);
	glm::ivec2 size;
	if (line == "TextureName:") {
		Tim::String::get_line(is, name, true, true);
	} else {
		std::cerr << "Load_textureCubeMap no Texture Name!!" << line
				<< std::endl;
		return;
	}
	Tim::String::get_line(is, line, true, true);
	if (line == "TextureSize:") {
		is >> size.x;
		is >> size.y;
	} else {
		std::cerr << "Load_textureCubeMap no TextureSize:!!" << line
				<< std::endl;
	}

	for (unsigned i = 0; i < 6; i++) {
		Tim::String::get_line(is, line, true, true);
		if (line == "TexturePath:") {
			Tim::String::get_line(is, line, true, true);
			path = folder_path + line;
			paths.push_back(path);
		} else {
			std::cerr << "Load_textureCubeMap no TexturePath!!" << line << ";"
					<< std::endl;
			return;
		}
	}
	load(paths,glm::ivec2(size.x, size.y),GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, P_MipMap);
}
void TextureCubeMap::load(std::vector<std::string>&path,glm::ivec2 _size,GLint _internalformat,
		GLenum _format,GLenum _type,int Parameteri){
	init(_size,_internalformat,_format,_type,Parameteri);
	for(unsigned i=0;i<6;i++){
		Image<unsigned char>::load_sub_image2D(path.at(i).c_str(),GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,
				internalformat,format,type);
	}
	TexFilterParameteri(GL_TEXTURE_CUBE_MAP,Parameteri);
}
int TextureCubeMap::get_layer()const{
	return 6;
}
}
