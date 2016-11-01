#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RULE_RULECREATOR_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RULE_RULECREATOR_H_
#include "class/game/chessMaster/chessboard/rule/Rule.h"
#include "class/tim/map/MapContainer.h"
#include "class/tim/globalObject/Singleton.h"
namespace CM {

class RuleCreator : public Tim::Singleton<RuleCreator>{
public:
	RuleCreator();
	virtual ~RuleCreator();
	Rule* create(std::string type_name);
protected:
	void push(Rule* obj);
	Tim::MapContainer<std::string,Rule>creator;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RULE_RULECREATOR_H_ */
