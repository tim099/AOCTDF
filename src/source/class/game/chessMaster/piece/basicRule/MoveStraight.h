#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_MOVESTRAIGHT_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_MOVESTRAIGHT_H_
#include "class/game/chessMaster/piece/basicRule/BasicRule.h"

namespace CM {

class MoveStraight : public BasicRule{
public:
	MoveStraight();
	virtual ~MoveStraight();
	virtual std::string get_name(){
		return "MoveStraight";
	}
	virtual BasicRule* clone(){
		return new MoveStraight();
	}
	virtual void save(FILE* file);
	virtual void load(FILE* file);
	void set_delta(int dx,int dy);
	virtual void get_next_step(CM::Board<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player);

	virtual void draw_UI();
	virtual void update_UI();
protected:
	int dx,dy;

};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_MOVESTRAIGHT_H_ */
