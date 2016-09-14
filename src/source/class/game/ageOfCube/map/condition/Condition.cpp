/*
 * Condition.cpp
 *
 *  Created on: 2016¦~7¤ë30¤é
 *      Author: LukeWu
 */

#include "class/game/ageOfCube/map/condition/Condition.h"

namespace AOC {

Condition::Condition(int _total_time, int _peroiod, Unit *_owner){
	owner = _owner;
	total_time = _total_time;
	remaining_time = total_time;
	tic = 0;
	effect_time_period = _peroiod;
	end = false;
}

Condition::~Condition() {
	// TODO Auto-generated destructor stub
}


void Condition::update(){
	if(end) return;


	if(remaining_time == 0){
		end = true;
	}
	if(tic % effect_time_period == 0){
		takeEffect();
	}

	tic++;
	remaining_time--;
}

void Condition::takeEffect(){

}

void Condition::endEffect(){

}

} /* namespace AOC */
