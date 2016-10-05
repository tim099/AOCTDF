#include "class/display/texture/texture2D/Texture2D.h"

#include "class/display/texture/image/Image.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/buffer/Buffer.h"
#include "class/tim/math/Math.h"
#include "class/display/uniform/Uniform.h"
#include "class/tim/file/File.h"
#include "class/display/window/ViewPort.h"
#include "class/tim/string/String.h"
#include <iostream>
namespace Display{
Texture2D::Texture2D(){

}
Texture2D::Texture2D(unsigned char *pixels,glm::ivec2 _size,GLint _internalformat,
		GLenum _format,GLenum _type,int Parameteri){
	init(pixels,_size,_internalformat,_format,_type,Parameteri);
}
Texture2D::Texture2D(Image<unsigned char>* image,GLint _internalformat,
		GLenum _type,int Parameteri){
	init(image->data,image->size,_internalformat,image->format,_type,Parameteri);
}
Texture2D::Texture2D(std::string imagepath,int Parameteri){
	load(imagepath,Parameteri);
}
Texture2D::~Texture2D() {

}
void Texture2D::load(std::istream &is,std::string folder_path){
	std::string line;
	Tim::String::get_line(is, line, true, true);
	if (line == "TextureName:") {
		Tim::String::get_line(is,line, true, true);
		name = Tim::String::cut(line, std::string("\""));
	} else {
		std::cerr << "Load_texture no Texture Name!!" << line << std::endl;
		return;
	}
	Tim::String::get_line(is, line, true, true);
	if (line == "TexturePath:") {
		Tim::String::get_line(is, line, true, true);
		path = line;
	} else {
		std::cerr << "Load_texture no TexturePath!!" << line << std::endl;
		return;
	}
	load(folder_path + path);
}
void Texture2D::load(std::string imagepath,int Parameteri){
	std::string type=Tim::File::get_type(imagepath);
	Image<unsigned char>* image=new Image<unsigned char>();
	image->loadImage(imagepath.c_str());
	if (type == "bmp" || type == "BMP") {
		init(image->data,image->size,GL_RGB,image->format,GL_UNSIGNED_BYTE,Parameteri);
	} else if (type == "png" || type == "PNG") {
		init(image->data,image->size,GL_RGBA,image->format,GL_UNSIGNED_BYTE,Parameteri);
	} else {
		std::cerr << "Texture2D::Texture2D unsupport image type:" << type << std::endl;
	}
	delete image;
}
void Texture2D::init(unsigned char *pixels,glm::ivec2 _size,GLint _internalformat,
		GLenum _format,GLenum _type,int Parameteri){
	glGenTextures(1,&TexID);
	glBindTexture(GL_TEXTURE_2D,TexID);
	size=_size;
	Texture::init(TexID,GL_TEXTURE_2D,_type,_format,_internalformat);

	glTexImage2D(GL_TEXTURE_2D,0,internalformat,size.x,size.y,0,format,type,pixels);
	TexFilterParameteri(GL_TEXTURE_2D,Parameteri);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);//GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
}
int Texture2D::get_texture_type(){
	return Shader::Type_Texture;
}
Texture2D* Texture2D::Tex2D(){
	return this;
}
int Texture2D::get_layer()const{
	return 0;
}
double Texture2D::get_aspect(){
	return Tim::Math::aspect(size);
}
void Texture2D::draw(Shader2D* shader2D,DrawData *data){
	DrawData2D *dat=(DrawData2D*)data;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	float targetaspect=ViewPort::get_cur_viewport_aspect();

    glm::vec2 tsize;
    float aspect=Tim::Math::aspect(size)/targetaspect;
    tsize=Tim::Math::get_size(dat->width,aspect);
    if(!dat->height==DrawData2D::AutoHeight){
    	tsize.y*=dat->height;
    }

	GLuint tex_vt=gen_texture_vertex(tsize),tex_uv=gen_texture_uv();

	Buffer::bind_vtbuffer(tex_vt);
	Buffer::bind_uvbuffer(tex_uv);

	sent_uniform(shader2D,0,"Texture");
	shader2D->sent_Uniform("TextureArr",1);
	//sent_uniform(shader2D,1,"TextureArr");

	math::vec2<float> pos=(dat->pos)*2.0f+
			math::vec2<float>(tsize.x,-tsize.y)-
			math::vec2<float>(1.0,1.0);
	shader2D->sent_Uniform("position",pos);
	shader2D->sent_Uniform("alpha",dat->alpha);
	//shader2D->sent_Uniform("tex_layer",dat->layer);
	//shader2D->set_texture_type(Display::Type_Texture);
	glDrawArrays(GL_TRIANGLES,0,2*3);


    glDeleteBuffers(1,&tex_vt);
    glDeleteBuffers(1,&tex_uv);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}
Image<unsigned char>* Texture2D::convert_to_image(GLenum _format){
	glBindTexture(GL_TEXTURE_2D,TexID);
	Image<unsigned char> *img=new Image<unsigned char>(size,_format);
	glGetTexImage(GL_TEXTURE_2D,0,_format,type,img->data);
	return img;
}
}
