#include "class/game/ageOfCube/scene/SceneStart.h"
#include "class/tim/file/File.h"
#include "class/display/UI/string/UIString.h"
#include "class/tim/string/String.h"
#include "class/game/ageOfCube/scene/SceneEditMap.h"
#include "class/game/ageOfCube/scene/ScenePlayTD.h"
#include "class/game/ageOfCube/field/StaticField.h"
#include <ctime>
#include <iostream>

namespace AOC{
SceneStart::SceneStart() {
	UI=0;
	receiver=0;
	p_control=0;
	auto_p_control=0;
	map_folder_path="files/AgeOfCube/maps/";
	music_player = 0;
	field = 0;
	camera = 0;
	lightControl = 0;
	//loading();
}
void SceneStart::scene_initialize(){

	glm::vec3 pos(10,80,10);

	camera = new Display::Camera(pos,
			pos+glm::vec3(10,-10,10), glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	camera->shadow_far=120.0;
	draw->set_camera(camera);

	lightControl = new Display::LightControl(120);
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(0.05, -1.2, -0.2),
					glm::vec3(0.3, 0.3, 0.3),false));
	draw->set_lightControl(lightControl);

	UI = new UI::UI();
	UI->Load_script("files/AgeOfCube/scenes/editMap/UI/editMapUI.txt");
	music_player = Audio::AudioPlayer("default_music/prepare_your_swords.wav");
	music_player.set_loop(true);



	//loading2();
	resume();
	//std::vector<std::string> files=Tim::File::get_all_dirs("files/texture/");
	//for(unsigned i=0;i<files.size();i++)std::cout<<files.at(i)<<std::endl;
}
void SceneStart::scene_terminate(){
	//UI->Save_script("files/AgeOfCube/startScene/UI/startSceneUI.txt");
	if(UI){
		delete UI;
		UI=0;
	}
	if(field){
		delete field;
		field = 0;
	}
}
SceneStart::~SceneStart() {

}
void SceneStart::pause(){
	music_player.pause();
	if(field){
		delete field;
		field = 0;
	}
}
void SceneStart::resume(){
	//std::cout<<"SceneStart::resume() 1"<<std::endl;
	music_player.play();
	draw->Enable3D=true;
	draw->set_camera(camera);
	draw->set_lightControl(lightControl);

	if(UI){
		delete UI;
		UI=0;
	}
	UI = new UI::UI("files/AgeOfCube/scenes/startScene/UI/startSceneUI.txt");
	p_control=(UI::PageControl*)UI->get_child("pageControl");
	auto_p_control=(UI::AutoPageControl*)UI->get_child("newGame_autoPageControl");
	//if(UI)delete UI;

	if(!p_control){
		std::cerr<<"SceneStart::scene_initialize ,can't find child page control"<<std::endl;
	}else{
		p_control->switch_page("startPage");
	}
	field=new StaticField();

	std::string map_name = "title";
	glm::ivec3 map_size(200,50,200);
	if(Tim::File::check_if_file_exist(map_folder_path+map_name)){
		//std::cout<<"find map"<<std::endl;
		field->load(map_folder_path+map_name);
	}else{
		//std::cout<<"not find map"<<std::endl;
		field->map->gen_map(map_size,time(NULL));
	}
	//std::cout<<"SceneStart::resume() END"<<std::endl;
}
void SceneStart::handle_signal(Input::Signal* sig){
	//std::cout<<"SceneStart got signal:"<<sig->get_data()<<std::endl;
	if(sig->get_data()=="CreateNewMap"){
		create_new_map();
	}else if(sig->get_data()=="CreateMap"){
		create_map();
	}else if(sig->get_data()=="edit_map"){
		load_map("edit");
	}else if(sig->get_data()=="delete_map"){
		delete_map();
	}else if(sig->get_data()=="play"){
		load_map("play");
	}
}
void SceneStart::load_map(std::string mode){
	std::string map_name=((UI::UIString*)UI->get_child("Selected_Map"))->get_string();
	if(map_name=="Null")return;
	Input::Signal *sig=new Input::Signal("push_scene","Game");

	if(mode == "edit"){
		sig->ex_data=new AOC::SceneEditMap(map_folder_path+map_name,
			glm::ivec3(1,1,1));
	}
	else if(mode == "play"){
		sig->ex_data=new AOC::ScenePlayTD(map_folder_path+map_name,
					glm::ivec3(1,1,1));
	}

	sig->sent();
}
void SceneStart::delete_map(){
	std::string map_name=((UI::UIString*)UI->get_child("Selected_Map"))->get_string();
	Tim::File::delete_file(map_folder_path+map_name);
	auto_p_control->update_pages();
}
void SceneStart::create_new_map(){
	UI::UIString *new_map_name=(UI::UIString*)UI->get_child("NewMapName");
	UI::UIString *new_map_size=(UI::UIString*)UI->get_child("NewMapSize");
	std::cout<<"new Map Name="<<new_map_name->get_string()<<std::endl;
	std::cout<<"new Map Size="<<new_map_size->get_string()<<std::endl;
	UI::PageControl* createNewMap_pc=(UI::PageControl*)UI->get_child("createNewMap_pageControl");
	createNewMap_pc->switch_page("newMap");
	UI::UIString *map_name=(UI::UIString*)UI->get_child("MapName");
	UI::UIString *map_size=(UI::UIString*)UI->get_child("MapSize");
	map_name->set_string(new_map_name->get_string());
	map_size->set_string(new_map_size->get_string());
}
void SceneStart::create_map(){
	UI::UIString *map_name=(UI::UIString*)UI->get_child("MapName");
	UI::UIString *map_size_str=(UI::UIString*)UI->get_child("MapSize");
	std::vector<std::string> size;
	Tim::String::split(map_size_str->get_string(),"*",size);
	std::cout<<"Map Name="<<map_name->get_string()<<std::endl;
	unsigned map_size[3];
	std::cout<<"map size=";
	if(size.size()!=3){
		std::cerr<<"SceneStart::create_map() fail!! Invalid Map Size:"
				<<map_size_str->get_string()<<std::endl;
		std::cerr<<"Please Enter Map Size"<<std::endl;
		return ;
	}
	for(int i=0;i<3;i++){
		map_size[i]=Tim::String::str_to_int(size.at(i).c_str());
		//sscanf(size.at(i).c_str(),"%u",&map_size[i]);
		std::cout<<map_size[i]<<",";
	}std::cout<<std::endl;
	Input::Signal *sig=new Input::Signal("push_scene","Game");
	sig->ex_data=new AOC::SceneEditMap(map_folder_path+std::string(map_name->get_string()),
			glm::ivec3(map_size[0],map_size[1],map_size[2]));
	//sig->ex_data=new SceneStart();
	sig->sent();

}
void SceneStart::handle_input(){
	///*
	if(input->keyboard->get('E')){
		if(UI->check_mode(UI::Mode::EDIT)){
			UI->Disable_Mode(UI::Mode::EDIT);
		}else{
			UI->Enable_Mode(UI::Mode::EDIT);
		}
	}else if(input->keyboard->get('S')){
		//UI->Save_script("files/AgeOfCube/startScene/UI/startSceneUI.txt");
	}else if(input->keyboard->get('L')){
		//delete UI;
		//UI = new UI::UI("files/AgeOfCube/startScene/UI/startSceneUI.txt");
	}
	//*/


	if (input->mouse->mid_pressed()||input->keyboard->pressed('Z')) {
		//std::cout<<"move"<<(int)(mouse->pos.x)<<","<<(int)mouse->prev_pos.x<<std::endl;
		camera->rotate(glm::vec3(0, 1, 0), -0.15 * input->mouse->pos_delta().x);
		camera->rotate(camera->yaw_vec(), 0.15 * input->mouse->pos_delta().y);
	}
	//camera->rotate(glm::vec3(0, 1, 0), 1.0f);
	if(input->mouse->screen_pos.y>0.95){
		camera->v += (float) (-0.02f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.y<-0.95){
		camera->v += (float) (0.02f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.x>0.95){
		camera->v += (float) (-0.02f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if(input->mouse->screen_pos.x<-0.95){
		camera->v += (float) (0.02f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->right_pressed()) {
		camera->v += (float) (0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().y) * camera->look_vec_xz();
		camera->v += (float) (-0.001f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().x)
				* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->scroll) {
		camera->dis_alter_v += sqrt(camera->look_dis() + 0.1)
				* (0.05 * input->mouse->scroll);
	}
	if(camera->look_at.x>Map::CUBE_SIZE*field->map->get_size().x+4.0){
		if(camera->v.x>0.0f){
			camera->v.x*=-0.9f;
		}
	}else if(camera->look_at.x<-4.0){
		if(camera->v.x<0.0f){
			camera->v.x*=-0.9f;
		}
	}
	if(camera->look_at.z>Map::CUBE_SIZE*field->map->get_size().z+4.0){
		if(camera->v.z>0.0f){
			camera->v.z*=-0.9f;
		}
	}else if(camera->look_at.z<-4.0){
		if(camera->v.z<0.0f){
			camera->v.z*=-0.9f;
		}
	}
}
void SceneStart::scene_update(){
	handle_input();
	field->update();
	UI->update_UIObject();
}
void SceneStart::scene_draw(){
	field->draw(draw,camera,thread_pool);
	UI->draw_UIObject(draw);
}
}
