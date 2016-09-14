#include "class/game/chessMaster/scene/ScenePlay.h"
#include "class/game/chessMaster/common.h"

#include "class/display/light/LightControl.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/AI/AI.h"
#include "class/tim/math/Position.h"
#include "class/tim/string/String.h"
#include "class/display/draw/drawObject/drawData/drawDateEX/SkyMap.h"
#include "class/audio/AudioController.h"
#include "class/game/chessMaster/chessboard/ChessBoardCreator.h"
#include "class/display/UI/page/AutoPageControl.h"
#include "class/tim/string/String.h"
#include <stdlib.h>
#include <time.h>
namespace CM {
namespace scene{
ScenePlay::ScenePlay() {
	UI = 0;
	promotedUI=0;
	local_path = std::string("scene/play/");
	chess_board = 0;
	player_move=false;
	camera = 0;
	p1camera = 0,p2camera = 0;;
	lightControl = 0;
	selected=false;
	promoting=false;
	lock_camera=false;

	difficulty=3;
	AI_mode=0;
	ai=0;
	simulation_times=0;
	back_music=0;
	selected_step=0;
}
ScenePlay::~ScenePlay() {

}
void ScenePlay::scene_initialize() {
	chess_board=ChessBoardCreator::create("renju");
	ai=new CM::AI();
	glm::vec3 pos=glm::vec3(0.5*chess_board->cube_size*chess_board->size.x,10,-2);
	p1camera = new Display::Camera(pos,
			pos+glm::vec3(0,-7,0.5f*chess_board->size.z),
			glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	glm::vec3 pos2=glm::vec3(0.5*chess_board->cube_size*chess_board->size.x,10,
			chess_board->cube_size*chess_board->size.z+2);
	p2camera = new Display::Camera(pos2,
			pos2+glm::vec3(0,-7,-0.5f*chess_board->size.z),
			glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	camera=p2camera;
	draw->set_camera(camera);

	lightControl = new Display::LightControl(120);
	lightControl->shadow_dis=3.0f;
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(1.0, -1.2, 0.2),
					glm::vec3(0.6, 0.6, 0.6), false));
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(-0.5, -0.5, 2.1),
					glm::vec3(0.8, 0.8, 0.8), false));
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(-0.2, -1.2, -1.1),
					glm::vec3(1.2, 1.2, 1.2), true));
	lightControl->push_light(
			new Display::ParallelLight(glm::vec3(0.5, -0.4, -0.7),
					glm::vec3(0.4, 0.4, 0.4), false));


	draw->set_lightControl(lightControl);
	UI = new UI::UI(CM::folder_path+local_path+"UI/UI.txt");
	promotedUI = new UI::UI(CM::folder_path+local_path+"UI/promotedUI.txt");

	back_music=new Audio::AudioPlayer();
	back_music->set_source("default_music/prepare_your_swords.wav");
	back_music->set_volume(0.2);
	back_music->set_loop(true);
	input->push_receiver(new Input::Receiver("switch_chess"));
	input->push_receiver(new Input::Receiver("promoted"));
	resume();
}
void ScenePlay::loading(){

}
void ScenePlay::scene_terminate() {
	std::cout<<"ScenePlay::scene_terminate() 1"<<std::endl;
	input->remove_receiver("switch_chess");
	input->remove_receiver("promoted");
	if(back_music)delete back_music;
	std::cout<<"ScenePlay::scene_terminate() 2"<<std::endl;
	delete ai;
	std::cout<<"ScenePlay::scene_terminate() 3"<<std::endl;
	delete chess_board;
	std::cout<<"ScenePlay::scene_terminate() 4"<<std::endl;
	delete p1camera;
	delete p2camera;
	delete lightControl;
	delete UI;
	delete promotedUI;
	std::cout<<"ScenePlay::scene_terminate() 5"<<std::endl;
}
void ScenePlay::pause(){
	back_music->pause();
}
void ScenePlay::resume(){
	back_music->play();
	draw->Enable3D = true;
}
void ScenePlay::next_turn(CM::Step step){
	Audio::AudioController::get_cur_object()->play("default_sound_effect/Pickup_Coin2.wav",0.2);
	chess_board->next_turn(step);
}
void ScenePlay::restart(){
	ai->search_done=false;
	next_step.clear();
	selected=false;
	promoting=false;
	chess_board->restart();
}
void ScenePlay::AI_move(int player){
	if(chess_board->winner)return;
	selected=false;
	if(!ai->is_searching()&&!ai->search_done){
		//ai->do_pruning=false;
		//ai->find_best_step(thread_pool,chess_board,player,difficulty,MAX);
		//ai->do_pruning=true;
		//ai->find_best_step(thread_pool,chess_board,player,difficulty,MAX);
		ai->search_start(thread_pool,chess_board,player,difficulty);
	}
}
void ScenePlay::camera_control(){
	if(input->keyboard->pressed('R')){
		camera->v.y += 0.01f* sqrt(camera->look_dis() + 0.001);
	}
	if(input->keyboard->pressed('F')){
		camera->v.y -= 0.01f* sqrt(camera->look_dis() + 0.001);
	}
	if (input->mouse->mid_pressed()||input->keyboard->pressed('Z')) {
		camera->rotate(glm::vec3(0, 1, 0), -0.15 * input->mouse->pos_delta().x);
		camera->rotate(camera->yaw_vec(), 0.15 * input->mouse->pos_delta().y);
	}
	if(input->mouse->screen_pos.y>0.95){
		camera->v += (float) (-0.004f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.y<-0.95){
		camera->v += (float) (0.004f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.x>0.95){
		camera->v += (float) (-0.004f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if(input->mouse->screen_pos.x<-0.95){
		camera->v += (float) (0.004f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->right_pressed()) {
		camera->v += (float) (0.0005f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().y) * camera->look_vec_xz();
		camera->v += (float) (-0.0005f * sqrt(camera->look_dis() + 0.001)
				* input->mouse->pos_delta().x)
				* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if (input->mouse->scroll) {
		camera->dis_alter_v += sqrt(camera->look_dis() + 0.1)
				* (0.05 * input->mouse->scroll);
	}
	if(camera->look_at.x>0.95*chess_board->cube_size*chess_board->size.x){
		if(camera->v.x>0.0f){
			camera->v.x*=-0.9f;
		}
	}else if(camera->look_at.x<0.05*chess_board->cube_size*chess_board->size.x){
		if(camera->v.x<0.0f){
			camera->v.x*=-0.9f;
		}
	}
	if(camera->look_at.z>0.95*chess_board->cube_size*chess_board->size.z){
		if(camera->v.z>0.0f){
			camera->v.z*=-0.9f;
		}
	}else if(camera->look_at.z<0.05*chess_board->cube_size*chess_board->size.z){
		if(camera->v.z<0.0f){
			camera->v.z*=-0.9f;
		}
	}
}
void ScenePlay::player_move_chess(){
	if(ai->is_searching()){
		return;
	}
	promoting=false;
	int tmpsx=chess_board->selected_piece.x;
	int tmpsy=chess_board->selected_piece.y;;
	if(tmpsx>=0&&tmpsy>=0&&tmpsx<chess_board->chess_board->sizex&&
			tmpsy<chess_board->chess_board->sizey){
		prev_s.x=s.x;
		prev_s.y=s.y;
		s.x=chess_board->selected_piece.x;
		s.y=chess_board->selected_piece.y;

		if(selected){
			std::vector<CM::Step*>buffer;
			std::vector<std::string> sigs;
			for(unsigned i=0;i<next_step.size();i++){
				if(next_step[i].selected(s.x,s.y)){
					selected=false;
					buffer.push_back(&next_step[i]);
					sigs.push_back(Tim::String::to_string(i));
					//break;
				}
			}
			if(buffer.size()==1){
				selected_step=buffer[0];
			}else if(buffer.size()>1){
				std::vector<std::string>names;

				CM::Step* step;
				for(unsigned i=0;i<buffer.size();i++){
					step=buffer.at(i);
					for(unsigned j=0;j<step->move_num;j++){
						if(step->moves[j].w==1){
							names.push_back(chess_board->pieces.at(abs(step->moves[j].z)-1)->get_name());
						}
					}
				}
				UI::AutoPageControl *page=dynamic_cast<UI::AutoPageControl*>
				(promotedUI->get_child("promoted_page"));
				if(page){
					page->create_pages(names,&sigs);
				}
				promoting=true;
			}
		}

		if(s.x>=0&&s.y>=0&&s.x<chess_board->chess_board->sizex&&
				s.y<chess_board->chess_board->sizey){
			if(chess_board->pick_chess(chess_board->chess_board,s.x,s.y,chess_board->cur_player)){
				next_step.clear();
				chess_board->find_next_step(chess_board->chess_board,
						s.x,s.y,chess_board->cur_player,next_step);
				selected=true;
			}else{
				selected=false;
			}
		}
	}
}
void ScenePlay::handle_signal(Input::Signal *sig){
	std::vector<std::string> strs;
	Tim::String::split(sig->get_data(),"_",strs);
	if(sig->get_data()=="harder"){
		if(difficulty<7)difficulty++;
	}else if(sig->get_data()=="normal"){
		difficulty=4;
	}else if(sig->get_data()=="easier"){
		if(difficulty>1)difficulty--;
	}else if(sig->get_data()=="AVP"){
		AI_mode=AI_MODE::AI_VS_P;
	}else if(sig->get_data()=="PVP"){
		AI_mode=AI_MODE::P_VS_P;
	}else if(sig->get_data()=="PVA"){
		AI_mode=AI_MODE::P_VS_AI;
	}else if(sig->get_data()=="AVA"){
		AI_mode=AI_MODE::AI_VS_AI;
	}else if(sig->get_data()=="auto_AVA"){
		AI_mode=AI_MODE::AUTO_AI_VS_AI;
	}else if(sig->get_data()=="undo"){
		next_step.clear();
		selected=false;
		//chess_board->undo();
		if(AI_mode==AI_MODE::P_VS_AI){//P vs AI
			chess_board->prev_turn();
			chess_board->prev_turn();
		}else if(AI_mode==AI_MODE::AI_VS_P){//P vs P
			chess_board->prev_turn();
			chess_board->prev_turn();
		}else if(AI_mode==AI_MODE::P_VS_P){//P vs P
			chess_board->prev_turn();
		}

	}else if(sig->get_data()=="restart"){
		restart();
	}else if(sig->get_data()=="auto"){
		next_step.clear();
		selected=false;
		AI_move(chess_board->cur_player);
	}
}
void ScenePlay::handle_input(){

	if(input->mouse->left_clicked()){
		player_move=true;
	}else{
		player_move=false;
	}

	if(input->keyboard->get('R')){
		std::cout<<"AI reboot"<<std::endl;
		ai->searching=false;
	}
	if(input->keyboard->get('0')){
		AI_mode=0;
	}
	if(input->keyboard->get('1')){
		AI_mode=1;
	}
	if(input->keyboard->get('2')){
		AI_mode=2;
	}
	if(input->keyboard->get('S')){
		//chess_board->save_board(chess_board->dir_path+"chessBoard/board.txt");
	}
	if(input->keyboard->get('L')){
		lock_camera^=1;
		//chess_board->load_board(chess_board->dir_path+"chessBoard/board.txt");
	}
	if(!lock_camera)camera_control();
}
void ScenePlay::draw_step(){
	Display::CubeLight* cl;
	cl=new Display::CubeLight();
	cl->size=1.01f*chess_board->cube_size;
	cl->color=glm::vec3(0.5,0.5,0.5);
	cl->pos=glm::vec3((s.x+0.5f)*chess_board->cube_size,
					  (2.5f)*chess_board->cube_size,
					  (s.y+0.5f)*chess_board->cube_size);
	lightControl->push_temp_light(cl);
	for(unsigned i=0;i<next_step.size();i++){
		next_step[i].draw_next_step();
	}
}
void ScenePlay::scene_update(){
	handle_input();
	camera->update();

	if(promoting){
		promotedUI->hide=false;
	}else{
		promotedUI->hide=true;
	}
	UI->update_UIObject();
	promotedUI->update_UIObject();

	chess_board->update();

	if(player_move){//player select a chess and move
		player_move_chess();
	}
	if(selected_step){
		next_turn(*selected_step);
		selected=false;
	}
	selected_step=0;
	if(!ai->is_searching()){
		AI_update();
	}


}
void ScenePlay::AI_update(){
	if (chess_board->winner == 0) {	//no player win yet
		if(ai->search_done){
			ai->search_done=false;
			next_turn(ai->best_step);
		}
		if (AI_mode == AI_MODE::P_VS_AI) {
			if (chess_board->cur_player == -1) {
				ai->traning_mode = false;
				AI_move(chess_board->cur_player);
			} else {
				camera = p1camera;
				draw->set_camera(camera);
			}
		} else if (AI_mode == AI_MODE::AI_VS_P) {
			if (chess_board->cur_player == 1) {
				ai->traning_mode = false;
				AI_move(chess_board->cur_player);
			} else {
				camera = p2camera;
				draw->set_camera(camera);
			}
		} else if (AI_mode == AI_MODE::AI_VS_AI) {
			ai->traning_mode = false;
			AI_move(chess_board->cur_player);
		} else if (AI_mode == AI_MODE::AUTO_AI_VS_AI) {	//auto AI training
			int score = chess_board->evaluate_score(chess_board->chess_board,
					chess_board->cur_player);
			if (chess_board->steps.size() > 40) {
				if (score > 20) {
					chess_board->backpropagation();
					restart();
					if (simulation_times < 100) {
						simulation_times++;
					} else {
						simulation_times = 0;
						chess_board->save_mct();
					}
				} else if (chess_board->steps.size() > 80) {
					chess_board->draw_backpropagation();
					restart();
					if (simulation_times < 100) {
						simulation_times++;
					} else {
						simulation_times = 0;
						chess_board->save_mct();
					}
				} else {
					ai->traning_mode = true;
					AI_move(chess_board->cur_player);
				}
			} else {
				ai->traning_mode = true;
				AI_move(chess_board->cur_player);
			}
		} else if (AI_mode == AI_MODE::P_VS_P) {
			if (chess_board->cur_player == 1) {
				//camera = p1camera;
				draw->set_camera(camera);
			} else {
				//camera = p2camera;
				draw->set_camera(camera);
			}
		}
	} else {
		ai->search_done=false;
		if (AI_mode == AI_MODE::AUTO_AI_VS_AI) {
			restart();
		}
	}
}
void ScenePlay::init_board(){
	selected=false;
	next_step.clear();
	selected_step=0;
}
void ScenePlay::scene_update_end(){
	handle_input();
	while(Input::Signal*sig=input->get_signal("switch_chess")){
		std::cout<<"play_chess:"<<sig->get_data()<<std::endl;
		init_board();

		delete chess_board;
		chess_board=ChessBoardCreator::create(sig->get_data());
	}
	while(Input::Signal*sig=input->get_signal("promoted")){
		//std::cout<<"promoted:"<<sig->get_data()<<std::endl;
		unsigned num=Tim::String::str_to_int(sig->get_data());
		selected_step=next_step.at(num);
		promoting=false;
	}
}
void ScenePlay::draw_AI_difficulty(){
	if(difficulty==1){
		draw->push(new Display::RenderString("Hyper Easy AI",0.02,math::vec2<float>(0.4,0.95)));
	}else if(difficulty==2){
		draw->push(new Display::RenderString("Super Easy AI",0.02,math::vec2<float>(0.4,0.95)));
	}else if(difficulty==3){
		draw->push(new Display::RenderString("Easy AI",0.02,math::vec2<float>(0.4,0.95)));
	}else if(difficulty==4){
		draw->push(new Display::RenderString("Normal AI",0.02,math::vec2<float>(0.4,0.95)));
	}else if(difficulty==5){
		draw->push(new Display::RenderString("Normal+ AI",0.02,math::vec2<float>(0.4,0.95)));
	}else if(difficulty==6){
		draw->push(new Display::RenderString("Hard AI",0.02,math::vec2<float>(0.4,0.95)));
	}else if(difficulty==7){
		draw->push(new Display::RenderString("super Hard AI",0.02,math::vec2<float>(0.4,0.95)));
	}
}
void ScenePlay::draw_board_data(){
	draw->push(new Display::RenderString(Tim::String::to_string(chess_board->selected_piece.x)+","+
	Tim::String::to_string(chess_board->selected_piece.y),0.02,math::vec2<float>(0.6,0.95)));

	int score=chess_board->evaluate_score(chess_board->chess_board,chess_board->cur_player);
	draw->push(new Display::RenderString("score:"+Tim::String::to_string(score),0.02,math::vec2<float>(0,0.85)));
	draw->push(new Display::RenderString("turn:"+Tim::String::to_string((int)chess_board->steps.size()),
			0.02,math::vec2<float>(0.2,0.85)));
	if(chess_board->winner!=0){
		if(chess_board->winner==1)draw->push(new Display::RenderString("player1 win!!",0.05,math::vec2<float>(0.3,0.5)));
		else draw->push(new Display::RenderString("player2 win!!",0.05,math::vec2<float>(0.3,0.5)));
	}
}
void ScenePlay::draw_prev_step(){
	CM::Step *step;
	if(!chess_board->steps.empty()){
		step=chess_board->steps.back();
		step->draw_step(0.4,0.4,0.6);
		if(chess_board->steps.size()>=2){
			step=chess_board->steps.at(chess_board->steps.size()-2);
			step->draw_step(0.4,0.6,0.4);
		}
	}
}
void ScenePlay::scene_draw(){
	Display::DrawObject* galaxy=Display::AllDrawObjects::get_cur_object()->get("default/galaxy");
	Display::DrawDataObj* data=new Display::DrawDataObj(&back_ground_pos,false,false);
	data->push_ex_data(new Display::drawDataEX::SkyMap());
	galaxy->push_temp_drawdata(data);

	if(ai->is_searching()){
		float time_used=(glfwGetTime()-ai->start_time);
		draw->push(new Display::RenderString("AI thinking time:"+
				Tim::String::to_string(time_used),0.02,math::vec2<float>(0,0.95)));
	}else{
		if(AI_mode==AI_MODE::AUTO_AI_VS_AI||AI_mode==AI_MODE::AI_VS_AI){

		}else{
			if(chess_board->cur_player==1){
				draw->push(new Display::RenderString("player1's turn",0.02,math::vec2<float>(0,0.95)));
			}else{
				draw->push(new Display::RenderString("player2's turn",0.02,math::vec2<float>(0,0.95)));
			}
		}
	}

	draw_AI_difficulty();
	draw_board_data();

	UI->draw_UIObject(draw);
	promotedUI->draw_UIObject(draw);

	chess_board->draw();

	Display::CubeLight* cl=new Display::CubeLight();
	cl->size=1.01f*chess_board->cube_size;

	cl->color=glm::vec3(0,1,0);
	cl->pos=glm::vec3((chess_board->selected_on.x+0.5f)*chess_board->cube_size,
			(chess_board->selected_on.y+0.5f)*chess_board->cube_size,
			(chess_board->selected_on.z+0.5f)*chess_board->cube_size);

	lightControl->push_temp_light(cl);

	draw_prev_step();
	if(selected){
		draw_step();
	}
}

}
} /* namespace CM */
