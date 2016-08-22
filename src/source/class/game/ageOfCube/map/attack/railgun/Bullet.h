#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_RAILGUN_BULLET_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_RAILGUN_BULLET_H_

#include "class/game/ageOfCube/map/attack/Attack.h"

namespace AOC {

class Bullet: public Attack {
public:
	Bullet();
	virtual ~Bullet();

	virtual Attack* clone(){
		return new Bullet();
	}
	virtual std::string get_name(){
		return std::string("Bullet");
	}
	virtual void save_attack(FILE* file);
	virtual void load_attack(FILE* file);
	virtual void draw_attack();
	virtual void attack_update();
protected:
	virtual Display::DrawObject *get_bullet_drawobj();
	virtual void fire();
	void explode();
	int explode_timer;
	int timer;
	double speed;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_ATTACK_RAILGUN_BULLET_H_ */
