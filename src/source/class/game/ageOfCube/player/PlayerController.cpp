/*
 *      Author: LukeWu
 */
#include <iostream>
#include "class/game/ageOfCube/player/PlayerController.h"
#include "class/input/Input.h"

namespace AOC {

PlayerController::PlayerController() {
	receiver=new Input::Receiver("PlayerController");
	Input::Input::get_cur_object()->push_receiver(receiver);

	current_player = new Player(0,type_player);
	current_player -> init_UI();
	//std::cout<<"current_player : "<<current_player<<std::endl;
	players.push_back(current_player);
	players.push_back(new Player(1, type_bot));
	register_cur();
}

PlayerController::~PlayerController() {
	Input::Input::get_cur_object()->remove_receiver(receiver->get_name());
	for(unsigned i=0;i<players.size();i++){
		delete players.at(i);
	}
	//delete receiver; //delete by input remove_reveiver
}
void PlayerController::game_over(unsigned player_id){
	//std::cout<<"player "<<player_id<<" game over"<<std::endl;
	players.at(player_id)->set_gameover(true);
}
void PlayerController::update(){
	for(unsigned i=0;i<players.size();i++){
		players.at(i)->update();
	}
}

void PlayerController::draw(Display::Draw* draw){
	current_player->draw(draw);
}

Player* PlayerController::search_player(unsigned int player_id){
	for(unsigned i=0;i<players.size();i++){
		if(players.at(i)->get_id()==player_id){
			return players.at(i);
		}
	}
	std::cerr<<"PlayerController::search_player player id:"<<player_id<<" not exist"<<std::endl;
	return 0;
}

void PlayerController::save(FILE *file){
	for(unsigned i=0;i<players.size();i++){
		players.at(i)->save(file);
	}
}
void PlayerController::load(FILE *file){
	for(unsigned i=0;i<players.size();i++){
		players.at(i)->load(file);
	}
}

} /* namespace AOC */
