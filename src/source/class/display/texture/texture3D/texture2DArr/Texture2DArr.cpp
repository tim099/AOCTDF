#include "class/display/texture/texture3D/Texture2DArr/Texture2DArr.h"

#include "class/display/texture/image/Image.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/window/ViewPort.h"
#include "class/tim/string/String.h"
#include <iostream>
namespace Display{
Texture2DArr::Texture2DArr(){

}
Texture2DArr::Texture2DArr(glm::ivec3 _size,GLint _internalformat,GLenum _format,
		GLenum _type,int _Parameteri){
	init(_size,_internalformat,_format,_type,_Parameteri);
}
Texture2DArr::Texture2DArr(std::vector<std::string>&path,glm::ivec3 size,GLint internalformat,
		GLenum format,GLenum type,int Parameteri){
	load(path,size,internalformat,format,type,Parameteri);
}
Texture2DArr::~Texture2DArr() {

}
void Texture2DArr::save(std::ostream &os){
	os << "	TextureName:" << std::endl;
	os << "		"+name<< std::endl;
	os << "	TextureSize:" << std::endl;
	os << "		"<<size.x<< std::endl;
	os << "		"<<size.y<< std::endl;
	for(unsigned i=0;i<paths.size();i++){
		os << "	TexturePath:" << std::endl;
		os << "		"+paths.at(i) << std::endl;
	}
	os << "#Load_texture2DArr_END"<< std::endl;
}
void Texture2DArr::load(std::istream &is,std::string folder_path){
	std::string line;
	Tim::String::get_line(is, line, true, true);
	glm::ivec2 size;
	if (line == "TextureName:") {
		Tim::String::get_line(is, name, true, true);
	} else {
		std::cerr << "Load_texture2DArr no Texture Name!!" << line << std::endl;
		return;
	}

	Tim::String::get_line(is, line, true, true);
	if (line == "TextureSize:") {
		is >> size.x;
		is >> size.y;
	} else {
		std::cerr << "Load_texture2DArr no TextureSize:!!" << line << std::endl;
	}
	Tim::String::get_line(is, line, true, true);
	std::vector<std::string> tex_paths;
	while(Tim::String::get_line(is, line, true, true)&&line!="#Load_texture2DArr_END"){
		if (line == "TexturePath:") {
			Tim::String::get_line(is, path, true, true);
			tex_paths.push_back(folder_path + path);
			paths.push_back(path);
		}
	}
	load(tex_paths,glm::ivec3(size.x, size.y, paths.size()),GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, P_MipMap);
}
void Texture2DArr::load(std::vector<std::string>&path,glm::ivec3 size,GLint internalformat,
		GLenum format,GLenum type,int Parameteri){
	init(size,internalformat,format,type,P_NONE);
	for(unsigned i=0;i<path.size();i++){
		Image<unsigned char>::load_sub_image3D(path.at(i).c_str(),target,i,type);
	}
	TexFilterParameteri(GL_TEXTURE_2D_ARRAY,Parameteri);
}
void Texture2DArr::init(glm::ivec3 _size,GLint _internalformat,GLenum _format,
		GLenum _type,int Parameteri){
	glGenTextures(1,&TexID);
	glBindTexture(GL_TEXTURE_2D_ARRAY,TexID);
	Texture::init(TexID,GL_TEXTURE_2D_ARRAY,_type,_format,_internalformat);
	size=_size;

	glTexImage3D(GL_TEXTURE_2D_ARRAY,0,internalformat,size.x,size.y,size.z,0,format,type,NULL);//0=level,0=border
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	TexFilterParameteri(GL_TEXTURE_2D_ARRAY,Parameteri);
}
int Texture2DArr::get_layer()const{
	return size.z;
}
int Texture2DArr::get_texture_type(){
	return Shader::Type_TextureArr;
}
void Texture2DArr::draw(Shader2D* shader2D,DrawData *data){
	DrawData2D *dat=(DrawData2D*)data;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	float targetaspect=ViewPort::get_cur_viewport_aspect();

    glm::vec2 tsize;
    float aspect=Tim::Math::aspect(glm::ivec2(size.x,size.y))/targetaspect;
    tsize=Tim::Math::get_size(dat->width,aspect);
    if(!dat->height==DrawData2D::AutoHeight){
    	tsize.y*=dat->height;
    }

	GLuint tex_vt=gen_texture_vertex(tsize),tex_uv=gen_texture_uv();

	Buffer::bind_vtbuffer(tex_vt);
	Buffer::bind_uvbuffer(tex_uv);

	shader2D->sent_Uniform("Texture",0);
	sent_uniform(shader2D,1,"TextureArr");
	math::vec2<float> pos=(dat->pos)*2.0f+
			math::vec2<float>(tsize.x,-tsize.y)-
			math::vec2<float>(1.0,1.0);
	shader2D->sent_Uniform("position",pos);
	shader2D->sent_Uniform("alpha",dat->alpha);
	shader2D->sent_Uniform("tex_layer",dat->layer);
	//shader2D->set_type(Display::Type_TextureArr);
	glDrawArrays(GL_TRIANGLES,0,2*3);


    glDeleteBuffers(1,&tex_vt);
    glDeleteBuffers(1,&tex_uv);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}
}
