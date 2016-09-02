#include "class/game/chessMaster/piece/basicRule/BasicRule.h"

namespace CM {

BasicRule::BasicRule() {
	ui=0;
}
BasicRule::~BasicRule() {

}
void BasicRule::next_step(CM::Board<short int> *chess_board,
			int x,int y,Tim::vector<CM::Step> &next_steps){
	int player;
	std::vector<int> next;
	next.reserve(120);
	if(chess_board->get(x,y)>0){
		player=1;
	}else{
		player=-1;
	}
	get_next_step(chess_board,x,y,next,player);
	int i=0;
	CM::Step next_step;
	while(i<(int)next.size()){
		next_step.parse_step(chess_board,x,y,next,i);
		next_steps.push_back(next_step);
	}
}
} /* namespace CM */
