/*
 * MapEditor.h
 *
 *  Created on: 2016¦~9¤ë28¤é
 *      Author: LukeWu
 */

#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_MAPEDITOR_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_MAPEDITOR_H_

#include <deque>
#include "class/game/ageOfCube/scene/MapEditRecord.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/tim/math/vec3.h"


namespace Display{
	class LightControl;
	class CubeLight;
}
namespace AOC {

class MapEditor {
public:
	MapEditor();
	virtual ~MapEditor();
	void setMap(Map *_map){map = _map;}
	void set_cube_type(int x,int y,int z,int type);
	bool build(Building *building);
	Display::CubeLight *highlightCube(int x, int y, int z);
	void highlightSelectedCubes(Display::LightControl *lc);
	void undo();
	void redo();

	glm::ivec3 select_range;
	bool destruct_mode;
private:
	Map *map;
	int undo_count;
	std::deque <MapEditRecord> edit_records;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_MAPEDITOR_H_ */
