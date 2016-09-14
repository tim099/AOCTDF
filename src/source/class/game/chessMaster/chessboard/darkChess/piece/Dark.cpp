#include "class/game/chessMaster/chessboard/darkChess/piece/Dark.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include <cstdlib>
namespace CM {
namespace darkChess {

Dark::Dark() {
	draw_piece1=Display::AllDrawObjects::get_cur_object()->get("chess/dark");
	draw_piece2=Display::AllDrawObjects::get_cur_object()->get("chess/dark");
	weight=0;
	name="Dark";
}
Dark::~Dark() {

}
void Dark::next_step(CM::Board<short int> *chess_board,
		int x,int y,Tim::vector<CM::Step> &next_step,int player){
	int chess_num=0;
	for(unsigned i=0;i<8;i++){
		for(unsigned j=5;j<9;j++){
			if(chess_board->get(i,j)){
				chess_num++;
			}
		}
	}
	mutex.wait_for_this();
	int next=rand()%chess_num;
	mutex.release();

	int px=0;//next%8
	int py=5;//(next/8)+5
	while(true){
		if(chess_board->get(px,py)){
			next--;
		}
		if(next<0)break;
		px++;
		if(px>=8){
			px=0;
			py++;
		}
		if(py>=9){
			break;
		}
	}

	int type=chess_board->get(px,py);
	CM::Step cur_step;
	cur_step.add_move(x,y,type,1);
	cur_step.add_move(px,py,0,0);
	next_step.push_back(cur_step);

}
} /* namespace darkChess */
} /* namespace CM */
