#include "class/display/draw/Draw.h"
#include "class/display/light/LightControl.h"
#include "class/display/shader/Shader.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/texture/texture2D/Texture2D.h"
#include "class/display/font/StringRenderer.h"
#include "class/display/font/TextureString.h"
#include "class/display/font/DrawDataStr.h"
#include "class/display/light/LightControl.h"
#include "class/display/buffer/frameBuffer/FrameBuffer.h"
#include "class/display/texture/AllTextures.h"
#include "class/input/mouse/Mouse.h"
#include "class/display/window/ViewPort.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/display/font/DrawTextureStr.h"
#include "class/display/draw/billboard/BillBoardRenderer.h"
#include "class/display/draw/particle/ParticleRenderer.h"
#include "class/display/texture/texture3D/cubemap/TextureCubeMap.h"
#include "class/display/draw/drawObject/DrawObject.h"
#include "class/tim/thread/mutex/Mutex.h"
#include "class/game/Config.h"
#include <cmath>
#include <iostream>
namespace Display{
Draw::Draw() {
	d_objsMutex=new Tim::Mutex();
	d_texsMutex=new Tim::Mutex();
	//strRenderer=new StringRenderer("files/texture/font/font.bmp");
	std::vector<std::string> paths;
	paths.push_back("files/texture/sky/sky0.bmp");
	paths.push_back("files/texture/sky/sky1.bmp");
	paths.push_back("files/texture/sky/sky2.bmp");
	paths.push_back("files/texture/sky/sky3.bmp");
	paths.push_back("files/texture/sky/sky4.bmp");
	paths.push_back("files/texture/sky/sky5.bmp");
	sky_box=new TextureCubeMap(paths,
			glm::ivec2(256,256),
			GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, P_MipMap);
	strRenderer=new StringRenderer("files/texture/font/font1.png");
	billBoardRenderer=new BillBoardRenderer();
	particleRenderer=new ParticleRenderer();
	lightControl=0;
	camera=0;
	Enable3D=true;
	real_water=game::Config::get_cur_object()->real_water;
	wave_height=0.2f;
	wave_width=0.8f;
	water_height=40.0f;
	time=0.0;
}
Draw::~Draw() {
	delete d_objsMutex;
	delete d_texsMutex;
	delete strRenderer;
	delete billBoardRenderer;
	delete particleRenderer;
	delete sky_box;
	while(!d_texs.empty()){
		delete d_texs.back();
		d_texs.pop_back();
	}
}
void Draw::set_lightControl(Display::LightControl* _lightControl){
	lightControl=_lightControl;
}
void Draw::set_camera(Camera *_camera){
	camera=_camera;
}
void Draw::draw3D(Shader *shader,Shader *shaderWater,Shader *shaderShadowMapping,
		Shader2D *shader2D,FrameBuffer *FBO,FrameBuffer *waterReflectFBO,
		FrameBuffer * waterRefractFBO){
	if(!Enable3D){
		shader->active_shader();
		FBO->bind_buffer();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear buffer
		return;
	}
	if(!camera||!lightControl){
		std::cerr<<"Draw::draw3D fail,light control or camera no set yet!!"<<std::endl;
		return;
	}
	lightControl->gen_shadow(shaderShadowMapping,camera,this);

	shader->active_shader();
	FBO->bind_buffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear buffer
	//sent uniform
	FBO->depth_textures.at(0)->sent_uniform(shader,33,"depthTexture");
	//Texture* sky_box=AllTextures::get_cur_tex("default/skybox")->sent_uniform(shader,30,"skybox");
	sky_box->sent_uniform(shader,30,"skybox");
	camera->sent_uniform(shader->programID,FBO->aspect());
	lightControl->sent_uniform(shader,camera->pos);
    for(unsigned i=0;i<d_objs.size();i++){//100
    	d_objs.at(i)->draw_object(shader);//draw all obj
    }

    draw_billBoard(shader,camera);
    draw_particle(shader,camera);
    draw_water(shader,shaderWater,FBO,waterReflectFBO,waterRefractFBO);

    Input::Mouse::get_cur_mouse()->get_world_space_pos(FBO,
			glm::inverse(camera->view_matrix(FBO->aspect())));

}
void Draw::draw_billBoard(Shader *shader,Camera *camera){
	billBoardRenderer->draw(shader,camera);
}
void Draw::draw_particle(Shader *shader,Camera *camera){
	particleRenderer->draw(shader,camera);
}
void Draw::draw_water(Shader *shader,Shader *shaderWater,FrameBuffer *FBO,
		FrameBuffer *waterReflectFBO,FrameBuffer *waterRefractFBO){
	Camera reflect_cam(camera);
	Camera refract_cam(camera);
	if(real_water){
	    waterReflectFBO->bind_buffer();
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear buffer

	    //float water_height=Map::get_cur_object()->get_water_height()*Map::CUBE_SIZE;
	    shader->Enable(Shader::Clipping);
	    glm::vec4 clip_plane(0,1.0,0,-water_height+0.01);
	    shader->sent_Uniform("clipping_plane",clip_plane);

		reflect_cam.pos.y-=2.0*(reflect_cam.pos.y-water_height);
		reflect_cam.look_at.y-=2.0*(reflect_cam.look_at.y-water_height);
		reflect_cam.fovy+=10;
		//reflect_cam.up.y=-1.0;
		reflect_cam.sent_uniform(shader->programID, waterReflectFBO->aspect());
		lightControl->sent_uniform(shader,camera->pos);
	    for(unsigned i=0;i<d_objs.size();i++){//100
	    	d_objs.at(i)->draw_object(shader);//draw all obj
	    }
	    shader->Disable(Shader::Clipping);

	    waterRefractFBO->bind_buffer();
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear buffer
	    shader->Enable(Shader::Clipping|Shader::Back_culling);

	    clip_plane=glm::vec4(0,-1.0,0,water_height-0.01);
	    shader->sent_Uniform("clipping_plane",clip_plane);
		//sent uniform

		refract_cam.dis_alter(1.0);
		refract_cam.fovy+=10;
		refract_cam.sent_uniform(shader->programID, waterRefractFBO->aspect());
		lightControl->sent_uniform(shader,camera->pos);
	    for(unsigned i=0;i<d_objs.size();i++){//100
	    	d_objs.at(i)->draw_object(shader);//draw all obj
	    }
	    shader->Disable(Shader::Clipping|Shader::Back_culling);
	}



	FBO->bind_buffer();

	//waterFBO->depth_textures.at(0)->draw_texture(shader2D,
				//new DrawData2D(1.0, glm::vec2(0, 1.0), 0.3));
	shaderWater->active_shader();


	//float time=glfwGetTime();
	if(time>1000.0){
		time=0.0;
	}else{
		time+=0.02;
	}
	shaderWater->sent_Uniform("waveTime",time);
	shaderWater->sent_Uniform("waveHeight",wave_height);
	shaderWater->sent_Uniform("waveWidth",wave_width);
	if(real_water){
		shaderWater->sent_Uniform("real_water",1);
		reflect_cam.sent_uniform(shaderWater->programID, waterReflectFBO->aspect(),"reflectWVP");
		waterReflectFBO->depth_textures.at(0)->sent_uniform(shaderWater,31,"reflectdepthtex");
		waterReflectFBO->color_textures.at(0)->sent_uniform(shaderWater,32,"reflecttex");

		refract_cam.sent_uniform(shaderWater->programID, waterRefractFBO->aspect(),"refractWVP");
		waterRefractFBO->depth_textures.at(0)->sent_uniform(shaderWater,34,"refractdepthtex");
		waterRefractFBO->color_textures.at(0)->sent_uniform(shaderWater,35,"refracttex");
	}else{
		shaderWater->sent_Uniform("real_water",0);
	}


	//sent uniform
	Texture*skybox_tex=AllTextures::get_cur_tex("default/skybox");
	if(skybox_tex){
		skybox_tex->sent_uniform(shaderWater, 30, "skybox");
	}


	camera->sent_uniform(shaderWater->programID, FBO->aspect());
	lightControl->sent_uniform(shaderWater,camera->pos);
    for(unsigned i=0;i<water_d_objs.size();i++){//100
    	//std::cout<<"draw water"<<std::endl;
    	water_d_objs.at(i)->draw_object(shaderWater);//draw all obj
    }
}
void Draw::draw2D(Shader2D *shader2D,FrameBuffer *FBO){
	FBO->bind_buffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear buffer
    for(unsigned i=0;i<d_texs.size();i++){
    	d_texs.at(i)->draw(shader2D);
    }
    strRenderer->draw(shader2D);
}
void Draw::draw_shadow(Shader *shader,FrameBuffer *FBO){
    for(unsigned i=0;i<d_objs.size();i++){
    	d_objs.at(i)->draw_shadow_map(shader);//draw all obj
    }
}
void Draw::remove(DrawObject* obj){
	if(obj->get_type()=="WaterDrawObject"){
		for(unsigned i=0;i<water_d_objs.size();i++){
			if(water_d_objs.at(i)==obj){
				water_d_objs.at(i)=water_d_objs.back();
				water_d_objs.pop_back();
				return;
			}
		}
	}else{
		for(unsigned i=0;i<d_objs.size();i++){
			if(d_objs.at(i)==obj){
				d_objs.at(i)=d_objs.back();
				d_objs.pop_back();
				return;
			}
		}
	}
	std::cerr<<"Draw::remove(DrawObject* obj) fail,can't find obj:"<<obj<<std::endl;
}
void Draw::push(DrawObject* obj){
	d_objsMutex->wait_for_this();
	if(obj->get_type()=="WaterDrawObject"){
		//std::cout<<"push draw object alpha"<<std::endl;
		water_d_objs.push_back(obj);
	}else{
		d_objs.push_back(obj);
	}
	d_objsMutex->release();
}
void Draw::push(DrawTexture* tex){
	d_texsMutex->wait_for_this();
	d_texs.push_back(tex);
	d_texsMutex->release();
}
void Draw::push(RenderString* renderStr){
	//std::cout<<"push "<<renderStr->str<<std::endl;
	strRenderer->push(renderStr);
}
void Draw::push(BillBoard* billboard){
	billBoardRenderer->push(billboard);
}
void Draw::push(Particle* particle){
	particleRenderer->push(particle);
}
void Draw::draw_bill_board(std::string texture,math::vec3<double> pos,math::vec2<double> size){
	BillBoard *bill_board=new BillBoard(texture,pos,size);
	push(bill_board);
}
void Draw::draw_particle(std::string texture,math::vec3<double> pos,math::vec2<double> size,int timer){
	Particle* particle=new Particle(texture,pos,size,timer);
	push(particle);
}
DrawData* Draw::push_as_tex(RenderString* renderStr){
	//std::cout<<"push as tex"<<renderStr->str<<std::endl;
	TextureString *tex=new TextureString();
	DrawDataStr *data=new DrawDataStr(strRenderer,renderStr);

	DrawTextureStr* draw_tex=new DrawTextureStr(tex,data);

	push(draw_tex);
	return data;
}
DrawObject* Draw::get_obj(unsigned i){
	return d_objs.at(i);
}
unsigned Draw::obj_size()const{
	return d_objs.size();
}
void Draw::update(){
    for(unsigned i=0;i<d_objs.size();i++){
    	d_objs.at(i)->update();
    }
    for(unsigned i=0;i<water_d_objs.size();i++){
    	water_d_objs.at(i)->update();
    }

}
void Draw::logical_update(){
	particleRenderer->update();
}
void Draw::logical_clear(){
	particleRenderer->clear();
}
void Draw::clear_tmp_data(){
    for(unsigned i=0;i<d_objs.size();i++){
    	d_objs.at(i)->clear_temp_drawdata();
    }
    for(unsigned i=0;i<water_d_objs.size();i++){
    	water_d_objs.at(i)->clear_temp_drawdata();
    }
    billBoardRenderer->clear_temp_drawdata();
    particleRenderer->clear_temp_drawdata();

    while(!d_texs.empty()){
    	delete d_texs.back();
    	d_texs.pop_back();
    }
    strRenderer->clear();
    if(lightControl){
    	lightControl->clear_temp_data();
    }
}
}
