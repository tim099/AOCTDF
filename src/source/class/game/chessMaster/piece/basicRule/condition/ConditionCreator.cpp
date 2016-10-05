#include "class/game/chessMaster/piece/basicRule/condition/ConditionCreator.h"
#include "class/game/chessMaster/piece/basicRule/condition/CheckBoard.h"
namespace CM {

ConditionCreator::ConditionCreator() {
	push(new CheckBoard());
}
ConditionCreator::~ConditionCreator() {

}
Condition* ConditionCreator::create(std::string type_name){
	if (!creator.get(type_name)) {
		std::cerr << "Condition name:" << type_name
				<< " not exist in this ConditionCreator" << std::endl;
		return 0;
	}
	return creator.get(type_name)->clone();
}
void ConditionCreator::push(Condition* obj){
	creator.push(obj->get_name(),obj);
}
} /* namespace CM */
