/*
 * StaticField.h
 *
 *  Created on: 2016¦~8¤ë13¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_FIELD_STATICFIELD_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_FIELD_STATICFIELD_H_

#include <class/game/ageOfCube/field/Field.h>

namespace AOC {

class StaticField: public Field {
public:
	StaticField();
	virtual ~StaticField();
	virtual void update();
	virtual void pause_update();//update for game state is pause
	virtual void draw(Display::Draw *draw,Display::Camera *camera,Tim::ThreadPool* threadpool);
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_FIELD_STATICFIELD_H_ */
