#include "class/display/draw/billboard/BillBoard.h"
#include "class/display/shader/Shader.h"

#include "class/display/texture/AllTextures.h"
#include <glm/gtx/vector_angle.hpp>
#include <iostream>
namespace Display {

BillBoard::BillBoard(std::string _texture,math::vec3<double> _pos,math::vec2<double> _size) {
	texture=_texture;
	pos=_pos;
	size=_size;
}
BillBoard::~BillBoard() {

}
void BillBoard::sent_uniform(Shader *shader,glm::vec3 l,glm::vec3 r,glm::vec3 u){
	Texture* tex=AllTextures::get_cur_tex(texture);
	tex->sent_uniform(shader,0,"Texture");
	shader->sent_Uniform("TextureArr",2);

	glm::mat4 m=glm::mat4
			(r.x,r.y,r.z,0,
			 u.x,u.y,u.z,0,
			 l.x,l.y,l.z,0,
			 pos.x,pos.y,pos.z,1
			);
	m*=glm::scale(glm::vec3(size.x,size.y,1.0));
	glUniformMatrix4fv(glGetUniformLocation(shader->programID,"M"),1,GL_FALSE,
				&(m[0][0]));
}


} /* namespace Display */
