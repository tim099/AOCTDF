#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_DARKCHESS_PIECE_ADVISOR_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_DARKCHESS_PIECE_ADVISOR_H_
#include "class/game/chessMaster/piece/Piece.h"
namespace CM {
namespace darkChess {

class Advisor : public Piece {
public:
	Advisor();
	virtual ~Advisor();
	inline bool bound_check(const int& x,const int &y){
		if(x>=0&&y>=0&&x<8&&y<4){
			return true;
		}
		return false;
	}
	virtual void next_step(CM::Board<short int> *chess_board,
			int x,int y,Tim::vector<CM::Step> &next_step,int player);
};

} /* namespace darkChess */
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_DARKCHESS_PIECE_ADVISOR_H_ */
