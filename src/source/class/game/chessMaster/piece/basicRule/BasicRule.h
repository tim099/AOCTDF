#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_H_
#include <string>
#include <vector>
#include "class/game/chessMaster/chessboard/Board.h"
#include "class/tim/array/vector.h"
#include "class/game/chessMaster/piece/Step.h"
#include "class/game/chessMaster/common.h"
#include "class/display/UI/UI.h"
namespace CM {

class BasicRule {
public:
	BasicRule();
	virtual ~BasicRule();
	virtual std::string get_name(){
		return "BasicRule";
	}
	virtual BasicRule* clone(){
		return 0;
	}
	virtual void save(FILE* file){}
	virtual void load(FILE* file){}
	virtual void draw_UI(){}
	virtual void update_UI(){}
	void next_step(CM::Board<short int> *chess_board,
			int x,int y,Tim::vector<CM::Step> &next_step);
	virtual void get_next_step(CM::Board<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player)=0;

	UI::UI *ui;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_BASICRULE_H_ */
