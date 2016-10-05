#include "class/game/ageOfCube/map/condition/GravityCondition.h"
#include "class/game/ageOfCube/map/minion/Minion.h"
namespace AOC {

GravityCondition::GravityCondition(int _total_time, int _peroiod, Unit *_owner,math::vec3<double> _pos,double _a)
			:Condition( _total_time, _peroiod, _owner){
	owner_minion= dynamic_cast<Minion *>(owner);
	pos=_pos;a=_a;
	if(!owner_minion){
		end = true;
	}
}
GravityCondition::~GravityCondition() {

}
void GravityCondition::takeEffect(){
	if(owner_minion){
		math::vec3<double> del=this->pos-owner_minion->get_mid_pos();
		owner_minion->set_vel(owner_minion->get_vel()+a*del.normalize());
	}
}
void GravityCondition::endEffect(){

}
} /* namespace AOC */
