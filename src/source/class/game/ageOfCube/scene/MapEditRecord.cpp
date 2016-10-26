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
	unit = 0;
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

void MapEditRecord::setUnit(Unit *_unit){
	unit = _unit;
	unit_name = unit->get_name();
	unit_pos = unit->get_pos_int();
}

bool MapEditRecord::undo(Map *map){
	if(unit == 0){
		return undoCube(map);
	}
	else{
		return undoUnit(map);
	}
}

bool MapEditRecord::redo(Map *map){
	if(unit == 0){
		return redoCube(map);
	}
	else{
		return redoUnit(map);
	}
}

bool MapEditRecord::undoCube(Map *map){
	glm::vec3 cube_pos;
	int cube_type;
	for(unsigned int i=0; i<changed_cubes.size(); i++){
		cube_pos = changed_cubes.at(i);
		cube_type = previous_type.at(i);
		map->set_cube_type(cube_pos.x, cube_pos.y, cube_pos.z, cube_type);
	}
	return true;
}

bool MapEditRecord::undoUnit(Map *map){
	unit->set_hp(0);
	return true;
}

bool MapEditRecord::redoCube(Map *map){
	glm::vec3 cube_pos;
	for(unsigned int i=0; i<changed_cubes.size(); i++){
		cube_pos = changed_cubes.at(i);
		map->set_cube_type(cube_pos.x, cube_pos.y, cube_pos.z, after_type);
	}
	return true;
}

bool MapEditRecord::redoUnit(Map *map){
	BuildingCreator* creator=BuildingCreator::get_cur_object();
	Building* constructing_building = creator->create(unit_name);
	constructing_building->set_pos(unit_pos.x, unit_pos.y, unit_pos.z);
	if(constructing_building->create_building()){
		unit = constructing_building;
	}
	else{
		std::cerr<<"create building fail "<<std::endl;
		return false;
	}
	return true;
}

void MapEditRecord::clear(){
	changed_cubes.clear();
}

} /* namespace AOC */
