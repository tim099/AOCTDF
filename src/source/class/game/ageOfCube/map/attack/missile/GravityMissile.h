#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_GRAVITYMISSILE_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_GRAVITYMISSILE_H_
#include "class/game/ageOfCube/map/attack/missile/Missile.h"

namespace AOC {

class GravityMissile : public Missile {
public:
	GravityMissile();
	virtual ~GravityMissile();

	virtual Attack* clone(){
		return new GravityMissile();
	}
	virtual std::string get_name(){
		return std::string("GravityMissile");
	}
protected:
	virtual void draw_attack();
	virtual Display::DrawObject *get_missile_drawobj();
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_GRAVITYMISSILE_H_ */
