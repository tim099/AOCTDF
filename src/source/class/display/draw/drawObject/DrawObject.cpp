#include "class/display/draw/drawObject/DrawObject.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "class/display/buffer/Buffer.h"
#include "class/display/shader/Shader.h"
#include "class/display/texture/Texture.h"
#include "class/display/texture/AllTextures.h"
#include "class/display/model/modelBuffer/AllModelBuffers.h"
#include "class/display/draw/drawObject/drawData/drawDateEX/SkyMap.h"
#include "class/display/camera/Camera.h"
#include "class/display/model/modelBuffer/ModelBuffer.h"
#include <cstring>

#include "class/display/draw/Draw.h"
#include <iostream>
namespace Display{
DrawObject::DrawObject(std::string _obj_str, std::string _tex_str,
std::string _normalTex_str, bool _layer_texture) {
	init_drawObject(_obj_str, _tex_str, _normalTex_str, _layer_texture);
	mat = math::vec4<float>(0.3, 0.4, 0.01, 0.15); //x=diffuse,y=specular_value,z=ambient,w=emissive
}
DrawObject::DrawObject(){
	model_buffer = 0;
	texture = 0;
	NormalMap = 0;
	draw_shadow = false;
	layer_texture = 0;
	alpha_drawobject=false;
	sky_map=false;
	mat = math::vec4<float>(0.3, 0.4, 0.01, 0.15); //x=diffuse,y=specular_value,z=ambient,w=emissive
	//sky_map=false;
}
void DrawObject::init_drawObject(std::string _obj_str, std::string _tex_str,
		std::string _normalTex_str, bool _layer_texture) {
	if (_tex_str != "") {
		texture = AllTextures::get_cur_tex(_tex_str);
		if(!texture){
			std::cerr<<"DrawObject::init_drawObject texture:"<<_tex_str<<"not found"<<std::endl;
		}
	} else {
		texture = 0;
	}
	if (_normalTex_str != "") {
		NormalMap = AllTextures::get_cur_tex(_normalTex_str);
	} else {
		NormalMap = 0;
	}
	if(_obj_str!=""){
		model_buffer=AllModelBuffers::get_cur_model(_obj_str);
	}else{
		model_buffer=0;
	}
	init_drawObject(model_buffer, texture, NormalMap, _layer_texture);
}
void DrawObject::init_drawObject(ModelBuffer* _obj, Texture* _texture,
		Texture* _NormalMap, bool _layer_texture) {
	model_buffer = _obj;
	texture = _texture;
	NormalMap = _NormalMap;
	draw_shadow = true;
	layer_texture = _layer_texture;


}
DrawObject::~DrawObject() {
	//std::cout << "delete draw object" << std::endl;
	clear_temp_drawdata();
}
void DrawObject::load(std::istream &is){
	std::string line;
	while(Tim::String::get_line(is, line, true, true)){
			if(line=="#load_end"){
				init_drawObject(modelbuffer_name,texture_name,normalmap_name);
				break;
			}else if(line=="Name:"){
				Tim::String::get_line(is, name, true, true);
			}else if(line=="ModelBuffer:"){
				Tim::String::get_line(is, modelbuffer_name, true, true);
			}else if(line=="Texture:"){
				Tim::String::get_line(is, texture_name, true, true);
			}else if(line=="NormalMap:"){
				Tim::String::get_line(is, normalmap_name, true, true);
			}else if(line=="Material:"){
				is>>mat.x;
				is>>mat.y;
				is>>mat.z;
				is>>mat.w;
			}else if(line=="DrawShadow:"){
				Tim::String::get_line(is, line, true, true);
				if(line=="false"){
					draw_shadow=false;
				}else{
					draw_shadow=true;
				}
			}else if(line=="SkyMap:"){
				Tim::String::get_line(is, line, true, true);
				if(line=="true"){
					sky_map=true;
				}else{
					sky_map=false;
				}
			}
	}
}
void DrawObject::update() {

}
void DrawObject::set_obj(ModelBuffer *_obj) {
	model_buffer = _obj;
}
void DrawObject::sent_model_veiw_uniform(GLuint programID, const glm::mat4 &M) {
	glUniformMatrix4fv(glGetUniformLocation(programID, "M"), 1, GL_FALSE,
			&(M[0][0]));
}
unsigned DrawObject::temp_pos_num() const {
	return temp_datas.size();
}
void DrawObject::clear_temp_drawdata() {
	for (unsigned i = 0; i < temp_datas.size(); i++) {
		delete temp_datas.at(i);
	}
	temp_datas.clear();
}
void DrawObject::push_temp_drawdata(DrawDataObj* p) {
	temp_datas.push_back(p);
}
void DrawObject::draw_shadow_vec(Shader *shader,
		std::vector<DrawDataObj*> &data_v) {
	DrawDataObj* data;
	for (unsigned i = 0; i < data_v.size(); i++) {
		data = data_v.at(i);
		if (data->draw_shadow) {
			sent_model_veiw_uniform(shader->programID, data->pos->get_pos_mat());
			model_buffer->draw(shader->programID);
		}
	}
}
void DrawObject::draw_vec(Shader *shader, std::vector<DrawDataObj*> &data_v) {
	DrawDataObj* data;
	for (unsigned i = 0; i < data_v.size(); i++) {
		data=data_v.at(i);
		data->prepare_to_draw(shader);
		sent_model_veiw_uniform(shader->programID, data->pos->get_pos_mat());
		model_buffer->draw(shader->programID);
		data->draw_end(shader);
	}
}
void DrawObject::draw_vec_fast(Shader *shader, std::vector<DrawDataObj*> &data_v){

	int Mat_size=sizeof(glm::mat4);
	GLuint m_buffer=Buffer::gen_buffer(0,Mat_size*(data_v.size()));
	glBindBuffer(GL_ARRAY_BUFFER,m_buffer);

	Buffer::bind_buffer_mat4(Buffer::m,data_v.size(),m_buffer);
	glm::mat4 *matrices=(glm::mat4*)glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
	DrawDataObj* data;
	sent_model_veiw_uniform(shader->programID, data_v.at(0)->pos->get_pos_mat());
	if(matrices){
		for (unsigned i=0;i<data_v.size();i++) {
			data=data_v.at(i);
			matrices[i]=data->pos->get_pos_mat();
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		shader->Enable(Shader::ModelMatArr);
		model_buffer->draw_instanced(shader->programID,data_v.size());
		shader->Disable(Shader::ModelMatArr);
	}else{
		std::cerr<<"DrawObject::draw_vec_fast"<<std::endl;
	}
	Buffer::unbind_buffer_mat4(Buffer::m);
	glDeleteBuffers(1,&m_buffer);
}
void DrawObject::draw_shadow_map(Shader *shader) {
	if (!draw_shadow)return;
	if(temp_datas.empty())return;
	if(model_buffer->lybuffer)model_buffer->lybuffer->unbind_buffer();
	if(model_buffer->uvbuffer)model_buffer->uvbuffer->unbind_buffer();
	model_buffer->vtbuffer->bind_buffer();
	draw_shadow_vec(shader, temp_datas);
	model_buffer->vtbuffer->unbind_buffer();
}
void DrawObject::draw_object(Shader *shader) {
	if(temp_datas.empty())return;

	model_buffer->bind_buffer(shader);
	glUniform4f(glGetUniformLocation(shader->programID,"mat"),mat.x,mat.y,mat.z,mat.w);
	if(alpha_drawobject){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_DST_ALPHA);
	}

	if (texture) {
		if(texture->format==GL_RGBA){
			shader->Enable(Shader::AlphaTexture);
		}
		if(!layer_texture){ //simple texture
			texture->sent_uniform(shader,0,"Texture");
			shader->sent_Uniform("TextureArr",2);
		}else{
			texture->sent_uniform(shader, 2, "TextureArr");
			shader->sent_Uniform("Texture",0);
		}
	}
	if (NormalMap) {
		shader->Enable(Shader::NormalMapping);
		if (!layer_texture) {
			NormalMap->sent_uniform(shader, 1, "NormalTexture");
			shader->sent_Uniform("NormalTextureArr",3);//clear data
		} else {
			NormalMap->sent_uniform(shader, 3, "NormalTextureArr");
			shader->sent_Uniform("NormalTexture",1);//clear data
		}
	}
	if(sky_map){
		shader->Enable(Display::Shader::SkyMap);
	}
	draw_vec(shader, temp_datas);
	//draw_vec_fast(shader, temp_datas);

	model_buffer->unbind_buffer(shader);
	shader->Disable(Display::Shader::SkyMap);
	shader->Disable(Shader::NormalMapping);
	shader->Disable(Shader::AlphaTexture);
	shader->Disable(Shader::LayerTexture);
	if (alpha_drawobject){
		glDisable(GL_BLEND);
	}
	//Buffer::disable_all_buffer();
}
}
