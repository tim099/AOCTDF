#include "class/game/chessMaster/chessboard/shogi/piece/Silver.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace CM {
namespace shogi {

Silver::Silver() {
	set_draw_piece1("chess/silver");
	set_draw_piece2("chess/silver");
	weight=80;
	name="Silver";
}
Silver::~Silver() {

}
void Silver::next_step(CM::Board<short int> *chess_board,
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

	CM::Step cur_step;
	cur_step.add_move(x,y,0,-1);
	cur_step.add_move(0,0,chess_board->get(x,y),1);
	int i,j,n_type;
	i=x;
	j=y+1*player;
	if(bound_check(i,j)){
		n_type=chess_board->get(i,j);
		if(n_type*player==0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			next_step.push_back(cur_step);
		}else if(n_type*player<0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			capture(chess_board,cur_step,player,n_type);
			next_step.push_back(cur_step);
		}
		if((player==1&&j>5)||(player==-1&&j<3)){
			cur_step.moves[1].z=player*(type+8);
			next_step.push_back(cur_step);
			cur_step.moves[1].z=player*type;
		}
	}
	cur_step.move_num=2;

	i=x+1;
	j=y+1*player;;
	if(bound_check(i,j)){
		n_type=chess_board->get(i,j);
		if(n_type*player==0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			next_step.push_back(cur_step);
		}else if(n_type*player<0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			capture(chess_board,cur_step,player,n_type);
			next_step.push_back(cur_step);
		}
		if((player==1&&j>5)||(player==-1&&j<3)){
			cur_step.moves[1].z=player*(type+8);
			next_step.push_back(cur_step);
			cur_step.moves[1].z=player*type;
		}
	}
	cur_step.move_num=2;

	i=x-1;
	j=y+1*player;;
	if(bound_check(i,j)){
		n_type=chess_board->get(i,j);
		if(n_type*player==0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			next_step.push_back(cur_step);
		}else if(n_type*player<0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			capture(chess_board,cur_step,player,n_type);
			next_step.push_back(cur_step);
		}
		if((player==1&&j>5)||(player==-1&&j<3)){
			cur_step.moves[1].z=player*(type+8);
			next_step.push_back(cur_step);
			cur_step.moves[1].z=player*type;
		}
	}
	cur_step.move_num=2;

	i=x+1;
	j=y-1*player;;
	if(bound_check(i,j)){
		n_type=chess_board->get(i,j);
		if(n_type*player==0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			next_step.push_back(cur_step);
		}else if(n_type*player<0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			capture(chess_board,cur_step,player,n_type);
			next_step.push_back(cur_step);
		}
		if((player==1&&j>5)||(player==-1&&j<3)){
			cur_step.moves[1].z=player*(type+8);
			next_step.push_back(cur_step);
			cur_step.moves[1].z=player*type;
		}
	}
	cur_step.move_num=2;

	i=x-1;
	j=y-1*player;
	if(bound_check(i,j)){
		n_type=chess_board->get(i,j);
		if(n_type*player==0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			next_step.push_back(cur_step);
		}else if(n_type*player<0){
			cur_step.moves[1].x=i;
			cur_step.moves[1].y=j;
			capture(chess_board,cur_step,player,n_type);
			next_step.push_back(cur_step);
		}
		if((player==1&&j>5)||(player==-1&&j<3)){
			cur_step.moves[1].z=player*(type+8);
			next_step.push_back(cur_step);
			cur_step.moves[1].z=player*type;
		}
	}
	cur_step.move_num=2;
}
} /* namespace shogi */
} /* namespace CM */
