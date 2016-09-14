#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_DARKCHESS_DARKCHESSRULE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_DARKCHESS_DARKCHESSRULE_H_
#include "class/game/chessMaster/chessboard/Rule.h"
namespace CM {
namespace darkChess {
class DarkChessRule : public Rule{
public:
	DarkChessRule();
	virtual ~DarkChessRule();
	virtual int check_winner(CM::Board<short int> *chess_board);
};
}
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_DARKCHESS_DARKCHESSRULE_H_ */
