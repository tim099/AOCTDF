#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_DARKCHESS_PIECE_DARK_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_DARKCHESS_PIECE_DARK_H_
#include "class/game/chessMaster/piece/Piece.h"
#include "class/tim/thread/mutex/Mutex.h"
namespace CM {
namespace darkChess {

class Dark : public Piece {
public:
	Dark();
	virtual ~Dark();
	virtual void next_step(CM::Board<short int> *chess_board,
			int x,int y,Tim::vector<CM::Step> &next_step,int player);
	Tim::Mutex mutex;
};

} /* namespace darkChess */
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_DARKCHESS_PIECE_DARK_H_ */
