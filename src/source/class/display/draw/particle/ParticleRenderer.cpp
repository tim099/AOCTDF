#include "class/display/draw/particle/ParticleRenderer.h"
#include "class/display/draw/billboard/BillBoardRenderer.h"
#include "class/display/texture/Texture.h"
#include "class/display/shader/Shader.h"
#include "class/display/buffer/Buffer.h"
namespace Display {

ParticleRenderer::ParticleRenderer() {

}
ParticleRenderer::~ParticleRenderer() {
    for(unsigned i=0;i<particles.size();i++){
    	delete particles.at(i);
    }
}
void ParticleRenderer::update(){
	for(unsigned i=0;i<particles.size();i++){
		particles.at(i)->update();
	}
}
void ParticleRenderer::clear_temp_drawdata(){
	for(unsigned i=0;i<particles.size();){
		if(particles.at(i)->end()){
			delete particles.at(i);
			particles.at(i)=particles.back();
			particles.pop_back();
		}else{
			i++;
		}
	}
}
void ParticleRenderer::draw(Shader *shader,Camera *camera){
	if(particles.empty())return;
	GLuint tex_vt=Texture::gen_texture_vertex(glm::vec2(1,1));
	GLuint tex_uv=Texture::gen_texture_uv();
	Buffer::bind_vtbuffer(tex_vt);
	Buffer::bind_uvbuffer(tex_uv);
	Buffer::bind_vnbuffer(tex_vt);

	Buffer::unbind_lybuffer();

	shader->Enable(Shader::BillBoard);
	shader->Enable(Shader::Particle);
	glm::vec3 l,r,u;
	camera->gen_bill_board_lru(l,r,u);

	for(unsigned i=0;i<particles.size();i++){
		particles.at(i)->draw(shader,l,r,u,camera);
	}
	shader->Disable(Shader::BillBoard);
	shader->Disable(Shader::Particle);
	shader->Disable(Shader::AlphaTexture);
	glDisable(GL_BLEND);
    glDeleteBuffers(1,&tex_vt);
    glDeleteBuffers(1,&tex_uv);
}
} /* namespace Display */
