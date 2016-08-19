#include "class/game/chessMaster/chessboard/othello/OthelloRule.h"

namespace CM {

OthelloRule::OthelloRule() {

}
OthelloRule::~OthelloRule() {

}
int OthelloRule::check_winner(CM::Board<short int> *chess_board){
	if(chess_board->get(8,3)&&chess_board->get(8,4)){
		int sum=0;
		for(unsigned i=0;i<8;i++){
			for(unsigned j=0;j<8;j++){
				sum+=chess_board->get(i,j);
			}
		}
		if(sum>=0){
			return 1;
		}else{
			return -1;
		}
	}
	return 0;
}
} /* namespace CM */
