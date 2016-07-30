/*
 * SlowCondition.h
 *
 *  Created on: 2016¦~7¤ë30¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CONDITION_SLOWCONDITION_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CONDITION_SLOWCONDITION_H_

#include "class/game/ageOfCube/map/condition/Condition.h"

namespace AOC {

class SlowCondition: public Condition {
public:
	SlowCondition(int _total_time, int _peroiod, Minion *_owner);
	virtual ~SlowCondition();
	virtual void takeEffect();
	virtual void endEffect();
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CONDITION_SLOWCONDITION_H_ */
