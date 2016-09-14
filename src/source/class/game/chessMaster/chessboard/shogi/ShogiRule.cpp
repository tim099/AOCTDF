#include "class/game/chessMaster/chessboard/shogi/ShogiRule.h"

namespace CM {
namespace shogi {
ShogiRule::ShogiRule() {

}
ShogiRule::~ShogiRule() {

}
int ShogiRule::check_winner(CM::Board<short int> *chess_board){
	if(chess_board->piece_num[7]>0)return 1;
	else if(chess_board->piece_num[7]<0)return -1;
	return 0;
}
}
} /* namespace CM */
