#include "class/game/chessMaster/scene/SceneMultiPlayer.h"
#include "class/game/chessMaster/chessboard/ChessBoardCreator.h"
#include "class/display/light/LightControl.h"

#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/display/draw/drawObject/drawData/drawDateEX/SkyMap.h"
#include "class/display/UI/page/AutoPageControl.h"
#include "class/audio/AudioController.h"
#include "class/display/UI/string/EnterString.h"
namespace CM {

SceneMultiPlayer::SceneMultiPlayer() {
	local_path = std::string("scene/multiplayer/");
	chess_board=0;
	camera = 0;
	lightControl=0;
	UI=0;
	promotedUI=0;
	selected=false;
	player_move=false;
	promoting=false;
	p1camera=0;
	p2camera=0;
	selected_step=0;
	client=0;
	server=0;
}
SceneMultiPlayer::~SceneMultiPlayer() {

}
void SceneMultiPlayer::scene_initialize(){
	chess_board=ChessBoardCreator::create("renju");
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
	camera=p1camera;
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
	input->push_receiver(new Input::Receiver("switch_chess"));
	input->push_receiver(new Input::Receiver("promoted"));
	UI = new UI::UI(CM::folder_path+local_path+"UI/UI.txt");
	UI::EnterString *ipstr=dynamic_cast<UI::EnterString*>(UI->get_child("ip"));
	ipstr->set_string(game::network::Socket::get_local_address());
	promotedUI = new UI::UI(CM::folder_path+local_path+"UI/promotedUI.txt");

	resume();
}
void SceneMultiPlayer::scene_terminate(){
	input->remove_receiver("switch_chess");
	input->remove_receiver("promoted");
	if(UI){
		delete UI;
		UI=0;
	}
	if(promotedUI){
		delete promotedUI;
		promotedUI=0;
	}
	if(server){
		server->end();
		delete server;
		server=0;
	}
	if(client){
		client->end();
		delete client;
		client=0;
	}
	if(chess_board)delete chess_board;
	delete p1camera;
	delete p2camera;
	delete lightControl;
}
void SceneMultiPlayer::pause(){
	if(UI){
		delete UI;
		UI=0;
	}
}
void SceneMultiPlayer::resume(){
	draw->Enable3D=true;

}
void SceneMultiPlayer::loading(){

}
void SceneMultiPlayer::next_turn(CM::Step step){
	Audio::AudioController::get_cur_object()->play("default_sound_effect/Pickup_Coin2.wav",0.2);
	//step.load_string(step_str);
	chess_board->next_turn(step);
}
void SceneMultiPlayer::scene_update(){
	handle_input();

	if(selected_step){
		next_turn((*selected_step));
		std::string step_str=selected_step->to_string();
		if(server){
			server->sent_data("next_turn#"+step_str);
		}else if(client){
			client->sent_data("next_turn#"+step_str);
		}
		selected=false;
	}
	selected_step=0;
	handle_receive_data();

	if(promoting){
		promotedUI->hide=false;
	}else{
		promotedUI->hide=true;
	}
	promotedUI->update_UIObject();
	if(server){
		if(server->get_new_connection()){
			server->sent_data("switch_chess#"+chess_board->game_name);
			restart();
		}
	}
	if(player_move){
		player_move_chess();
	}


	camera->update();
	UI->update_UIObject();
	chess_board->update();
}
void SceneMultiPlayer::handle_receive_data(std::string str){
	std::string a,b;
	Tim::String::split_into_two(str,"#",a,b);
	if(a=="next_turn"){
		CM::Step step;
		step.load_string(b);
		next_turn(step);
	}else if(a=="switch_chess"){
		switch_chess(b);
	}else if(a=="restart"){
		restart();
	}else if(a=="undo"){
		undo();
	}
}
void SceneMultiPlayer::handle_receive_data(){
	if(server){
		std::string str;
		while((str=server->receive_data())!=""){
			handle_receive_data(str);
		}
	}else if(client){
		std::string str;
		while((str=client->receive_data())!=""){
			handle_receive_data(str);
		}
		if(!client->client_start){
			if(client){
				client->end();
				delete client;
				client=0;
			}
		}
	}
}
void SceneMultiPlayer::draw_step(){
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
void SceneMultiPlayer::scene_draw(){
	Display::DrawObject* galaxy=Display::AllDrawObjects::get_cur_object()->get("default/galaxy");
	Display::DrawDataObj* data=new Display::DrawDataObj(&back_ground_pos,false,false);
	data->push_ex_data(new Display::drawDataEX::SkyMap());
	galaxy->push_temp_drawdata(data);


	UI->draw_UIObject(draw);
	promotedUI->draw_UIObject(draw);

	chess_board->draw();

	Display::CubeLight* cl=new Display::CubeLight();
	cl->size=1.01f*chess_board->cube_size;

	cl->color=glm::vec3(0,1,0);
	cl->pos=glm::vec3((chess_board->selected_on.x+0.5f)*chess_board->cube_size,
			(chess_board->selected_on.y+0.5f)*chess_board->cube_size,
			(chess_board->selected_on.z+0.5f)*chess_board->cube_size);


	CM::Step *step;
	if(!chess_board->steps.empty()){
		step=chess_board->steps.back();
		step->draw_step(0.4,0.4,0.6);
		if(chess_board->steps.size()>=2){
			step=chess_board->steps.at(chess_board->steps.size()-2);
			step->draw_step(0.4,0.6,0.4);
		}
	}

	lightControl->push_temp_light(cl);

	if(selected)draw_step();

	if(server){
		draw->push(new Display::RenderString("Host ip="+server->server_addr+
				"		local ip="+server->local_addr,
				0.02,math::vec2<float>(0.1,0.99)));
		if(server->client_connected()){
			draw->push(new Display::RenderString("client connected!!",
					0.02,math::vec2<float>(0.1,0.9)));
		}else{
			draw->push(new Display::RenderString("client not connected!!",
					0.02,math::vec2<float>(0.1,0.9)));
		}

	}else if(client){
		draw->push(new Display::RenderString("Client",
				0.02,math::vec2<float>(0.1,0.99)));
	}
	if (chess_board->winner!=0) {
		if ((chess_board->winner>0&&server)||(chess_board->winner<0&&client)){
			draw->push(new Display::RenderString("You Win!!",
					0.04,math::vec2<float>(0.4,0.7)));
		}else {
			draw->push(new Display::RenderString("You Lose!!",
					0.04,math::vec2<float>(0.4,0.7)));
		}
	}
}


void SceneMultiPlayer::camera_control(){
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
void SceneMultiPlayer::handle_input(){
	if(input->mouse->left_clicked()){
		player_move=true;
	}else{
		player_move=false;
	}

	camera_control();
}
void SceneMultiPlayer::handle_signal(Input::Signal *sig){
	if(sig->get_data()=="restart"){
		restart();
		if(server){
			server->sent_data("restart#");
		}else if(client){
			client->sent_data("restart#");
		}
	}else if(sig->get_data()=="connect_server"){
		if(server){
			server->end();
			delete server;
			server=0;
		}
		if(client){
			client->end();
			delete client;
			client=0;
		}
		camera=p2camera;
		draw->set_camera(camera);
		UI::EnterString *ipstr=dynamic_cast<UI::EnterString*>(UI->get_child("ip"));
		std::cout<<"connect_server:"<<ipstr->get_string()<<std::endl;
		client=new game::network::Client();
		client->set_ip(ipstr->get_string());
		client->start();
	}else if(sig->get_data()=="host_server"){
		if(server){
			server->end();
			delete server;
			server=0;
		}
		if(client){
			client->end();
			delete client;
			client=0;
		}
		server=new game::network::Server();
		server->start();
		camera=p1camera;
		draw->set_camera(camera);
	}else if(sig->get_data()=="undo"){
		undo();
		if(server){
			server->sent_data("undo#");
		}else if(client){
			client->sent_data("undo#");
		}
	}

}
void SceneMultiPlayer::undo(){
	next_step.clear();
	selected=false;
	chess_board->prev_turn();
}
void SceneMultiPlayer::restart(){
	next_step.clear();
	selected=false;
	promoting=false;
	chess_board->restart();
}
void SceneMultiPlayer::player_move_chess(){
	promoting=false;
	int tmpsx=chess_board->selected_piece.x;
	int tmpsy=chess_board->selected_piece.y;;
	if(tmpsx>=0&&tmpsy>=0&&tmpsx<chess_board->chess_board->sizex&&
			tmpsy<chess_board->chess_board->sizey){
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
void SceneMultiPlayer::init_board(){
	selected=false;
	//next_step.clear();
	//selected_step=0;
}
void SceneMultiPlayer::switch_chess(std::string str){
	init_board();

	delete chess_board;
	chess_board=ChessBoardCreator::create(str);
}
void SceneMultiPlayer::scene_update_end(){
	while(Input::Signal*sig=input->get_signal("switch_chess")){
		std::cout<<"play_chess:"<<sig->get_data()<<std::endl;
		switch_chess(sig->get_data());

		if(server){
			server->sent_data("switch_chess#"+chess_board->game_name);
		}else if(client){
			client->sent_data("switch_chess#"+chess_board->game_name);
		}
	}
	while(Input::Signal*sig=input->get_signal("promoted")){
		std::cout<<"promoted:"<<sig->get_data()<<std::endl;
		unsigned num=Tim::String::str_to_int(sig->get_data());
		selected_step=next_step.at(num);
		promoting=false;
	}
}
} /* namespace CM */
