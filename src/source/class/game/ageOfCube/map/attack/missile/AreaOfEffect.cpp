/*
 * AreaOfEffect.cpp
 *
 *  Created on: 2016¦~8¤ë16¤é
 *      Author: LukeWu
 */

#include "class/game/ageOfCube/map/attack/missile/AreaOfEffect.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/audio/AudioController.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/Draw.h"
#include "class/game/ageOfCube/player/PlayerController.h"
#include "class/game/ageOfCube/player/Player.h"
#include "class/display/draw/Draw.h"
#include <cmath>

namespace AOC {


AreaOfEffect::AreaOfEffect() {
	radius=0.1;
	timer=0;
	type=0;
	explode_timer=0;
	this->special_collide_off=true;
	this->be_collide_off=true;
	stop_when_collide=false;
	physical = false;
	exploded_render=false;
}

AreaOfEffect::AreaOfEffect(AreaOfEffect *aoe){
	radius=aoe->radius;
	timer=aoe->timer;
	type=aoe->type;
	explode_timer=0;
	this->special_collide_off=true;
	this->be_collide_off=true;
	stop_when_collide=false;
	physical = false;
	exploded_render=false;
}

AreaOfEffect::~AreaOfEffect() {

}
void  AreaOfEffect::explode(){
	//std::cout<<"AOE::explode()  radius="<<radius<<std::endl;

	for(unsigned i=0;i<collied_units.size();i++){
		collied_units.at(i)->hp_alter(-damage);
		//std::cout<<"id"<<collied_units.at(i)->get_id()<<"  damage : "<<damage<<std::endl;
		if(collied_units.at(i)->get_is_dead()){
			Player* player=PlayerController::get_cur_object()->search_player(player_id);
			player->score_alter(target->get_max_hp());
		}
	}
	Audio::AudioController::get_cur_object()->
			play_by_dis("default_sound_effect/Bomb.wav",pos,100);

	explode_timer++;
	//die=true;
}

void AreaOfEffect::draw_attack(){
	if(explode_timer==1){
		if(!exploded_render){
			exploded_render=true;
			//std::cout<<"AreaOfEffect::draw_attack()"<<std::endl;
			Display::Draw::get_cur_object()->draw_particle("misc/explode",pos,
				math::vec2<double>(0.5*radius,0.5*radius),20);
		}

	}
}

void AreaOfEffect::attack_update(){
	//std::cout<<"Missile::attack_update()"<<std::endl;
	if(explode_timer){
		explode_timer++;
		if(explode_timer>2)die=true;
		return;
	}
	timer++;
	if(be_collided==true||collided==true){
		explode();
	}
	/*
	if(timer<50){
		this->collision_off=true;
	}else{
		this->collision_off=false;
	}
	*/
}

} /* namespace AOC */
