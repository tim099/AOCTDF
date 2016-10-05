#include "class/game/ageOfCube/map/attack/aoe/AreaOfEffect.h"

#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/audio/AudioController.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/Draw.h"
#include "class/game/ageOfCube/player/PlayerController.h"
#include "class/game/ageOfCube/player/Player.h"

#include "class/display/draw/Draw.h"

#include "class/game/ageOfCube/map/condition/SlowCondition.h"
#include "class/display/draw/particle/Particle.h"
#include <cmath>

namespace AOC {


AreaOfEffect::AreaOfEffect() {
	radius=0.1;
	timer=0;
	type=0;
	explode_timer=0;
	max_explode_time=12;
	this->special_collide_off=true;
	this->be_collide_off=true;
	stop_when_collide=false;
	physical = false;
	exploded_render=false;
}
AreaOfEffect::~AreaOfEffect() {

}
void AreaOfEffect::explode_target(Unit* unit){
	unit->hp_alter(-damage);
	unit->add_condition(new SlowCondition(1000,1,unit));
}
void  AreaOfEffect::explode(){
	//std::cout<<"AOE::explode()  radius="<<radius<<std::endl;

	for(unsigned i=0;i<collied_units.size();i++){
		explode_target(collied_units.at(i));
		//std::cout<<"id"<<collied_units.at(i)->get_id()<<"  damage : "<<damage<<std::endl;
		if(collied_units.at(i)->get_is_dead()){
			Player* player=PlayerController::get_cur_object()->search_player(player_id);
			player->score_alter(target->get_max_hp());
		}
	}
	Audio::AudioController::get_cur_object()->
			play_by_dis("default_sound_effect/Bomb.wav",pos,1000);

	explode_timer++;
	//die=true;
}

void AreaOfEffect::draw_attack(){
	if(explode_timer==1){
		if(!exploded_render){
			exploded_render=true;
			Display::Particle *p=new Display::Particle("misc/explode_atlas",pos,
					math::vec2<double>(0.5*radius,0.5*radius),64);
			p->set_atlas(8,8,1);
			Display::Draw::get_cur_object()->push(p);
		}
	}
	if(explode_timer){
		Display::PointLight *light=new Display::PointLight(
				glm::vec3(pos.x,pos.y,pos.z),
				glm::vec3(7.0,5.0,5.0)*(float)(12.0f-explode_timer),false);
		Display::Draw::get_cur_object()->lightControl->push_temp_light(light);
	}
}

void AreaOfEffect::attack_update(){
	//std::cout<<"Missile::attack_update()"<<std::endl;
	if(explode_timer){
		explode_timer++;
		if(explode_timer>max_explode_time)die=true;
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
