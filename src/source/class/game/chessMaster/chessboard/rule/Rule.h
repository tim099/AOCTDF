#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RULE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RULE_H_
#include "class/game/chessMaster/common.h"
#include "class/tim/lua/Lua.h"
#include "class/game/chessMaster/chessboard/Board.h"
#include "class/tim/thread/mutex/Mutex.h"
#include "class/display/UI/UI.h"
#include <string>
namespace CM {

class Rule {
public:
	Rule();
	virtual ~Rule();
	virtual std::string get_name(){
		return "Rule";
	}
	virtual Rule* clone(){
		return new Rule();
	}

	virtual void init_UI(){}
	virtual void update_UI(){}
	virtual void set_UI(){}
	virtual void draw_UI(){}

	void load_rule(std::string path);

	virtual void save(std::ostream &os){}
	virtual void load(std::istream &is){}

	virtual int check_winner(CM::Board<short int> *chess_board);
	Tim::Lua *rule;
	Tim::Mutex rule_mutex;
	UI::UI *ui;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RULE_H_ */
