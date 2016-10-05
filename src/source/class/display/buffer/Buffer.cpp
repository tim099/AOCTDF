#include "class/display/buffer/Buffer.h"
#include <glm/glm.hpp>
#include <iostream>
namespace Display{
Buffer::Buffer(GLfloat* data,int datasize,GLuint _index,GLint _size,GLenum _type,GLboolean _normalized
		,GLsizei _stride) {
	buffer=gen_buffer(data,datasize);
	index=_index;
	size=_size;
	type=_type;
	normalized=_normalized;
	stride=_stride;
}
Buffer::~Buffer() {
	glDeleteBuffers(1,&buffer);
}
GLuint Buffer::gen_buffer(GLfloat* data,int datasize){
	GLuint buffer;
	glGenBuffers(1,&buffer);
	glBindBuffer(GL_ARRAY_BUFFER,buffer);
	glBufferData(GL_ARRAY_BUFFER,datasize,data,GL_STATIC_DRAW);

	return buffer;
}
void Buffer::update_buffer(GLfloat* data,int datasize){
	glBindBuffer(GL_ARRAY_BUFFER,buffer);
	glBufferData(GL_ARRAY_BUFFER,datasize,data,GL_STATIC_DRAW);
}
GLuint Buffer::GenVertexArray(){
    GLuint VertexArrayID;
    glGenVertexArrays(1,&VertexArrayID);
    glBindVertexArray(VertexArrayID);
    return VertexArrayID;
}
void Buffer::bind_buffer(){
	glBindBuffer(GL_ARRAY_BUFFER,buffer);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index,size,type,normalized,stride,NULL);
}
void Buffer::unbind_buffer(){
	glDisableVertexAttribArray(index);
}
void Buffer::unbind_vtbuffer(){
	glDisableVertexAttribArray(vt);//vertexbuffer
}
void Buffer::unbind_uvbuffer(){
	glDisableVertexAttribArray(uv);//uv
}
void Buffer::unbind_vnbuffer(){
	glDisableVertexAttribArray(vn);//vn
}
void Buffer::unbind_lybuffer(){
	glDisableVertexAttribArray(ly);//ly
}
void Buffer::unbind_buffer(int type){
	glDisableVertexAttribArray(type);
}
void Buffer::unbind_buffer_mat4(int index){
	for (int i=0;i<4;i++){
		glDisableVertexAttribArray(index+i);
	    glVertexAttribDivisor(index+i,0);
	}
}
void Buffer::bind_vtbuffer(GLuint vertexbuffer){
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glEnableVertexAttribArray(vt);
	glVertexAttribPointer(vt,3,GL_FLOAT,GL_FALSE,0,NULL);
}
void Buffer::bind_uvbuffer(GLuint uvbuffer){
	glBindBuffer(GL_ARRAY_BUFFER,uvbuffer);
	glEnableVertexAttribArray(uv);
	glVertexAttribPointer(uv,2,GL_FLOAT,GL_FALSE,0,NULL);//vernum,v_num,type
}
void Buffer::bind_vnbuffer(GLuint vnbuffer){
	glBindBuffer(GL_ARRAY_BUFFER,vnbuffer);
	glEnableVertexAttribArray(vn);
	glVertexAttribPointer(vn,3,GL_FLOAT,GL_FALSE,0,NULL);
}
void Buffer::bind_buffer(int index,int size,GLuint buffer){
	glBindBuffer(GL_ARRAY_BUFFER,buffer);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index,size,GL_FLOAT,GL_FALSE,0,NULL);//vernum,v_num,type
}
void Buffer::bind_buffer_mat4(int index,int size,GLuint buffer){
	glBindBuffer(GL_ARRAY_BUFFER,buffer);
	for (int i=0;i<4;i++){
	    glVertexAttribPointer(index+i,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void *)(sizeof(glm::vec4)*i));
	    glEnableVertexAttribArray(index+i);
	    glVertexAttribDivisor(index+i,1);
	}
}
void Buffer::disable_all_buffer(){
	glDisableVertexAttribArray(0);//vertexbuffer
	glDisableVertexAttribArray(1);//uv
	glDisableVertexAttribArray(2);//vn
	glBindBuffer(GL_ARRAY_BUFFER,0);//unbind buffer
}
}
