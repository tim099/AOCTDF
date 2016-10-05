#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_CONDITION_CHECKBOARD_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_CONDITION_CHECKBOARD_H_
#include "class/game/chessMaster/piece/basicRule/condition/Condition.h"
namespace CM {
static const int type_empty=1;
static const int type_enemy=2;
static const int type_player=3;
static const int type_piece=4;
class CheckBoard : public Condition{
public:
	CheckBoard();
	virtual ~CheckBoard();
	virtual Condition* clone(){
		return new CheckBoard();
	}
	virtual std::string get_name(){
		return "CheckBoard";
	}
	virtual bool get_condition(CM::Board<short int> *chess_board,
				int x,int y,int player);
	virtual void draw(int x,int y);
	virtual void draw_UI();
	virtual void update();
	virtual void update_UI();

protected:
	virtual void save_condition(FILE* file);
	virtual void load_condition(FILE* file);
	void set_delta(int dx,int dy);
	int dx,dy;
	int type;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_CONDITION_CHECKBOARD_H_ */
