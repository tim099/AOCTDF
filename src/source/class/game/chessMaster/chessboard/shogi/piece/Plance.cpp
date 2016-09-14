#include "class/game/chessMaster/chessboard/shogi/piece/Plance.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace CM {
namespace shogi {

Plance::Plance() {
	draw_piece1=Display::AllDrawObjects::get_cur_object()->get("chess/plance");
	draw_piece2=Display::AllDrawObjects::get_cur_object()->get("chess/plance");
	weight=90;
	name="Promoted Lance";
}
Plance::~Plance() {

}
void Plance::next_step(CM::Board<short int> *chess_board,
		int x,int y,Tim::vector<CM::Step> &next_step,int player){
	if(!bound_check(x,y))return;

	CM::Step cur_step;
	cur_step.add_move(x,y,0,-1);
	cur_step.add_move(0,0,chess_board->get(x,y),1);
	int i,j,type;
	i=x;
	j=y+1*player;
	if(bound_check(i,j)){
		type=chess_board->get(i,j);
		if(type*player==0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			next_step.push_back(cur_step);
		}else if(type*player<0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			capture(chess_board,cur_step,player,type);
			next_step.push_back(cur_step);
		}
	}
	cur_step.move_num=2;
	i=x;
	j=y-1*player;
	if(bound_check(i,j)){
		type=chess_board->get(i,j);
		if(type*player==0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			next_step.push_back(cur_step);
		}else if(type*player<0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			capture(chess_board,cur_step,player,type);
			next_step.push_back(cur_step);
		}
	}
	cur_step.move_num=2;
	i=x+1;
	j=y;
	if(bound_check(i,j)){
		type=chess_board->get(i,j);
		if(type*player==0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			next_step.push_back(cur_step);
		}else if(type*player<0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			capture(chess_board,cur_step,player,type);
			next_step.push_back(cur_step);
		}
	}
	cur_step.move_num=2;

	i=x-1;
	j=y;
	if(bound_check(i,j)){
		type=chess_board->get(i,j);
		if(type*player==0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			next_step.push_back(cur_step);
		}else if(type*player<0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			capture(chess_board,cur_step,player,type);
			next_step.push_back(cur_step);
		}
	}
	cur_step.move_num=2;

	i=x+1;
	j=y+1*player;;
	if(bound_check(i,j)){
		type=chess_board->get(i,j);
		if(type*player==0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			next_step.push_back(cur_step);
		}else if(type*player<0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			capture(chess_board,cur_step,player,type);
			next_step.push_back(cur_step);
		}
	}
	cur_step.move_num=2;

	i=x-1;
	j=y+1*player;;
	if(bound_check(i,j)){
		type=chess_board->get(i,j);
		if(type*player==0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			next_step.push_back(cur_step);
		}else if(type*player<0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			capture(chess_board,cur_step,player,type);
			next_step.push_back(cur_step);
		}
	}
	cur_step.move_num=2;
}
} /* namespace shogi */
} /* namespace CM */
