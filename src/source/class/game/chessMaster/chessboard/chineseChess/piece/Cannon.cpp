#include "class/game/chessMaster/chessboard/chineseChess/piece/Cannon.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

Cannon::Cannon() {
	set_draw_piece1("chess/red_cannon");
	set_draw_piece2("chess/black_cannon");
	weight=50;
	name="Cannon";
}
Cannon::~Cannon() {

}
void Cannon::next_step(CM::Board<short int>*chess_board,
		int x,int y,Tim::vector<CM::Step> &next_step,int player){
	cannon_move(chess_board,x,y,1,0,player,next_step);
	cannon_move(chess_board,x,y,-1,0,player,next_step);
	cannon_move(chess_board,x,y,0,1,player,next_step);
	cannon_move(chess_board,x,y,0,-1,player,next_step);
}
} /* namespace CM */
