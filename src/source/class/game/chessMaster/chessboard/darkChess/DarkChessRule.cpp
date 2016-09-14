#include "class/game/chessMaster/chessboard/darkChess/DarkChessRule.h"

namespace CM {
namespace darkChess {
DarkChessRule::DarkChessRule() {

}
DarkChessRule::~DarkChessRule() {

}
int DarkChessRule::check_winner(CM::Board<short int> *chess_board){
	bool p1=false,p2=false;
	for(unsigned i=0;i<8;i++){
		for(unsigned j=0;j<9;j++){
			if(chess_board->get(i,j)>1){
				p1=true;
			}else if(chess_board->get(i,j)<-1){
				p2=true;
			}
			if(p1&&p2)break;
		}
	}
	if(!p1)return -1;
	if(!p2)return 1;

	return 0;
}
}
} /* namespace CM */
