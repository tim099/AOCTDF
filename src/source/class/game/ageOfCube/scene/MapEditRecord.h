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
	void undo(Map *map);
	void redo(Map *map);
	void clear();

	bool is_building;
	std::vector<glm::vec3> changed_cubes;
	std::vector<int> previous_type;
	int after_type;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_MAPEDITRECORD_H_ */
