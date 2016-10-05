#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CONDITION_GRAVITYCONDITION_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CONDITION_GRAVITYCONDITION_H_
#include "class/game/ageOfCube/map/condition/Condition.h"
#include "class/tim/math/vec3.h"
namespace AOC {
class Minion;
class GravityCondition : public Condition{
public:
	GravityCondition(int total_time,int peroiod,Unit *owner,math::vec3<double> pos,double a);
	virtual ~GravityCondition();
	virtual void takeEffect();
	virtual void endEffect();
	Minion *owner_minion;
	math::vec3<double> pos;
	double a;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_CONDITION_GRAVITYCONDITION_H_ */
