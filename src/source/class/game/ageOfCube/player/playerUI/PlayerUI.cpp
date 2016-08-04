/*
 * PlayerUI.cpp
 *
 *  Created on: 2016¦~6¤ë9¤é
 *      Author: LukeWu
 */

#include <iostream>
#include "class/game/ageOfCube/player/playerUI/PlayerUI.h"
#include "class/tim/string/String.h"

namespace UI {

PlayerUI::PlayerUI() {
	inited = false;
	score_string = 0;
	resource_amount_string=0;
	health_string=0;
}

PlayerUI::~PlayerUI() {
	// TODO Auto-generated destructor stub
}

void PlayerUI::init_playerUI(){
	resource_amount_string = dynamic_cast<UIString *>(get_child("resource1_amount"));
	score_string = dynamic_cast<UIString *>(get_child("player_score"));
	health_string = dynamic_cast<UIString *>(get_child("player_health"));

	inited = true;
}

bool PlayerUI::check_script(){
	return true;
}

void PlayerUI::set_resource_amount(int value){
	//std::cout<<"set_resource "<<resource_string_id<<" amount "<<value<<std::endl;
	if(!inited){
		return;
	}
	resource_amount_string->set_string(Tim::String::to_string(value));
}

void PlayerUI::set_score(int score){
	//std::cout<<"set_resource "<<resource_string_id<<" amount "<<value<<std::endl;
	if(!inited){
		return;
	}
	score_string->set_string(Tim::String::to_string(score));
}

} /* namespace AOC */
