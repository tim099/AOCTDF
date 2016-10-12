#include "class/display/model/modelBuffer/ModelBuffer.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/model/Model.h"
#include "class/display/texture/Texture.h"
#include "class/display/shader/Shader.h"
#include "class/tim/string/String.h"
#include <iostream>
namespace Display{
ModelBuffer::ModelBuffer(){
	vtbuffer = 0;
	uvbuffer = 0;
	vnbuffer = 0;
	lybuffer = 0;
	size=0;
	vertex_num=0;
	Align_center=true;
}
ModelBuffer::ModelBuffer(Model *m) {
	initialize(m);
}
void ModelBuffer::initialize(std::string path, float _size,bool align_center){

	Model*m = Model::load_obj(path.c_str(), _size, align_center);
	initialize(m);
	delete m;
}
void ModelBuffer::initialize(Model *m) {
	vtbuffer = 0;
	uvbuffer = 0;
	vnbuffer = 0;
	lybuffer = 0;
	load_model(m);
}
ModelBuffer::~ModelBuffer() {
	delete vtbuffer;
	delete uvbuffer;
	delete vnbuffer;
	if (lybuffer)
		delete lybuffer;
	//std::cout << "delete model buffer" << std::endl;
}
void ModelBuffer::save(std::ostream &os){
	os << "	Name:" << std::endl;
	os << "		"+name<< std::endl;
	os << "	Path:" << std::endl;
	os << "		"+path<< std::endl;
	os << "	Size:" << std::endl;
	os << "		"<<size<< std::endl;
	os << "	Align_center:" << std::endl;
	if(Align_center){
		os << "		true"<< std::endl;
	}else{
		os << "		false"<< std::endl;
	}
	os<<"#load_end"<<std::endl;
}
void ModelBuffer::load(std::istream &is,std::string folder_path){
	std::string line;
	while(Tim::String::get_line(is, line, true, true)){
		if(line=="#load_end"){
			initialize(folder_path+path,size,Align_center);
			break;
		}else if(line=="Name:"){
			Tim::String::get_line(is, name, true, true);
		}else if(line=="Path:"){
			Tim::String::get_line(is, path, true, true);
		}else if(line=="Size:"){
			is>>size;
		}else if(line=="Align_center:"){
			Tim::String::get_line(is, line, true, true);
			if(line=="false"){
				Align_center=false;
			}else if(line=="true"){
				Align_center=true;
			}
		}
	}
}
void ModelBuffer::load_model(Model *m) {
	if (!vtbuffer) {
		vtbuffer = new Buffer(m->vtBuffer, m->vtdatasize(), 0, 3, GL_FLOAT);
	} else {
		vtbuffer->update_buffer(m->vtBuffer, m->vtdatasize());
	}
	if (!uvbuffer) {
		uvbuffer = new Buffer(m->uvBuffer, m->uvdatasize(), 1, 2, GL_FLOAT);
	} else {
		uvbuffer->update_buffer(m->uvBuffer, m->uvdatasize());
	}
	if (!vnbuffer) {
		vnbuffer = new Buffer(m->vnBuffer, m->vndatasize(), 2, 3, GL_FLOAT);
	} else {
		vnbuffer->update_buffer(m->vnBuffer, m->vndatasize());
	}

	if (m->lyBuffer) {
		if (!lybuffer) {
			lybuffer = new Buffer(m->lyBuffer, m->lydatasize(), 3, 1, GL_FLOAT);
		} else {
			lybuffer->update_buffer(m->lyBuffer, m->lydatasize());
		}
	} else {
		if (!lybuffer) {
			lybuffer = 0;
		} else {
			delete lybuffer;
			lybuffer = 0;
		}
	}
	vertex_num = m->vtlen();
}
void ModelBuffer::bind_buffer(Shader *shader) {
	vtbuffer->bind_buffer();
	uvbuffer->bind_buffer();
	vnbuffer->bind_buffer();

	if (lybuffer) {
		lybuffer->bind_buffer();
		shader->Enable(Shader::LayerTexture); //enable lybuffer
	} else {
		Buffer::unbind_lybuffer();
		shader->Disable(Shader::LayerTexture); //disable lybuffer
	}
}
void ModelBuffer::unbind_buffer(Shader *shader) {
	if (lybuffer)
		lybuffer->unbind_buffer();
	//vtbuffer->unbind_buffer();
	//uvbuffer->unbind_buffer();
	//vnbuffer->unbind_buffer();
}
void ModelBuffer::draw(GLuint programID, GLenum mode) {
	//std::cout<<"ModelBuffer::draw="<<vertex_num<<std::endl;
	glDrawArrays(mode, 0, vertex_num);
	//std::cout<<"ModelBuffer::draw end"<<std::endl;
	//glDrawArrays(GL_LINES,0,vertex_num);
	//glDrawArrays(GL_POINTS,0,vertex_num);
}
void ModelBuffer::draw_instanced(GLuint programID,int num,GLenum mode){
	glDrawArraysInstanced(mode,0,vertex_num,num);
}
}
