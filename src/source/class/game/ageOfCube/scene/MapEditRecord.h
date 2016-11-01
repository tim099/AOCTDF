/*
 * MapEditRecord.h
 *
 *  Created on: 2016¦~10¤ë25¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_MAPEDITRECORD_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_MAPEDITRECORD_H_

#include "class/game/ageOfCube/map/Map.h"

namespace AOC {

class MapEditRecord {
public:
	MapEditRecord();
	virtual ~MapEditRecord();
	void push(int _x, int _y, int _z, int _type);
	void setType(int _type);
	void setUnit(Unit *_unit);
	bool undo(Map *map);
	bool redo(Map *map);
	void clear();

private:
	bool undoCube(Map *map);
	bool undoUnit(Map *map);
	bool redoCube(Map *map);
	bool redoUnit(Map *map);
	Unit *unit;
	std::string unit_name;
	math::vec3<int> unit_pos;
	std::vector<glm::vec3> changed_cubes;
	std::vector<int> previous_type;
	int after_type;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_MAPEDITRECORD_H_ */
