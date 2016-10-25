#include "class/game/chessMaster/chessboard/shogi/piece/Pawn.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace CM {
namespace shogi {

Pawn::Pawn() {
	set_draw_piece1("chess/pawn");
	set_draw_piece2("chess/pawn");
	weight=10;
	name="Pawn";
}
Pawn::~Pawn() {

}
void Pawn::next_step(CM::Board<short int> *chess_board,
		int x,int y,Tim::vector<CM::Step> &next_step,int player){
	if(!bound_check(x,y)){
		CM::Step cur_step;
		cur_step.add_move(x,y,0,-1);
		cur_step.add_move(0,0,player*type,1);
		bool flag;
		for(int i=0;i<9;i++){
			flag=false;
			for(int j=0;j<9;j++){
				if(chess_board->get(i,j)==player*type){
					flag=true;
					break;
				}
			}
			if(!flag){
				if(player==1){
					for(int j=0;j<8;j++){
						if(chess_board->get(i,j)==0){
							cur_step.moves[1].x=i;
							cur_step.moves[1].y=j;
							next_step.push_back(cur_step);
						}
					}
				}else{
					for(int j=1;j<9;j++){
						if(chess_board->get(i,j)==0){
							cur_step.moves[1].x=i;
							cur_step.moves[1].y=j;
							next_step.push_back(cur_step);
						}
					}
				}

			}
		}



		return;
	}

	CM::Step cur_step;
	cur_step.add_move(x,y,0,-1);
	cur_step.add_move(0,0,player*type,1);
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
			cur_step.moves[1].z=player*(type+8);//ppawn
			next_step.push_back(cur_step);
			cur_step.moves[1].z=player*type;
		}
	}
	cur_step.move_num=2;
	//cur_step.moves[1].z=player*type;
}
} /* namespace shogi */
} /* namespace CM */
