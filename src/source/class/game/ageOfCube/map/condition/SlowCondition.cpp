/*
 * SlowCondition.cpp
 *
 *  Created on: 2016¦~7¤ë30¤é
 *      Author: LukeWu
 */

#include "class/game/ageOfCube/map/condition/SlowCondition.h"

namespace AOC {

SlowCondition::SlowCondition(int _total_time, int _peroiod, Minion *_owner)
	:Condition( _total_time, _peroiod, _owner)
{
}

SlowCondition::~SlowCondition() {
	// TODO Auto-generated destructor stub
}

void SlowCondition::takeEffect(){
	owner->set_vel(owner->get_vel() * 0.5);
}

void SlowCondition::endEffect(){
	owner->set_vel(owner->get_vel() * 2);
}

} /* namespace AOC */
