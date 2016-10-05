#include "class/display/draw/particle/Particle.h"
#include "class/display/shader/Shader.h"
#include "class/display/texture/AllTextures.h"
#include "class/display/model/Vertex.h"
#include <cstdlib>
#include <algorithm>
#include <glm/gtx/vector_angle.hpp>
namespace Display {

Particle::Particle(std::string _texture,math::vec3<double> _pos,math::vec2<double> _size,int _timer) {
	texture=_texture;
	pos=_pos;
	size=_size;
	timer=_timer;
	create_timer=0;
	atlas=false;
	x_seg=0,y_seg=0;play_speed=0;
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

	particle* p;
	for(unsigned i=0;i<particles.size();){
		p=particles.at(i);
		p->life--;
		p->pos+=p->vel;
		p->vel*=0.9;
		p->tex+=play_speed;
		if(p->life<=0){
			delete particles.at(i);
			particles.at(i)=particles.back();
			particles.pop_back();
		}else{
			i++;
		}
	}
	if(create_timer>0){
		create_timer=0;
		for(int i=0;i<8;i++){
			double rx=0.01*(rand()%201-100);
			double ry=0.01*(rand()%201-100);
			double rz=0.01*(rand()%201-100);
			math::vec3<double> v(rx,ry,rz);
			v.normalize();
			particle *p=new particle(pos,v*0.1*size.x,63);
			p->tex=i;
			particles.push_back(p);
		}
	}
}
void Particle::sent_uniform(Shader *shader,glm::vec3 l,glm::vec3 r,glm::vec3 u){

}
void Particle::draw(Shader *shader,glm::vec3 l,glm::vec3 r,glm::vec3 u,Camera *camera){
	if(particles.size()>0){
		for(unsigned i=0;i<particles.size();i++){
			particles.at(i)->gen_cam_dis(camera);
		}
		std::sort(particles.begin(),particles.end(),particleCmp());


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
				 0,0,0,1);
		m*=glm::scale(glm::vec3(size.x,size.y,1.0));
		glUniformMatrix4fv(glGetUniformLocation(shader->programID,"M"),1,GL_FALSE,&(m[0][0]));


		GLfloat *vndata=new GLfloat[3*particles.size()];
		particle* p;
		for(unsigned i=0;i<particles.size();i++){
			p=particles.at(i);
			vndata[3*i]=p->pos.x;vndata[3*i+1]=p->pos.y;vndata[3*i+2]=p->pos.z;
		}
		GLuint vn_buffer=Buffer::gen_buffer(vndata,sizeof(GLfloat)*(3*particles.size()));
		delete vndata;
		Buffer::bind_vnbuffer(vn_buffer);

		GLuint ly_buffer;
		if(atlas){
			shader->Enable(Shader::Atlas);
			shader->sent_Uniform("atlas_sx",x_seg);
			shader->sent_Uniform("atlas_sy",y_seg);
			GLfloat *lydata=new GLfloat[particles.size()];
			for(unsigned i=0;i<particles.size();i++){
				p=particles.at(i);
				lydata[i]=p->tex;
			}
			ly_buffer=Buffer::gen_buffer(lydata,sizeof(GLfloat)*(particles.size()));
			Buffer::bind_buffer(Buffer::ly,1,ly_buffer);
			delete lydata;

			glVertexAttribDivisor(Buffer::ly,1);
		}

		glVertexAttribDivisor(Buffer::vn,1);
		glDrawArraysInstanced(GL_TRIANGLES,0,2*3,particles.size());
		glVertexAttribDivisor(Buffer::vn,0);

		glDeleteBuffers(1,&vn_buffer);
		if(atlas){
			Buffer::unbind_buffer(Buffer::ly);
			glVertexAttribDivisor(Buffer::ly,0);
			glDeleteBuffers(1,&ly_buffer);
			shader->Disable(Shader::Atlas);
		}
	}

}
} /* namespace Display */
