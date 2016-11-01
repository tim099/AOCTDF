#include "class/game/chessMaster/chessboard/rule/RuleCreator.h"
#include "class/game/chessMaster/chessboard/rule/Checkmate.h"
namespace CM {

RuleCreator::RuleCreator() {
	push(new Rule());
	push(new Checkmate());
}
RuleCreator::~RuleCreator() {

}
Rule* RuleCreator::create(std::string type_name){
	if (!creator.get(type_name)) {
		std::cerr << "Rule name:" << type_name
				<< " not exist in this Creator" << std::endl;
		return 0;
	}
	return creator.get(type_name)->clone();
}
void RuleCreator::push(Rule* obj){
	creator.push(obj->get_name(),obj);
}
} /* namespace CM */
