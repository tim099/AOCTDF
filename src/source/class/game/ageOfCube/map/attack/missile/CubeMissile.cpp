#include "class/game/ageOfCube/map/attack/missile/CubeMissile.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace AOC {

CubeMissile::CubeMissile() {
	//radius=cube->radius;
	//special_collide_off=true;
	be_collide_off=true;
	stop_when_collide=false;
	timer=0;
	type=0;
}
CubeMissile::~CubeMissile() {

}
Display::DrawObject *CubeMissile::get_missile_drawobj(){
	return Display::AllDrawObjects::get_cur_object()->get("attack/cube_missile_1");
}
} /* namespace AOC */
