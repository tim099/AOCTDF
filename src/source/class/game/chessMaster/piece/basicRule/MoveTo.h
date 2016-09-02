#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_MOVETO_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_MOVETO_H_

#include "class/game/chessMaster/piece/basicRule/BasicRule.h"

namespace CM {

class MoveTo: public BasicRule {
public:
	MoveTo();
	virtual ~MoveTo();
	virtual std::string get_name(){
		return "MoveTo";
	}
	///*
	virtual BasicRule* clone(){
		return new MoveTo();
	}
	//*/
	virtual void save(FILE* file);
	virtual void load(FILE* file);
	virtual void get_next_step(CM::Board<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player);

	virtual void draw_UI();
	virtual void update_UI();
	void set_delta(int dx,int dy);
	int dx,dy;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_MOVETO_H_ */