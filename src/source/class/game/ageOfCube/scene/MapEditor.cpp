/*
 * MapEditor.cpp
 *
 *  Created on: 2016¦~9¤ë28¤é
 *      Author: LukeWu
 */

#include "class/game/ageOfCube/scene/MapEditor.h"
#include "class/display/light/LightControl.h"
#include "class/display/light/CubeLight.h"
namespace AOC {

MapEditor::MapEditor() {
	map = 0;
	destruct_mode=false;
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
	int x,y,z;
	Display::CubeLight*cl=new Display::CubeLight();
	if(!destruct_mode){
		cl->color=glm::vec3(0.0f, 0.8f, 0.0f);
		x=map->selected_on.x;y=map->selected_on.y;z=map->selected_on.z;
	}else{
		cl->color=glm::vec3(0.8f, 0.0f, 0.0f);
		x=map->selected_cube.x;y=map->selected_cube.y;z=map->selected_cube.z;
	}


	cl->cube_size.x=1.01f*Map::CUBE_SIZE*select_range.x;
	cl->cube_size.y=1.01f*Map::CUBE_SIZE*select_range.y;
	cl->cube_size.z=1.01f*Map::CUBE_SIZE*select_range.z;

	cl->pos=glm::vec3((x+0.5*(select_range.x%2))*Map::CUBE_SIZE,
			  (y+0.5f*select_range.y)*Map::CUBE_SIZE,
			  (z+0.5*(select_range.z%2))*Map::CUBE_SIZE);
	lc->push_temp_light(cl);
}

} /* namespace AOC */
