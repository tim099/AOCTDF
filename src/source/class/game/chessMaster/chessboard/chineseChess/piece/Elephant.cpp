#include "class/game/chessMaster/chessboard/chineseChess/piece/Elephant.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

Elephant::Elephant() {
	set_draw_piece1("chess/red_elephant");
	set_draw_piece2("chess/black_elephant");
	weight=20;
	name="Elephant";
}
Elephant::~Elephant() {

}
void Elephant::next_step(CM::Board<short int> *chess_board,
		int x,int y,Tim::vector<CM::Step> &next_step,int player){
	CM::Step cur_step;
	cur_step.add_move(x,y,0,-1);
	cur_step.add_move(0,0,chess_board->get(x,y),1);
	int i,j;
	i=x+2;
	j=y+2;
	if(bound_check(i,j)&&chess_board->get(x+1,y+1)==0&&chess_board->get(i,j)*player<=0
			&&((player==1&&j<5)||(player==-1&&j>=5))){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
	i=x-2;
	j=y+2;
	if(bound_check(i,j)&&chess_board->get(x-1,y+1)==0&&chess_board->get(i,j)*player<=0
			&&((player==1&&j<5)||(player==-1&&j>=5))){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
	i=x+2;
	j=y-2;
	if(bound_check(i,j)&&chess_board->get(x+1,y-1)==0&&chess_board->get(i,j)*player<=0
			&&((player==1&&j<5)||(player==-1&&j>=5))){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
	i=x-2;
	j=y-2;
	if(bound_check(i,j)&&chess_board->get(x-1,y-1)==0&&chess_board->get(i,j)*player<=0
			&&((player==1&&j<5)||(player==-1&&j>=5))){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
}
} /* namespace CM */
