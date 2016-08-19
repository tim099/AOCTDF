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

void Bomb::explode(){
	if(!target)return;

	Attack* attack=AttackCreator::get_cur_object()->create("AOE");
	attack->radius=10.0;

	attack->pos=pos;
	attack->set_target(target);
	attack->set_damage(damage);
	attack->set_player(player_id);
	attack->create_attack();

	explode_timer++;
}

} /* namespace AOC */
