#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_IF_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_IF_H_
#include "class/game/chessMaster/piece/basicRule/BasicRule.h"
#include "class/game/chessMaster/piece/basicRule/condition/Condition.h"
namespace CM {

class IF : public BasicRule{
public:
	IF();
	virtual ~IF();
	virtual std::string get_name(){
		return "IF";
	}
	virtual BasicRule* clone(){
		return new IF();
	}
	virtual bool get_remove_rule();
	virtual bool get_edit_done();
	virtual void save(FILE* file);
	virtual void load(FILE* file);
	virtual void get_next_step(CM::Board<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player);

	virtual void deselected();
	virtual void draw_UI();
	virtual void update();
	virtual void update_UI();
	void add_rule(std::string rule_name);
	void add_condition(std::string rule_name);
	void get_rule_names(std::vector<std::string> &names);
	void get_condition_names(std::vector<std::string> &names);
	virtual void draw_rule(CM::Board<short int> *chess_board,
			int x,int y);
	bool true_mode;
	BasicRule* selected_rule;
	Condition* selected_condition;
	std::vector<Condition*> conditions;
	std::vector<BasicRule*> true_rules;
	std::vector<BasicRule*> false_rules;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_IF_H_ */
