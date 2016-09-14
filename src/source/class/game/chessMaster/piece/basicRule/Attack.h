#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_ATTACK_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_ATTACK_H_
#include "class/game/chessMaster/piece/basicRule/BasicRule.h"
namespace CM {

class Attack : public BasicRule{
public:
	Attack();
	virtual ~Attack();
	virtual std::string get_name(){
		return "Attack";
	}
	virtual Attack* clone(){
		return new Attack();
	}

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

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_ATTACK_H_ */
