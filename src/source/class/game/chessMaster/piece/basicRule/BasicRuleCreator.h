#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULECREATOR_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULECREATOR_H_
#include "class/game/chessMaster/piece/basicRule/BasicRule.h"
#include "class/tim/map/MapContainer.h"
#include "class/tim/globalObject/Singleton.h"
namespace CM {

class BasicRuleCreator : public Tim::Singleton<BasicRuleCreator>{
public:
	BasicRuleCreator();
	virtual ~BasicRuleCreator();
	BasicRule* create(std::string type_name);
protected:
	void push(BasicRule* obj);
	Tim::MapContainer<std::string,BasicRule>creator;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULECREATOR_H_ */
