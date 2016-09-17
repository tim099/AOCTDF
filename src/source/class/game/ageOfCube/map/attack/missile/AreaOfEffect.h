/*
 * AreaOfEffect.h
 *
 *  Created on: 2016¦~8¤ë16¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_AREAOFEFFECT_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_AREAOFEFFECT_H_

#include "class/game/ageOfCube/map/attack/Attack.h"

namespace AOC {

class AreaOfEffect : public Attack{
public:
	AreaOfEffect();
	AreaOfEffect(AreaOfEffect *aoe);
	virtual ~AreaOfEffect();
	virtual Attack* clone(){
		return new AreaOfEffect(this);
	}
	virtual std::string get_name(){return "AOE";}
	virtual void explode();
protected:
	virtual void draw_attack();
	virtual void attack_update();
	int explode_timer;
	bool exploded_render;
	int timer;
	int type;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_AREAOFEFFECT_H_ */
