#include "class/display/draw/particle/Particle.h"
#include "class/display/shader/Shader.h"
#include "class/display/texture/AllTextures.h"
#include <cstdlib>
#include <glm/gtx/vector_angle.hpp>
namespace Display {

Particle::Particle(std::string _texture,math::vec3<double> _pos,math::vec2<double> _size,int _timer) {
	texture=_texture;
	pos=_pos;
	size=_size;
	timer=_timer;
	vn_buffer=0;
	create_timer=0;
}
Particle::~Particle() {
	for(unsigned i=0;i<particles.size();i++){
		delete particles.at(i);
	}
}
bool Particle::end(){
	if(timer<=0)return true;
	return false;
}
void Particle::update(){
	timer--;
	particles_update();
}
void Particle::particles_update(){
	create_timer++;
	if(create_timer>3){
		create_timer=0;
		for(int i=0;i<3;i++){
			double rx=0.01*(rand()%201-100);
			double ry=0.01*(rand()%201-100);
			double rz=0.01*(rand()%201-100);
			math::vec3<double> v(rx,ry,rz);
			v.normalize();
			particles.push_back(new particle(pos,v*0.5,10));
		}


	}
	particle* p;
	for(unsigned i=0;i<particles.size();){
		p=particles.at(i);
		p->life--;
		p->pos+=p->vel;
		p->vel*=0.9;
		if(p->life<=0){
			delete particles.at(i);
			particles.at(i)=particles.back();
			particles.pop_back();
		}else{
			i++;
		}
	}
}
void Particle::sent_uniform(Shader *shader,glm::vec3 l,glm::vec3 r,glm::vec3 u){
	Texture* tex=AllTextures::get_cur_tex(texture);
	tex->sent_uniform(shader,0,"Texture");
	shader->sent_Uniform("TextureArr",2);
	if(tex->format==GL_RGBA){
		shader->Enable(Shader::AlphaTexture);
		glEnable(GL_BLEND);
	}else{
		shader->Disable(Shader::AlphaTexture);
		glDisable(GL_BLEND);
	}
	glm::mat4 m=glm::mat4
			(r.x,r.y,r.z,0,
			 u.x,u.y,u.z,0,
			 l.x,l.y,l.z,0,
			 0,0,0,1
			);
	m*=glm::scale(glm::vec3(size.x,size.y,1.0));

	int data_len=3*particles.size();
	GLfloat *data=new GLfloat[data_len];
	particle* p;
	for(unsigned i=0;i<particles.size();i++){
		p=particles.at(i);
		data[3*i]=p->pos.x;data[3*i+1]=p->pos.y;data[3*i+2]=p->pos.z;
	}
	vn_buffer=Buffer::gen_buffer(data,sizeof(GLfloat)*data_len);
	delete data;

	Buffer::bind_vnbuffer(vn_buffer);

	glUniformMatrix4fv(glGetUniformLocation(shader->programID,"M"),1,GL_FALSE,&(m[0][0]));
}
void Particle::draw(Shader *shader,glm::vec3 l,glm::vec3 r,glm::vec3 u,Camera *camera){
	if(particles.size()>0){
		sent_uniform(shader,l,r,u);

		glVertexAttribDivisor(2,1);
		glDrawArraysInstanced(GL_TRIANGLES,0,2*3,particles.size());
		glVertexAttribDivisor(2,0);

		glDeleteBuffers(1,&vn_buffer);
	}

}
} /* namespace Display */
