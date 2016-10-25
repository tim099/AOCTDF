#ifndef SOURCE_CLASS_TIM_MAP_MAPTREE_H_
#define SOURCE_CLASS_TIM_MAP_MAPTREE_H_
#include "class/tim/map/MapContainer.h"
namespace Tim {
template <class maptype,class type>
class MapTree {
public:
	MapTree();
	virtual ~MapTree();
	std::string get_name()const;
	void set_name(std::string name);

	type *get(std::string path);
	void push(std::string path,type* obj);
	bool find(std::string path);



	//remove a map from this
	void remove_map(maptype* map);

	void push_map(maptype* map);//push a map into this
	maptype* get_map(std::string name);//get map by name

	void push_dir(MapTree *dir);//push a dir into this
	MapTree* get_dir(std::string name);//get Dir by name
protected:
	Tim::MapContainer<std::string,maptype>maps;
	Tim::MapContainer<std::string,MapTree<maptype,type> >dirs;
	std::string name;
};

} /* namespace Tim */
#include "class/tim/map/MapTree.cpp"
#endif /* SOURCE_CLASS_TIM_MAP_MAPTREE_H_ */
