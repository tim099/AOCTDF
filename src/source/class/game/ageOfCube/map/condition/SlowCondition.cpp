/*
 * SlowCondition.cpp
 *
 *  Created on: 2016¦~7¤ë30¤é
 *      Author: LukeWu
 */

#include <iostream>
#include "class/game/ageOfCube/map/condition/SlowCondition.h"


namespace AOC {

SlowCondition::SlowCondition(int _total_time, int _peroiod, Unit *_owner)
	:Condition( _total_time, _peroiod, _owner)
{
	owner2 = dynamic_cast<Minion *>(owner);
}

SlowCondition::~SlowCondition() {
	// TODO Auto-generated destructor stub
}

void SlowCondition::takeEffect(){
	//std::cout<<"take effect"<<std::endl;
	owner2->set_vel(owner2->get_vel() * 0.5);
}

void SlowCondition::endEffect(){
}

} /* namespace AOC */
