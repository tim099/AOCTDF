#include "class/display/texture/Texture.h"
#include "class/tim/string/String.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/model/Vertex.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
#include <GL/glfw3.h>
namespace Display{
Texture::Texture(GLuint _TexID,GLenum _target,GLenum _type,GLenum _format,GLint _internalformat) {
	init(_TexID,_target,_type,_format,_internalformat);
}
void Texture::init(GLuint _TexID,GLenum _target,GLenum _type,GLenum _format,GLint _internalformat){
	TexID=_TexID;
	target=_target;
	type=_type;
	format=_format;
	internalformat=_internalformat;
}
Texture::Texture() {
	TexID=0;
	target=0;
	type=0;
	format=0;
	internalformat=0;
}
Texture::~Texture() {
	//std::cout<<"texture delete"<<std::endl;
	glDeleteTextures(1,&TexID);
}
Texture2D* Texture::Tex2D(){
	return 0;
}
void Texture::bind_texture(){
	glBindTexture(target,TexID);
}
void Texture::sent_uniform(Shader* shader,int num,const char *name){
	glActiveTexture(GL_TEXTURE0+num);
	glBindTexture(target,TexID);

	shader->sent_Uniform(name,num);//texturebuffer
	shader->set_texture_type(get_texture_type());
}
void Texture::TexFilterParameteri(GLenum target,int Parameteri){
	switch(Parameteri){
		case P_NONE:
			break;
		case P_MipMap:
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(target,GL_TEXTURE_BASE_LEVEL,0);
			glTexParameteri(target,GL_TEXTURE_MAX_LEVEL,20);
			glGenerateMipmapEXT(target);
			break;
		case P_Linear:
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR);//GL_NEAREST
			glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_LINEAR);//GL_NEAREST
			break;
		case P_Nearest:
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			break;
		default:
			std::cout<<"err unknow texture Parameteri type:"<<Parameteri<<std::endl;

	}
}
void Texture::sent_textureVec(Shader* shader,std::vector<Texture*>& texvec,int num,const char *name){
	char temp[100];
	for(unsigned i=0;i<texvec.size();i++){
		//Tim::String::gen_array_num(temp+slen,i);
		sprintf(temp,"%s[%d]",name,i);
		texvec.at(i)->sent_uniform(shader,i+num,temp);
	}
}
GLuint Texture::gen_texture_vertex(glm::vec2 size){
	GLfloat vertex_buffer_data[18];
	Vertex::gen_quad_vt(vertex_buffer_data,glm::vec3(0,0,0),glm::vec3(size.x,size.y,0),true);
	return Buffer::gen_buffer(vertex_buffer_data,sizeof(vertex_buffer_data));
}
GLuint Texture::gen_texture_uv(){
	GLfloat uv_buffer_data[12];
	Vertex::gen_quad_uv(uv_buffer_data);
	return Buffer::gen_buffer(uv_buffer_data,sizeof(uv_buffer_data));
}
int Texture::get_layer()const{
	return 0;
}
void Texture::draw_texture(Shader2D* shader2D,DrawData *data){
	shader2D->active_shader();
	shader2D->set_format(format);

	data->prepare_to_draw(shader2D);
	draw(shader2D,data);
	data->draw_end(shader2D);

	delete data;//remember to delete this!!
}
void Texture::draw(Shader2D* shader2D,DrawData *data){
	std::cerr<<"error not implement draw texture in this class"<<std::endl;
}
double Texture::get_aspect(){
	std::cerr<<"error not implement get_aspect() in this class"<<std::endl;
	return 1.0;
}
}
