#ifndef SOURCE_CLASS_TIM_MAP_MAPTREE_CPP_
#define SOURCE_CLASS_TIM_MAP_MAPTREE_CPP_
#include "class/tim/map/MapTree.h"
#include "class/tim/string/String.h"
#include <iostream>
namespace Tim {
template <class maptype,class type>
MapTree<maptype,type>::MapTree() {
	default_map=0;
}
template <class maptype,class type>
MapTree<maptype,type>::~MapTree() {

}
template <class maptype,class type>
std::string MapTree<maptype,type>::get_name() const {
	return name;
}
template <class maptype,class type>
void MapTree<maptype,type>::set_name(std::string _name) {
	name = _name;
}
template <class maptype,class type>
void MapTree<maptype,type>::push(std::string obj_path,type* obj){
	std::vector<std::string> path;
	Tim::String::split(obj_path, "/", path);
	if (path.size() == 2) {
		maptype *obj_map = get_map(path.at(0));
		if (obj_map) {
			obj_map->push(obj);
		}
	} else if (path.size() > 2) {
		MapTree<maptype,type>* dir=get_dir(path.at(0));
		if(dir){
			std::string new_path;
			for(unsigned i=1;i<path.size();i++){
				new_path+="/"+path.at(i);
			}
			return dir->push(new_path,obj);
		}
	} else if (path.size()==1&&default_map) {
		default_map->push(obj);
	}
}
template <class maptype,class type>
type *MapTree<maptype,type>::get(std::string obj_path){
	std::vector<std::string> path;
	Tim::String::split(obj_path, "/", path);
	if (path.size() == 2) {
		maptype *obj_map = get_map(path.at(0));
		if (obj_map) {
			return obj_map->get(path.at(1));
		}
	} else if (path.size() > 2) { //bigger than 2
		MapTree<maptype,type>* dir=get_dir(path.at(0));
		if(dir){
			std::string new_path;
			for(unsigned i=1;i<path.size();i++){
				new_path+="/"+path.at(i);
			}
			return dir->get(new_path);
		}
	} else if (path.size()==1&&default_map) {
		return default_map->get(path.at(0));
	}
	//std::cerr<<"Map tree can't find object:"<<obj_path<<std::endl;
	return 0;
}
template <class maptype,class type>
bool  MapTree<maptype,type>::find(std::string obj_path){
	std::vector<std::string> path;
	Tim::String::split(obj_path, "/", path);
	if (path.size() == 2) {
		maptype *obj_map = get_map(path.at(0));
		if (obj_map) {
			return obj_map->find(path.at(1));
		}
	} else if (path.size() > 2) { //bigger than 2
		MapTree<maptype,type>* dir=get_dir(path.at(0));
		if(dir){
			std::string new_path;
			for(unsigned i=1;i<path.size();i++){
				new_path+="/"+path.at(i);
			}
			return dir->find(new_path);
		}
	} else if (path.size()==1&&default_map) {
		return default_map->find(path.at(0));
	}
	return 0;
}

template <class maptype,class type>
void MapTree<maptype,type>::push_map(maptype* map){
	maps.push(map->get_name(),map);
}
template <class maptype,class type>
void MapTree<maptype,type>::remove_map(maptype* map){
	if(map==default_map){
		default_map=0;
	}
	maps.remove(map->get_name());
}
template <class maptype,class type>
maptype* MapTree<maptype,type>::get_map(std::string name){
	return maps.get(name);
}
template <class maptype,class type>
void MapTree<maptype,type>::push_dir(MapTree<maptype,type> *dir){
	dirs.push(dir->get_name(),dir);
}
template <class maptype,class type>
MapTree<maptype,type>* MapTree<maptype,type>::get_dir(std::string name){
	return dirs.get(name);
}


} /* namespace Tim */
#endif /* SOURCE_CLASS_TIM_MAP_MAPTREE_CPP_ */
