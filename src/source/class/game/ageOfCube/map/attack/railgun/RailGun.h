#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_RAILGUN_RAILGUN_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_RAILGUN_RAILGUN_H_

#include "class/game/ageOfCube/map/attack/weapon/Weapon.h"

namespace AOC {

class RailGun: public Weapon {
public:
	RailGun();
	virtual ~RailGun();
	virtual Weapon* clone(){
		return new RailGun();
	}
	virtual std::string get_name(){
		return "RailGun";
	}
	virtual std::string get_attack_type(){
		return "Bullet";
	}
protected:
	virtual void weapon_update();
	virtual void draw_weapon();
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_RAILGUN_RAILGUN_H_ */
