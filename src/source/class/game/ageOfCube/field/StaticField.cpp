/*
 * StaticField.cpp
 *
 *  Created on: 2016¦~8¤ë13¤é
 *      Author: LukeWu
 */

#include "class/game/ageOfCube/field/StaticField.h"

namespace AOC {

StaticField::StaticField() {
	// TODO Auto-generated constructor stub

}

StaticField::~StaticField() {
	// TODO Auto-generated destructor stub
}

void StaticField::draw(Display::Draw *draw,Display::Camera *camera,Tim::ThreadPool* threadpool){
	map->draw(draw,camera,threadpool);
	draw_back_ground();
}

void StaticField::update(){

	timer.tic(1);
	map->update(&timer);
}
void StaticField::pause_update(){
}

} /* namespace AOC */
