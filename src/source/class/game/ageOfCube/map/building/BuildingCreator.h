#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_BUILDINGCREATOR_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_BUILDINGCREATOR_H_

#include "class/game/ageOfCube/map/building/Building.h"
#include "class/tim/map/MapContainer.h"
#include "class/tim/globalObject/Singleton.h"
#include "class/tim/globalObject/GlobalObject.h"

namespace AOC {

class BuildingCreator : public Tim::GlobalObject<BuildingCreator> {
public:
	BuildingCreator();
	virtual ~BuildingCreator();
	Building* create(std::string type_name);
	std::vector<std::string> get_buildings_name();
protected:
	void push(Building* obj);
	Tim::MapContainer<std::string,Building>creator;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_BUILDING_BUILDINGCREATOR_H_ */
