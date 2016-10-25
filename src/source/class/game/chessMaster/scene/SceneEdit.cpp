#include "class/game/chessMaster/scene/SceneEdit.h"

#include "class/game/chessMaster/common.h"

#include "class/display/light/LightControl.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/AI/AI.h"
#include "class/tim/math/Position.h"
#include "class/tim/string/String.h"
#include "class/display/draw/drawObject/drawData/drawDateEX/SkyMap.h"
#include "class/audio/AudioController.h"
#include "class/display/texture/AllTextures.h"
#include "class/tim/string/String.h"
#include "class/game/chessMaster/chessboard/ChessBoardCreator.h"
#include "class/display/UI/string/EnterString.h"
#include <stdlib.h>
#include <time.h>
namespace CM {
namespace scene{
SceneEdit::SceneEdit() {
	UI = 0;
	edit_board_UI=0;
	edit_chess_UI=0;
	edit_rule_UI=0;
	rule_UI=0;
	import_texture_UI=0;
	selected_piece=0;
	selected_rule=0;
	init_game="renju";//
	local_path = std::string("scene/edit/");
	chess_board = 0;
	camera = 0;
	light_control = 0;
	destruct_mode=false;
	type=1;
	chess_type=0;
	//edit_chess=false;
	back_music=0;

	mode=edit_board;
}
SceneEdit::~SceneEdit() {

}
void SceneEdit::init_board(){
	type=1;
	chess_type=0;
	selected_piece=0;
	selected_rule=0;
}
void SceneEdit::loading(){

}
void SceneEdit::set_chess_board(ChessBoard* board){
	chess_board=board;
	chess_board->init_UI(edit_board_UI);
}
void SceneEdit::scene_initialize() {
	load_UI();
	set_chess_board(ChessBoardCreator::create(init_game));
	glm::vec3 pos=glm::vec3(4,10,-2);
	camera = new Display::Camera(pos,
			pos+glm::vec3(0,-7,4),
			glm::vec3(0, 1, 0), 60.0, 0.1f,
			10000.0f);
	camera->shadow_far=60.0f;
	draw->set_camera(camera);

	light_control = new Display::LightControl(120);
	light_control->shadow_dis=3.0f;

	light_control->push_light(
			new Display::ParallelLight(glm::vec3(1.0, -1.2, 0.2),
					glm::vec3(0.6, 0.6, 0.6), false));
	light_control->push_light(
			new Display::ParallelLight(glm::vec3(-0.5, -0.5, 2.1),
					glm::vec3(0.8, 0.8, 0.8), false));
	light_control->push_light(
			new Display::ParallelLight(glm::vec3(-0.2, -1.2, -1.1),
					glm::vec3(1.2, 1.2, 1.2), true));
	light_control->push_light(
			new Display::ParallelLight(glm::vec3(0.5, -0.4, -0.7),
					glm::vec3(0.4, 0.4, 0.4), false));

	draw->set_lightControl(light_control);


	back_music=new Audio::AudioPlayer();
	back_music->set_source("default_music/prepare_your_swords.wav");
	back_music->set_volume(0.2);
	back_music->set_loop(true);
	input->push_receiver(new Input::Receiver("edit_chess"));
	input->push_receiver(new Input::Receiver("edit_rule"));
	input->push_receiver(new Input::Receiver("add_rule"));
	input->push_receiver(new Input::Receiver("rule"));

	input->push_receiver(new Input::Receiver("if_edit_rule"));
	input->push_receiver(new Input::Receiver("if_edit_condition"));
	input->push_receiver(new Input::Receiver("if_add_condition"));
	input->push_receiver(new Input::Receiver("rule_if"));

	resume();
	std::cout<<"SceneEdit::scene_initialize() 2"<<std::endl;
}
void SceneEdit::load_UI(){
	if(UI)delete UI;
	if(edit_chess_UI)delete edit_chess_UI;
	if(edit_board_UI)delete edit_board_UI;
	if(edit_rule_UI)delete edit_rule_UI;
	if(rule_UI)delete rule_UI;
	if(import_texture_UI)delete import_texture_UI;

	UI = new UI::UI(CM::folder_path+local_path+"UI/UI.txt");
	edit_chess_UI=new UI::UI(CM::folder_path+local_path+"UI/edit_chessUI.txt");
	edit_board_UI=new UI::UI(CM::folder_path+local_path+"UI/edit_boardUI.txt");
	edit_rule_UI=new UI::UI(CM::folder_path+local_path+"UI/edit_ruleUI.txt");
	rule_UI=new UI::UI(CM::folder_path+local_path+"UI/pieceUI.txt");
	import_texture_UI=new UI::UI(CM::folder_path+local_path+"UI/import_textureUI.txt");


}
void SceneEdit::scene_terminate() {
	//std::cout<<"SceneEdit::scene_terminate() 1"<<std::endl;
	input->remove_receiver("edit_chess");
	input->remove_receiver("edit_rule");
	input->remove_receiver("add_rule");
	input->remove_receiver("rule");

	input->remove_receiver("if_edit_rule");
	input->remove_receiver("if_edit_condition");
	input->remove_receiver("if_add_condition");
	input->remove_receiver("rule_if");
	if(back_music)delete back_music;
	//std::cout<<"SceneEdit::scene_terminate() 2"<<std::endl;
	delete chess_board;
	//std::cout<<"SceneEdit::scene_terminate() 3"<<std::endl;
	delete camera;
	delete light_control;

	if(edit_chess_UI)delete edit_chess_UI;
	if(edit_board_UI)delete edit_board_UI;
	if(edit_rule_UI)delete edit_rule_UI;
	if(rule_UI)delete rule_UI;
	if(import_texture_UI)delete import_texture_UI;
	if(UI)delete UI;

	//std::cout<<"SceneEdit::scene_terminate() 4"<<std::endl;
}
void SceneEdit::pause(){
	back_music->pause();
}
void SceneEdit::resume(){
	back_music->play();
	draw->Enable3D = true;
}
void SceneEdit::set_chess_type(int type){
	chess_type=type;
	if(mode==edit_piece){
		if(chess_type>0){
			chess_board->pieces.at(chess_type-1)->init_piece_UI(edit_chess_UI);
		}
	}
}
void SceneEdit::add_piece(){
	if(mode==edit_piece){
		UI::EnterString *str=dynamic_cast<UI::EnterString*>(edit_chess_UI->get_child("piece_name"));
		std::string name=str->get_string();
		Piece *piece=new Piece();
		piece->init(name);
		chess_board->push_piece(piece);
	}
}
void SceneEdit::handle_signal(Input::Signal *sig){
	//std::cerr<<sig->get_data()<<std::endl;
	//std::cerr<<"SceneEdit::handle_signal 1"<<std::endl
	std::vector<std::string> strs;
	Tim::String::split(sig->get_data(),"_",strs);
	if(sig->get_data()=="Edit_chess"){
		mode=edit_piece;
	}else if(sig->get_data()=="Edit_board"){
		mode=edit_board;
	}else if(sig->get_data()=="Edit_rule"){
		mode=edit_rule;
	}else if(sig->get_data()=="Import_texture"){
		mode=import_texture;
	}else if(sig->get_data()=="load_board"){
		chess_board->load_board(chess_board->dir_path+"chessBoard/board.txt");
	}else if(sig->get_data()=="save_board"){
		chess_board->save_board(chess_board->dir_path+"chessBoard/board.txt");
	}else if(sig->get_data()=="reload_UI"){
		load_UI();
	}else if(sig->get_data()=="plus"){
		if(mode==edit_piece||mode==edit_rule){
			if(chess_type<(int)chess_board->pieces.size()){
				set_chess_type(chess_type+1);
				//chess_type++;
			}
		}else if(mode==edit_board){
			if(type<chess_board->cube_type_num)type++;
		}

	}else if(sig->get_data()=="minus"){
		if(mode==edit_piece||mode==edit_rule){
			if(chess_type>0){
				//chess_type--;
				set_chess_type(chess_type-1);
			}
		}else if(mode==edit_board){
			if(type>1)type--;
		}
	}else if(sig->get_data()=="switch_player"){
		destruct_mode^=1;
	}else if(sig->get_data()=="destruct"){
			destruct_mode=true;
	}else if(sig->get_data()=="build"){
			destruct_mode=false;
	}else if(sig->get_data()=="remove_rule"){
			if(selected_piece&&selected_rule){
				if(selected_rule->get_remove_rule()){
					selected_piece->remove_basic_rule(selected_rule);
					selected_piece->init_rule_page(rule_UI);
					selected_rule=0;
				}
			}
	}else if(sig->get_data()=="rule_edit_done"){
		if(selected_rule){
			if(selected_rule->get_edit_done()){
				selected_rule->deselected();
				selected_rule=0;
			}
		}
	}else if(sig->get_data()=="piece_edit_done"){
		if(chess_type>0){
			chess_board->pieces.at(chess_type-1)->update_piece_UI(edit_chess_UI);
		}
	}else if(sig->get_data()=="board_edit_done"){
		chess_board->update_UI(edit_board_UI);
	}else if(sig->get_data()=="add_piece"){
		add_piece();
	}
	//
	//std::cerr<<"SceneEdit::handle_signal 2"<<std::endl;
	//std::cout<<sig->get_data()<<std::endl;
}
void SceneEdit::camera_control(){
	if(input->keyboard->pressed('R')){
		camera->v.y += 0.01f* sqrt(camera->look_dis() + 0.001);
	}
	if(input->keyboard->pressed('F')){
		camera->v.y -= 0.01f* sqrt(camera->look_dis() + 0.001);
	}
	if (input->mouse->mid_pressed()||input->keyboard->pressed('Z')) {
		//std::cout<<"move"<<(int)(mouse->pos.x)<<","<<(int)mouse->prev_pos.x<<std::endl;
		camera->rotate(glm::vec3(0, 1, 0), -0.15 * input->mouse->pos_delta().x);
		camera->rotate(camera->yaw_vec(), 0.15 * input->mouse->pos_delta().y);
	}
	//camera->rotate(glm::vec3(0, 1, 0), 1.0f);
	if(input->mouse->screen_pos.y>0.95){
		camera->v += (float) (-0.007f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.y<-0.95){
		camera->v += (float) (0.007f * sqrt(camera->look_dis() + 0.001))
				* camera->look_vec_xz();
	}
	if(input->mouse->screen_pos.x>0.95){
		camera->v += (float) (-0.007f * sqrt(camera->look_dis() + 0.001))
		* glm::cross(camera->look_vec_xz(), glm::vec3(0, 1, 0));
	}
	if(input->mouse->screen_pos.x<-0.95){
		camera->v += (float) (0.007f * sqrt(camera->look_dis() + 0.001))
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
void SceneEdit::handle_input(){
	if(input->keyboard->get('V')){
		destruct_mode^=1;
	}

	if(mode==edit_piece){
		if (input->mouse->left_clicked()) {
			if(!destruct_mode){
				chess_board->set_type(chess_board->selected_on.x,
						chess_board->selected_on.z,chess_type);
			}else{
				chess_board->set_type(chess_board->selected_on.x,
						chess_board->selected_on.z,-chess_type);
			}
		}
	}else if(mode==edit_board){
		if (input->mouse->left_clicked()) {
			if(!destruct_mode){
				chess_board->set_type(chess_board->selected_on.x,
									chess_board->selected_on.y,
									chess_board->selected_on.z,type);
			}else{
				chess_board->set_type(chess_board->selected_cube.x,
									chess_board->selected_cube.y,
									chess_board->selected_cube.z,0);
			}
		}
	}else if(mode==edit_rule){
		if (input->mouse->left_clicked()){
			if(chess_board->selected_on.x>=0&&chess_board->selected_on.z>=0){
				set_selected_piece(chess_board->get_piece(chess_board->selected_piece.x,
						chess_board->selected_piece.y));
			}
		}
	}

	if(input->keyboard->get('P')){
		mode=edit_piece;
	}
	if(input->keyboard->get('B')){
		mode=edit_board;
	}
	if(input->keyboard->get(Input::KeyCode::Plus)){
		if(mode==edit_piece||mode==edit_rule){
			if(chess_type<(int)chess_board->pieces.size()){
				set_chess_type(chess_type+1);
			}
		}else if(mode==edit_board){
			if(type<chess_board->cube_type_num)type++;
		}

	}
	if(input->keyboard->get(Input::KeyCode::Minus)){
		if(mode==edit_piece||mode==edit_rule){
			if(chess_type>0){
				set_chess_type(chess_type-1);
			}
		}else if(mode==edit_board){
			if(type>1)type--;
		}
	}
	camera_control();
}
void SceneEdit::scene_update(){
	camera->update();
	edit_chess_UI->hide=true;
	edit_board_UI->hide=true;
	edit_rule_UI->hide=true;
	if(mode==edit_piece){
		edit_chess_UI->hide=false;
	}else if(mode==edit_board){
		edit_board_UI->hide=false;
	}else if(mode==edit_rule){
		edit_rule_UI->hide=false;
		edit_rule_UI->update_UIObject();

		if(selected_piece){
			selected_piece->update_rule_UI(rule_UI);
			if(selected_rule){
				selected_rule->update_UI();
			}
		}
	}else if(mode==import_texture){
		import_texture_UI->update_UIObject();
	}
	edit_chess_UI->update_UIObject();
	edit_board_UI->update_UIObject();


	UI->update_UIObject();
	chess_board->find_select_cube();
	chess_board->winner=chess_board->check_winner(chess_board->chess_board);
}
void SceneEdit::set_selected_piece(Piece *piece){
	if(!piece)return;
	piece_at.x=chess_board->selected_on.x;
	piece_at.y=chess_board->selected_on.z;
	selected_piece=piece;



	if(selected_rule){
		while(!selected_rule->get_edit_done()){
		}
		selected_rule->deselected();
		selected_rule=0;
	}
	selected_piece->init_rule_page(rule_UI);
}
void SceneEdit::set_selected_rule(BasicRule* _selected_rule){
	selected_rule=_selected_rule;
	if(selected_rule){
		selected_rule->init_UI();
	}
}
void SceneEdit::scene_update_end(){
	handle_input();

	if(selected_rule){
		selected_rule->update();
	}
	while(Input::Signal*sig=input->get_signal("add_rule")){
		if(selected_piece){
			if(selected_rule)selected_rule->deselected();
			selected_piece->add_rule(sig->get_data());
			selected_piece->init_rule_page(rule_UI);
		}
		delete sig;
	}
	while(Input::Signal*sig=input->get_signal("edit_chess")){
		std::cout<<"edit_chess:"<<sig->get_data()<<std::endl;
		delete chess_board;
		set_chess_board(ChessBoardCreator::create(sig->get_data()));
		init_board();
		delete sig;
	}
	while(Input::Signal*sig=input->get_signal("edit_rule")){
		//std::cout<<"edit_rule:"<<sig->get_data()<<std::endl;
		unsigned rule_num=Tim::String::str_to_int(sig->get_data());
		//std::cout<<"edit_rule:"<<rule_num<<std::endl;
		if(selected_piece){
			if(rule_num<selected_piece->basic_rules.size()){
				set_selected_rule(selected_piece->basic_rules.at(rule_num));
			}
		}
		delete sig;
	}

}
void SceneEdit::scene_draw(){
	UI->draw_UIObject(draw);
	edit_chess_UI->draw_UIObject(draw);
	edit_board_UI->draw_UIObject(draw);
	edit_rule_UI->draw_UIObject(draw);

	Display::DrawObject* galaxy=Display::AllDrawObjects::get_cur_object()->get("default/galaxy");
	Display::DrawDataObj* data=new Display::DrawDataObj(&back_ground_pos,false,false);
	data->push_ex_data(new Display::drawDataEX::SkyMap());
	galaxy->push_temp_drawdata(data);


	draw->push(new Display::RenderString(Tim::String::to_string(chess_board->selected_piece.x)+","+
	Tim::String::to_string(chess_board->selected_piece.y),0.02,math::vec2<float>(0.7,0.98)));

	if(mode==edit_piece){
		static math::Position pos=math::Position(glm::vec3(), glm::vec3());

		if(chess_type>0){
			pos.set_pos(glm::vec3((chess_board->selected_on.x+0.5f)*chess_board->cube_size,
					(chess_board->selected_on.y+0.5f)*chess_board->cube_size,
					(chess_board->selected_on.z+0.5f)*chess_board->cube_size));
			if(destruct_mode){
				pos.set_ry(0);
			}else{
				pos.set_ry(180);
			}
			chess_board->pieces.at(chess_type-1)->draw(&pos,!destruct_mode);
		}
		draw->push(new Display::RenderString("Edit Piece",0.015,math::vec2<float>(0.75,0.98)));
		if(chess_type!=0){
			draw->push(new Display::RenderString("Piece="+chess_board->pieces.at(abs(chess_type)-1)->get_name(),
							0.015,math::vec2<float>(0.75,0.93)));
		}else{
			draw->push(new Display::RenderString("remove Piece",0.015,math::vec2<float>(0.75,0.93)));
		}
	}else if(mode==edit_board){
		draw->push(new Display::RenderString("Edit Board",0.02,math::vec2<float>(0.8,0.98)));
		draw->push(new Display::RenderString("Board type="+Tim::String::to_string(type),
				0.02,math::vec2<float>(0.8,0.93)));

		Display::DrawData2D* data = new Display::DrawData2D(1.0,math::vec2<float>(0.85,0.88),0.08);
		data->layer=type-1;
		Display::Texture* texture=Display::AllTextures::get_cur_tex(chess_board->tex_path);
		draw->push(new Display::DrawTexture(texture, data));
	}if(mode==edit_rule){
		draw->push(new Display::RenderString("Edit Rule",0.02,math::vec2<float>(0.8,0.98)));

		if(selected_piece){
			draw->push(new Display::RenderString("Piece="+selected_piece->get_name(),0.02,
					math::vec2<float>(0.8,0.93)));
			rule_UI->draw_UIObject(draw);
			if(selected_rule){
				selected_rule->draw_UI();
				selected_rule->draw_rule(chess_board->chess_board,piece_at.x,
						piece_at.y);
			}
			Display::CubeLight* cl;
			cl=new Display::CubeLight();
			cl->size=1.01f*chess_board->cube_size;
			cl->color=glm::vec3(0.5,0.5,0.5);
			cl->pos=glm::vec3((piece_at.x+0.5f)*chess_board->cube_size,
							  (2.5f)*chess_board->cube_size,
							  (piece_at.y+0.5f)*chess_board->cube_size);
			light_control->push_temp_light(cl);
		}
	}else if(mode==import_texture){
		import_texture_UI->draw_UIObject(draw);
	}

	chess_board->draw();
	Display::CubeLight* cl=new Display::CubeLight();
	cl->size=1.01f*chess_board->cube_size;

	if(destruct_mode){
		cl->color=glm::vec3(1,0,0);
		cl->pos=glm::vec3((chess_board->selected_cube.x+0.5f)*chess_board->cube_size,
						  (chess_board->selected_cube.y+0.5f)*chess_board->cube_size,
						  (chess_board->selected_cube.z+0.5f)*chess_board->cube_size);
	}else{
		cl->color=glm::vec3(0,1,0);
		cl->pos=glm::vec3((chess_board->selected_on.x+0.5f)*chess_board->cube_size,
				  (chess_board->selected_on.y+0.5f)*chess_board->cube_size,
				  (chess_board->selected_on.z+0.5f)*chess_board->cube_size);
	}
	light_control->push_temp_light(cl);
}



}
} /* namespace CM */
