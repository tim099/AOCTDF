#include "class/game/chessMaster/chessboard/othello/piece/OthelloStone.h"

#include "class/game/chessMaster/chessboard/renju/Renju.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace CM {

OthelloStone::OthelloStone() {
	draw_piece1=Display::AllDrawObjects::get_cur_object()->get("chess/black");
	draw_piece2=Display::AllDrawObjects::get_cur_object()->get("chess/white");
	weight=1;
}
OthelloStone::~OthelloStone() {

}
void OthelloStone::next_step(CM::Board<short int> *chess_board,
		int x,int y,Tim::vector<CM::Step> &next_step,int player){
	if(bound_check(x,y)){//in chess board
		return;
	}


	//cur_step.add_move(0,0,player,1);
	CM::Step cur_step;
	int count;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(chess_board->get(i,j)==0){
				cur_step.move_num=0;//clear

				count=0;
				for(int k=i+1;k<8;k++){
					if(chess_board->get(k,j)==-player){
						cur_step.add_move(k,j,player,-1);
						count++;
					}else{
						if((chess_board->get(k,j)==player)){
							count=0;
						}
						break;
					}
				}
				cur_step.move_num-=count;
				count=0;
				for(int k=i-1;k>=0;k--){
					if(chess_board->get(k,j)==-player){
						cur_step.add_move(k,j,player,-1);
						count++;
					}else{
						if((chess_board->get(k,j)==player)){
							count=0;
						}
						break;
					}
				}
				cur_step.move_num-=count;
				count=0;
				for(int k=j+1;k<8;k++){
					if(chess_board->get(i,k)==-player){
						cur_step.add_move(i,k,player,-1);
						count++;
					}else{
						if(chess_board->get(i,k)==player){
							count=0;
						}
						break;
					}
				}
				cur_step.move_num-=count;
				count=0;
				for(int k=j-1;k>=0;k--){
					if(chess_board->get(i,k)==-player){
						cur_step.add_move(i,k,player,-1);
						count++;
					}else{
						if(chess_board->get(i,k)==player){
							count=0;
						}
						break;
					}
				}
				cur_step.move_num-=count;
				count=0;
				for(int k=1;bound_check(i+k,j+k);k++){
					if(chess_board->get(i+k,j+k)==-player){
						cur_step.add_move(i+k,j+k,player,-1);
						count++;
					}else{
						if(chess_board->get(i+k,j+k)==player){
							count=0;
						}
						break;
					}
				}
				cur_step.move_num-=count;
				count=0;
				for(int k=1;bound_check(i-k,j+k);k++){
					if(chess_board->get(i-k,j+k)==-player){
						cur_step.add_move(i-k,j+k,player,-1);
						count++;
					}else{
						if(chess_board->get(i-k,j+k)==player){
							count=0;
						}
						break;
					}
				}
				cur_step.move_num-=count;
				count=0;
				for(int k=1;bound_check(i+k,j-k);k++){
					if(chess_board->get(i+k,j-k)==-player){
						cur_step.add_move(i+k,j-k,player,-1);
						count++;
					}else{
						if(chess_board->get(i+k,j-k)==player){
							count=0;
						}
						break;
					}
				}
				cur_step.move_num-=count;
				count=0;
				for(int k=1;bound_check(i-k,j-k);k++){
					if(chess_board->get(i-k,j-k)==-player){
						cur_step.add_move(i-k,j-k,player,-1);
						count++;
					}else{
						if(chess_board->get(i-k,j-k)==player){
							count=0;
						}
						break;
					}
				}
				cur_step.move_num-=count;
				count=0;

				if(cur_step.move_num>0){
					cur_step.add_move(i,j,player,1);
					if(chess_board->get(8,3))cur_step.add_move(8,3,player,0);
					if(chess_board->get(8,4))cur_step.add_move(8,4,player,0);
					/*
					for(unsigned i=0;i<cur_step.move_num;i++){
						std::cout<<"step="<<cur_step.moves[i].x<<","<<cur_step.moves[i].y<<
								","<<cur_step.moves[i].w<<std::endl;
					}
					std::cout<<std::endl;
					*/
					next_step.push_back(cur_step);

				}
			}
		}
	}
	if(next_step.size()==0){
		cur_step.move_num=0;
		if(player==1){
			cur_step.add_move(8,3,player,1);
		}else{
			cur_step.add_move(8,4,player,1);
		}
		next_step.push_back(cur_step);
	}
	//




}
} /* namespace CM */
