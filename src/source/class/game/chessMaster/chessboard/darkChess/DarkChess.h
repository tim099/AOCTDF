#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_DARKCHESS_DARKCHESS_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_DARKCHESS_DARKCHESS_H_
#include "class/game/chessMaster/chessboard/ChessBoard.h"

namespace CM {
namespace darkChess {
class DarkChess : public ChessBoard{
public:
	DarkChess();
	virtual ~DarkChess();
	void create_pieces();
};
}
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_DARKCHESS_DARKCHESS_H_ */
