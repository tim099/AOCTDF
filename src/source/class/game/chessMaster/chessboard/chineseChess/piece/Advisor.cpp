#include "class/game/chessMaster/chessboard/chineseChess/piece/Advisor.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

Advisor::Advisor() {
	set_draw_piece1("chess/red_advisor");
	set_draw_piece2("chess/black_advisor");
	weight=10;
	name="Advisor";
}
Advisor::~Advisor() {

}
void Advisor::next_step(CM::Board<short int> *chess_board,
		int x,int y,Tim::vector<CM::Step> &next_step,int player){
	CM::Step cur_step;
	cur_step.add_move(x,y,0,-1);
	cur_step.add_move(0,0,chess_board->get(x,y),1);

	int i,j;
	i=x+1;
	j=y+1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
	i=x-1;
	j=y+1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
	i=x+1;
	j=y-1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
	i=x-1;
	j=y-1;
	if(bound_check(i,j)&&in_nine(i,j)&&chess_board->get(i,j)*player<=0){
		cur_step.moves[1].x=i;
		cur_step.moves[1].y=j;
		next_step.push_back(cur_step);
	}
}
} /* namespace CM */
