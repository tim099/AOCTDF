#include "class/game/ageOfCube/map/attack/missile/Bomb.h"

#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/audio/AudioController.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/Draw.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/ageOfCube/map/attack/AttackCreator.h"

namespace AOC {

Bomb::Bomb() {

}
Bomb::~Bomb() {

}
Bomb::Bomb(Bomb* cube){
	radius=cube->radius;
	timer=0;
	type=0;
}
Display::DrawObject *Bomb::get_missile_drawobj(){
	return Display::AllDrawObjects::get_cur_object()->get("attack/cube_missile_1");
}
void Bomb::draw_attack(){
	if(explode_timer){

	}else{
		Display::DrawObject *missile_Drawobj=get_missile_drawobj();
		math::Position *dp_pos=new math::Position();
		dp_pos->set_pos(glm::vec3(pos.x,pos.y,pos.z));
		dp_pos->set_scale(glm::vec3(2*radius,2*radius,2*radius));
		dp_pos->set_r(glm::vec3((180.0/M_PI)*atan2(sqrt(vel.x*vel.x+vel.z*vel.z),vel.y),
				(180.0/M_PI)*atan2(vel.x,vel.z),0));
		missile_Drawobj->push_temp_drawdata(new Display::DrawDataObj(dp_pos,true,true));
	}
}
void Bomb::explode(){
	if(!target)return;

	Attack* attack=AttackCreator::get_cur_object()->create("AOE");
	//Attack* attack=AttackCreator::get_cur_object()->create("GravityAOE");

	attack->radius=5.0;

	attack->pos=pos;
	attack->set_target(target);
	attack->set_damage(damage);
	attack->set_player(player_id);
	attack->create_attack();

	explode_timer++;
}

} /* namespace AOC */
