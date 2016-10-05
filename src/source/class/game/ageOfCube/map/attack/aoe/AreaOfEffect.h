/*
 * AreaOfEffect.h
 *
 *  Created on: 2016�~8��16��
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_AREAOFEFFECT_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_AREAOFEFFECT_H_

#include "class/game/ageOfCube/map/attack/Attack.h"

namespace AOC {

class AreaOfEffect : public Attack{
public:
	AreaOfEffect();
	virtual ~AreaOfEffect();
	virtual Attack* clone(){
		return new AreaOfEffect();
	}
	virtual std::string get_name(){return "AOE";}
	virtual void explode();
protected:
	virtual void draw_attack();
	virtual void attack_update();
	virtual void explode_target(Unit* unit);
	int explode_timer;
	int max_explode_time;
	bool exploded_render;
	int timer;
	int type;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_AREAOFEFFECT_H_ */
