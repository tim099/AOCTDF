#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_CONDITION_CONDITIONCREATOR_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_CONDITION_CONDITIONCREATOR_H_
#include "class/tim/map/MapContainer.h"
#include "class/tim/globalObject/Singleton.h"
#include "class/game/chessMaster/piece/basicRule/condition/Condition.h"
namespace CM {

class ConditionCreator : public Tim::Singleton<ConditionCreator>{
public:
	ConditionCreator();
	virtual ~ConditionCreator();
	Condition* create(std::string type_name);
protected:
	void push(Condition* obj);
	Tim::MapContainer<std::string,Condition>creator;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_CONDITION_CONDITIONCREATOR_H_ */
