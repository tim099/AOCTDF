#include "class/game/chessMaster/piece/basicRule/BasicRuleCreator.h"
#include "class/game/chessMaster/piece/basicRule/MoveStraight.h"
#include "class/game/chessMaster/piece/basicRule/MoveTo.h"
#include "class/game/chessMaster/piece/basicRule/IF.h"
namespace CM {

BasicRuleCreator::BasicRuleCreator() {
	push(new MoveStraight());
	push(new MoveTo());
	push(new IF());

}
BasicRuleCreator::~BasicRuleCreator() {

}
BasicRule* BasicRuleCreator::create(std::string type_name){
	if (!creator.get(type_name)) {
		std::cerr << "BasicRule name:" << type_name
				<< " not exist in this BasicRuleCreator" << std::endl;
		return 0;
	}
	return creator.get(type_name)->clone();
}
void BasicRuleCreator::push(BasicRule* obj){
	creator.push(obj->get_name(),obj);
}
} /* namespace CM */
