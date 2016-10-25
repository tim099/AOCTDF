#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_MINION_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_MINION_H_

#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/physic/RigidBody.h"
#include "class/tim/math/Position.h"
#include "class/game/ageOfCube/map/ai/search/finder/FindPath.h"
#include "class/tim/pointer/SmartPointer.h"
#include "class/game/ageOfCube/map/minion/MinionAI.h"

namespace Display{
	class DrawObject;
}
namespace AOC {

class Minion: public Unit{
	static constexpr float gravity=-0.003f;
public:
	Minion();
	virtual ~Minion();
	virtual void minion_pre_init(){}
	virtual Minion* clone()=0;


	void save(FILE * file);
	void load(FILE * file);
	void create_minion();
	void draw();
	void move_to(math::vec3<double> target,double vel);

	virtual math::vec3<double> get_size(){
		return math::vec3<double>(rigid_body.radius*2.0,rigid_body.radius*2.0,rigid_body.radius*2.0);
	}
	virtual math::vec3<double> get_vel(){
		return rigid_body.vel;
	}
	virtual double get_attack_size();
	virtual math::vec3<double> get_rotate();
	virtual math::vec3<double> get_pos(){return rigid_body.pos;}
	virtual math::vec3<int> get_pos_int();
	virtual math::vec3<double> get_speed(){return rigid_body.vel;}
	inline void set_pos(math::vec3<double> pos){rigid_body.pos=pos;}
	inline void set_vel(math::vec3<double> vel){rigid_body.vel=vel;}
	inline void set_size(double size){rigid_body.radius=0.5*size;}
protected:
	virtual void minion_create(){}
	virtual void unit_update();
	virtual void save_minion(FILE * file){}
	virtual void load_minion(FILE * file){}
	virtual void draw_minion()=0;
	virtual void minion_update(){}
	virtual void miniod_collide(entity::Entity* entity){};
	virtual void miniod_be_collide(entity::Entity* entity){miniod_collide(entity);};

	void attack_main_tower();
	void AI_update();
	void draw_hp();


	void move();
	void find_path();
	void moving();

	MinionAI *ai;
	math::Position dp_pos;
	physic::RigidBody rigid_body;
	Tim::SmartPointer<AI::search::Finder> *finder;
	bool minion_created;
	int stuck_timer,stuck_times,colli_timer;
	int timer;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_MINION_H_ */
