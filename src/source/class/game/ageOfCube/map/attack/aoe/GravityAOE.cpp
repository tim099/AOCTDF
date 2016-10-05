#include "class/game/ageOfCube/map/attack/aoe/GravityAOE.h"

#include "class/game/ageOfCube/map/minion/Minion.h"
#include "class/game/ageOfCube/map/condition/GravityCondition.h"
namespace AOC {

GravityAOE::GravityAOE() {
	//std::cout<<"GravityAOE::GravityAOE()"<<std::endl;
	max_explode_time=60;
}
GravityAOE::~GravityAOE() {

}
void GravityAOE::explode_target(Unit* unit){
	//std::cout<<"GravityAOE::explode_target(Unit* unit)"<<std::endl;
	unit->add_condition(new GravityCondition(60,1,unit,pos,-0.5));

}
} /* namespace AOC */
