#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_OTHELLO_PIECE_OTHELLOSKIPSTONE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_OTHELLO_PIECE_OTHELLOSKIPSTONE_H_

#include "class/game/chessMaster/piece/Piece.h"

namespace CM {

class OthelloSkipStone: public Piece {
public:
	OthelloSkipStone();
	virtual ~OthelloSkipStone();
	virtual void next_step(CM::Board<short int> *chess_board,
			int x,int y,Tim::vector<CM::Step> &next_step,int player){}
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_OTHELLO_PIECE_OTHELLOSKIPSTONE_H_ */
