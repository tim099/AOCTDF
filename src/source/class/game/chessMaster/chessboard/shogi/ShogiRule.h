#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_SHOGIRULE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_SHOGIRULE_H_
#include "class/game/chessMaster/chessboard/rule/Rule.h"
namespace CM {
namespace shogi {
class ShogiRule : public Rule{
public:
	ShogiRule();
	virtual ~ShogiRule();
	virtual int check_winner(CM::Board<short int> *chess_board);
};
}
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_SHOGIRULE_H_ */
