#include "class/game/chessMaster/chessboard/darkChess/piece/Horse.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace CM {
namespace darkChess {

Horse::Horse() {
	draw_piece1=Display::AllDrawObjects::get_cur_object()->get("chess/red_horse");
	draw_piece2=Display::AllDrawObjects::get_cur_object()->get("chess/black_horse");
	weight=40;
	name="Horse";
}
Horse::~Horse() {

}
void Horse::next_step(CM::Board<short int> *chess_board,
		int x,int y,Tim::vector<CM::Step> &next_step,int player){
	if(!bound_check(x,y))return;
	static const int rank=4;
	CM::Step cur_step;
	cur_step.add_move(x,y,0,-1);
	cur_step.add_move(0,0,chess_board->get(x,y),1);
	int i,j,type;
	i=x;
	j=y+1*player;
	type=chess_board->get(i,j);
	if(bound_check(i,j)&&(type!=1)&&(type==0||(type*player<0&&-type*player<=rank))){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
	i=x;
	j=y-1*player;
	type=chess_board->get(i,j);
	if(bound_check(i,j)&&(type!=1)&&(type==0||(type*player<0&&-type*player<=rank))){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
	i=x+1*player;
	j=y;
	type=chess_board->get(i,j);
	if(bound_check(i,j)&&(type!=1)&&(type==0||(type*player<0&&-type*player<=rank))){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
	i=x-1*player;
	j=y;
	type=chess_board->get(i,j);
	if(bound_check(i,j)&&(type!=1)&&(type==0||(type*player<0&&-type*player<=rank))){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
}
} /* namespace darkChess */
} /* namespace CM */
