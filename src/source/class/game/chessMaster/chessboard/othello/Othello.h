#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_OTHELLO_OTHELLO_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_OTHELLO_OTHELLO_H_

#include "class/game/chessMaster/chessboard/ChessBoard.h"

namespace CM {

class Othello: public ChessBoard {
public:
	static const int board_size=8;
	Othello();
	virtual ~Othello();
	void create_pieces();
	virtual int evaluate_score(CM::Board<short int> *chess_board,int player);
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_OTHELLO_OTHELLO_H_ */
