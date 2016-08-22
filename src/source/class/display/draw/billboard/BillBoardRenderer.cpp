#include "class/display/draw/billboard/BillBoardRenderer.h"
#include "class/display/texture/Texture.h"
#include "class/display/shader/Shader.h"

namespace Display {

BillBoardRenderer::BillBoardRenderer() {

}
BillBoardRenderer::~BillBoardRenderer() {
	clear_temp_drawdata();
}
void BillBoardRenderer::clear_temp_drawdata(){
    for(unsigned i=0;i<billboards.size();i++){
    	delete billboards.at(i);
    }
    billboards.clear();
}
void BillBoardRenderer::push(BillBoard* billboard){
	billboards.push_back(billboard);
}
void BillBoardRenderer::draw(Shader *shader,Camera *camera){
	if(billboards.empty())return;
	GLuint tex_vt=Texture::gen_texture_vertex(glm::vec2(1,1));
	GLuint tex_uv=Texture::gen_texture_uv();
	Buffer::bind_vtbuffer(tex_vt);
	Buffer::bind_uvbuffer(tex_uv);
	Buffer::bind_vnbuffer(tex_vt);

	Buffer::unbind_lybuffer();
	shader->Disable(Shader::LayerTexture);
	shader->Enable(Shader::BillBoard);

	glm::vec3 l,r,u;
	camera->gen_bill_board_lru(l,r,u);

	for(unsigned i=0;i<billboards.size();i++){
		//std::cout<<"BillBoardRenderer::draw"<<std::endl;
		billboards.at(i)->sent_uniform(shader,l,r,u);
		glDrawArrays(GL_TRIANGLES,0,2*3);
	}
	shader->Disable(Shader::BillBoard);

    glDeleteBuffers(1,&tex_vt);
    glDeleteBuffers(1,&tex_uv);
	//model_buffer->unbind_buffer(shader);
}
} /* namespace Display */
