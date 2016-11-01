#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_OTHELLO_OTHELLORULE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_OTHELLO_OTHELLORULE_H_

#include "class/game/chessMaster/chessboard/rule/Rule.h"

namespace CM {

class OthelloRule: public Rule {
public:
	OthelloRule();
	virtual ~OthelloRule();
	virtual int check_winner(CM::Board<short int> *chess_board);
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_OTHELLO_OTHELLORULE_H_ */
