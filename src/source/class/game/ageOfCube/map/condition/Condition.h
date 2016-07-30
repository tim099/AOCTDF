/*
 * Condition.h
 *
 *  Created on: 2016¦~7¤ë30¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CONDITION_CONDITION_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CONDITION_CONDITION_H_

#include "class/game/ageOfCube/map/minion/Minion.h"

namespace AOC {

class Condition {
public:
	Condition(int _total_time, int _peroiod, Minion *_owner);
	virtual ~Condition();
	void update();
	virtual void takeEffect();
	virtual void endEffect();
	void setOwner(Minion *_owner){owner = _owner;}
protected:
	Minion *owner;
	int total_time;
	int remaining_time;
	int effect_time_period;
	int tic;
	bool end;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CONDITION_CONDITION_H_ */
