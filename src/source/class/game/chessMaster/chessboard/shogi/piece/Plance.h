#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_PIECE_PLANCE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_PIECE_PLANCE_H_
#include "class/game/chessMaster/chessboard/shogi/piece/ShogiPiece.h"
namespace CM {
namespace shogi {

class Plance : public ShogiPiece{
public:
	Plance();
	virtual ~Plance();
	virtual void next_step(CM::Board<short int> *chess_board,
			int x,int y,Tim::vector<CM::Step> &next_step,int player);
};

} /* namespace shogi */
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_PIECE_PLANCE_H_ */
