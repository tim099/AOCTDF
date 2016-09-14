#include "class/game/ageOfCube/map/minion/ball/Ball.h"
#include "class/display/draw/Draw.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/ageOfCube/map/Map.h"

#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/entity/EntityController.h"
#include "class/audio/AudioController.h"
#include "class/game/ageOfCube/map/attack/weapon/WeaponCreator.h"
#include "class/game/ageOfCube/player/PlayerController.h"
#include <cstdlib>
#include <ctime>
namespace AOC {
void Ball::minion_pre_init(){
	ball_Drawobj=Display::AllDrawObjects::get_cur_object()->get("minion/ball");
}
Ball::Ball() {
	ball_Drawobj=0;
	set_max_hp(100);
}
Ball::Ball(Ball* ball) {
	ball_Drawobj=ball->ball_Drawobj;
	//attack_damage=10;
	set_attack_cycle(300);
	set_max_hp(ball->get_hp());

	//Weapon* weapon=WeaponCreator::get_cur_object()->create("MissileLauncher");
	//weapon->set_attack_range(8.0);
	//weapon->set_attack_damage(10);
	//weapon->set_attack_size(0.36);

	//push_weapon(weapon);
}
void Ball::unit_create(){
	//weapons.at(0)->set_attack_size(1.5*rigid_body.radius);
	//weapons.at(0)->set_pos(math::vec3<double>(0,0.55*(get_size().y),0));
}
Ball::~Ball() {

}
void Ball::save_minion(FILE * file){

}
void Ball::load_minion(FILE * file){

}
void Ball::killed(){
	Player *cur_player=PlayerController::get_cur_object()->get_cur_player();
	cur_player->modify_resource("cube",1*(get_max_hp()/50));
	int ran=rand()%20;
	//std::cout<<"ran="<<ran<<std::endl;
	switch(ran){
		case 0:
			cur_player->modify_resource("cube",1*(get_max_hp()/30));
			break;
		case 1:
			cur_player->modify_resource("water",1*(get_max_hp()/100));
			break;
		case 2:
			cur_player->modify_resource("fire",1*(get_max_hp()/100));
			break;
		case 3:
			cur_player->modify_resource("earth",1*(get_max_hp()/100));
			break;
		case 4:
			cur_player->modify_resource("air",1*(get_max_hp()/100));
			break;
		default:
			cur_player->modify_resource("cube",1*(get_max_hp()/50));
			break;
	}
	Audio::AudioController::get_cur_object()->play("default_sound_effect/Pickup_Coin2.wav",0.3);
}
void Ball::minion_update(){
	rigid_body.mass=rigid_body.radius*rigid_body.radius*rigid_body.radius;
}
void Ball::draw_minion(){
	math::vec3<double> pos=get_pos();
	dp_pos.set_pos(glm::vec3(pos.x,pos.y,pos.z));
	dp_pos.set_scale(glm::vec3(2.0*rigid_body.radius,2.0*rigid_body.radius,2.0*rigid_body.radius));
	ball_Drawobj->push_temp_drawdata(new Display::DrawDataObj(&dp_pos));
}
} /* namespace AOC */
