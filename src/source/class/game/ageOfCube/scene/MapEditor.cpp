/*
 * MapEditor.cpp
 *
 *  Created on: 2016¦~9¤ë28¤é
 *      Author: LukeWu
 */

#include "class/game/ageOfCube/scene/MapEditor.h"

namespace AOC {

MapEditor::MapEditor() {
	map = 0;
	select_range = glm::ivec3(1, 1, 1);
}

MapEditor::~MapEditor() {

}
void MapEditor::set_cube_type(int x,int y,int z,int type){
	int cur_x, cur_y, cur_z;
	if(!map){
		return;
	}
	for(int i=0; i<select_range.y; i++){
		cur_y = y+i;
		for(int j=0; j<select_range.x; j++){
			cur_x = x-(select_range.x/2)+j;
			for(int k=0; k<select_range.z; k++){
				cur_z = z-(select_range.z/2)+k;
				map->set_cube_type(cur_x, cur_y, cur_z, type);
			}
		}
	}
}

Display::CubeLight* MapEditor::highlightCube(int x, int y, int z){
	Display::CubeLight*cl=new Display::CubeLight();
	cl->size=1.01f*Map::CUBE_SIZE;
	cl->pos=glm::vec3((x+0.5f)*Map::CUBE_SIZE,
			  (y+0.5f)*Map::CUBE_SIZE,
			  (z+0.5f)*Map::CUBE_SIZE);
	return cl;
}

void MapEditor::highlightSelectedCubes(Display::LightControl *lc){
	//int cur_x, cur_y, cur_z;
	int x=map->selected_on.x, y=map->selected_on.y, z=map->selected_on.z;
	/*for(int i=0; i<select_range.y; i++){
		cur_y = y+i;
		for(int j=0; j<select_range.x; j++){
			cur_x = x-(select_range.x/2)+j;
			for(int k=0; k<select_range.z; k++){
				cur_z = z-(select_range.z/2)+k;
				lc->push_light(highlightCube(cur_x, cur_y, cur_z));
			}
		}
	}*/
	Display::CubeLight*cl=new Display::CubeLight();
	cl->size=1.01f*Map::CUBE_SIZE*select_range.x;
	cl->color=glm::vec3(0.0f, 1.0f, 0.0f);
	cl->pos=glm::vec3((x+0.5f)*Map::CUBE_SIZE,
			  (y+0.5f)*Map::CUBE_SIZE,
			  (z+0.5f)*Map::CUBE_SIZE);
	lc->push_temp_light(cl);
}

} /* namespace AOC */
