#include "class/game/chessMaster/chessboard/renju/piece/Stone.h"

#include "class/game/chessMaster/chessboard/renju/Renju.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace CM {

Stone::Stone() {
	draw_piece1=Display::AllDrawObjects::get_cur_object()->get("renju/black");
	draw_piece2=Display::AllDrawObjects::get_cur_object()->get("renju/white");
	weight=1;
	name="stone";
}
Stone::~Stone() {

}
void Stone::next_step(CM::Board<short int> *chess_board,
		int x,int y,Tim::vector<CM::Step> &next_steps,int player){
	if(bound_check(x,y)){//in chess board
		std::vector<int> next;
		next.reserve(120);
		basic_next_step(chess_board,x,y,next,player);
		CM::Step next_step;
		int i=0;
		while(i<(int)next.size()){
			next_step.parse_step(chess_board,x,y,next,i);
			next_steps.push_back(next_step);
		}
		return;
	}
	CM::Step cur_step;
	cur_step.add_move(0,0,player,1);
	for(int i=0;i<Renju::board_width;i++){
		for(int j=0;j<Renju::board_width;j++){
			if(chess_board->get(i,j)==0){
				cur_step.moves[0].x=i;
				cur_step.moves[0].y=j;
				next_steps.push_back(cur_step);
			}
		}
	}
	if(next_steps.size()==0){
		CM::Step null_step;
		null_step.add_move(9,4,player,1);
		next_steps.push_back(null_step);
	}



}
} /* namespace CM */
