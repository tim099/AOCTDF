/*
 * MapEditRecord.cpp
 *
 *  Created on: 2016¦~10¤ë25¤é
 *      Author: LukeWu
 */

#include "class/game/ageOfCube/scene/MapEditRecord.h"

namespace AOC {

MapEditRecord::MapEditRecord() {
	// TODO Auto-generated constructor stub
	is_building = false;
	after_type = 0;
}

MapEditRecord::~MapEditRecord() {
	// TODO Auto-generated destructor stub
}

void MapEditRecord::push(int _x, int _y, int _z, int _type){
	changed_cubes.push_back(glm::vec3(_x, _y, _z));
	previous_type.push_back(_type);
}

void MapEditRecord::setType(int _type){
	after_type = _type;
}

void MapEditRecord::undo(Map *map){
	glm::vec3 cube_pos;
	int cube_type;
	for(unsigned int i=0; i<changed_cubes.size(); i++){
		cube_pos = changed_cubes.at(i);
		cube_type = previous_type.at(i);
		map->set_cube_type(cube_pos.x, cube_pos.y, cube_pos.z, cube_type);
	}
}

void MapEditRecord::redo(Map *map){
	glm::vec3 cube_pos;
	for(unsigned int i=0; i<changed_cubes.size(); i++){
		cube_pos = changed_cubes.at(i);
		map->set_cube_type(cube_pos.x, cube_pos.y, cube_pos.z, after_type);
	}
}

void MapEditRecord::clear(){
	changed_cubes.clear();
}

} /* namespace AOC */
