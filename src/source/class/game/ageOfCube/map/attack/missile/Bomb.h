/*
 * Bomb.h
 *
 *  Created on: 2016¦~8¤ë15¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_BOMB_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_BOMB_H_

#include "class/game/ageOfCube/map/attack/missile/Missile.h"

namespace AOC {

class Bomb: public Missile {
public:
	Bomb();
	Bomb(Bomb* cube);
	virtual ~Bomb();
	virtual Attack* clone(){
		return new Bomb(this);
	}
	virtual std::string get_name(){
		return std::string("Bomb");
	}
	virtual void explode();
protected:
	virtual void draw_attack();
	virtual Display::DrawObject *get_missile_drawobj();
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_MISSILE_BOMB_H_ */
