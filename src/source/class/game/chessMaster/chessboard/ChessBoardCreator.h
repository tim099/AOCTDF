#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARDCREATOR_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARDCREATOR_H_
#include <string>
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

class ChessBoardCreator {
public:
	ChessBoardCreator();
	virtual ~ChessBoardCreator();
	static ChessBoard* create(std::string name);
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARDCREATOR_H_ */
