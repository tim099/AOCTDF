#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_PIECE_PROOK_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_PIECE_PROOK_H_
#include "class/game/chessMaster/chessboard/shogi/piece/ShogiPiece.h"
namespace CM {
namespace shogi {

class Prook : public ShogiPiece{
public:
	Prook();
	virtual ~Prook();
	virtual void next_step(CM::Board<short int> *chess_board,
			int x,int y,Tim::vector<CM::Step> &next_step,int player);
};

} /* namespace shogi */
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_PIECE_PROOK_H_ */
