#include "class/game/chessMaster/chessboard/shogi/piece/Lance.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace CM {
namespace shogi {

Lance::Lance() {
	set_draw_piece1("chess/lance");
	set_draw_piece2("chess/lance");
	weight=50;
	name="Lance";
}
Lance::~Lance() {

}
void Lance::next_step(CM::Board<short int> *chess_board,
		int x,int y,Tim::vector<CM::Step> &next_step,int player){
	if(!bound_check(x,y)){
		CM::Step cur_step;
		cur_step.add_move(x,y,0,-1);
		cur_step.add_move(0,0,player*type,1);
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				if(chess_board->get(i,j)==0){
					cur_step.moves[1].x=i;
					cur_step.moves[1].y=j;
					next_step.push_back(cur_step);
				}
			}
		}
		return;
	}

	move_straight(chess_board,x,y,0,1,player,next_step);
}
} /* namespace shogi */
} /* namespace CM */
