/*
 * Condition.h
 *
 *  Created on: 2016¦~7¤ë30¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CONDITION_CONDITION_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CONDITION_CONDITION_H_

namespace AOC {

class Unit;

class Condition {
public:
	Condition(int _total_time, int _peroiod, Unit *_owner);
	virtual ~Condition();
	void update();
	virtual void takeEffect();
	virtual void endEffect();
	void setOwner(Unit *_owner){owner = _owner;}
	bool end;
protected:
	Unit *owner;
	int total_time;
	int remaining_time;
	int effect_time_period;
	int tic;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CONDITION_CONDITION_H_ */
