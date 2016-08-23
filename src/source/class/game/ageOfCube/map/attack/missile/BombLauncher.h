/*
 * BombLauncher.h
 *
 *  Created on: 2016¦~8¤ë15¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_BOMBLAUNCHER_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_BOMBLAUNCHER_H_

#include "class/game/ageOfCube/map/attack/missile/MissileLauncher.h"

namespace AOC {

class BombLauncher: public MissileLauncher {
public:
	BombLauncher();
	virtual ~BombLauncher();
	virtual Weapon* clone(){
		return new BombLauncher();
	}
	virtual std::string get_name(){
		return "BombLauncher";
	}
	virtual std::string get_attack_type(){
		return "Bomb";
	}
protected:
	virtual void draw_weapon();
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_BOMBLAUNCHER_H_ */
