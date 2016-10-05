#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_CONDITION_CONDITION_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_CONDITION_CONDITION_H_
#include <string>
#include "class/game/chessMaster/common.h"
#include "class/game/chessMaster/chessboard/Board.h"
#include "class/display/UI/UI.h"
namespace CM {

class Condition {
public:
	Condition();
	virtual ~Condition();
	virtual Condition* clone()=0;
	virtual std::string get_name(){
		return "Condition";
	}
	virtual void save(FILE* file);
	virtual void load(FILE* file);
	virtual void draw(int x,int y){}
	virtual void draw_UI(){}
	virtual void update(){}
	virtual void update_UI(){}
	virtual bool get_condition(CM::Board<short int> *chess_board,
			int x,int y,int player)=0;

	bool do_and;//and operator to next condition
protected:
	virtual void save_condition(FILE* file){}
	virtual void load_condition(FILE* file){}
	UI::UI *ui;

};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_CONDITION_CONDITION_H_ */
