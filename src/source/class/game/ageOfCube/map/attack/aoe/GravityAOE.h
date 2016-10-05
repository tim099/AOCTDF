#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_AOE_GRAVITYAOE_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_AOE_GRAVITYAOE_H_
#include "class/game/ageOfCube/map/attack/aoe/AreaOfEffect.h"
namespace AOC {

class GravityAOE : public AreaOfEffect{
public:
	GravityAOE();
	virtual ~GravityAOE();
	virtual Attack* clone(){
		return new GravityAOE();
	}
	virtual std::string get_name(){return "GravityAOE";}
	virtual void explode_target(Unit* unit);
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_AOE_GRAVITYAOE_H_ */
