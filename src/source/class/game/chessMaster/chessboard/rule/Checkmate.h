#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RULE_CHECKMATE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RULE_CHECKMATE_H_
#include "class/game/chessMaster/chessboard/rule/Rule.h"
namespace CM {

class Checkmate : public Rule{
public:
	Checkmate();
	virtual ~Checkmate();
	virtual std::string get_name(){
		return "Checkmate";
	}
	virtual Rule* clone(){
		return new Checkmate();
	}

	virtual void init_UI();
	virtual void update_UI();
	virtual void set_UI();
	virtual void draw_UI();

	virtual void save(std::ostream &os);
	virtual void load(std::istream &is);

	virtual int check_winner(CM::Board<short int> *chess_board);
	void set_king(std::string name);
	int king;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_RULE_CHECKMATE_H_ */
