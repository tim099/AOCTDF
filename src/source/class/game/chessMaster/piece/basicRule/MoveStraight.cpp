#include "class/game/chessMaster/piece/basicRule/MoveStraight.h"

#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/display/draw/Draw.h"
#include "class/tim/string/String.h"
#include "class/display/UI/string/EnterString.h"
#include "class/tim/string/String.h"
#include <cstdio>
namespace CM {

MoveStraight::MoveStraight() {
	dx=0;dy=0;
	ui=new UI::UI(CM::folder_path+"basicRule/"+get_name()+"/UI.txt");
}
MoveStraight::~MoveStraight() {
	delete ui;
}
void MoveStraight::get_next_step(CM::Board<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player){

	ChessBoard* board=ChessBoard::get_cur_object();
	if(!board->bound_check(x,y))return;

	int i=x+dx;
	int j=y+dy*player;
	while(board->bound_check(i,j)){
		short int type=chess_board->get(i,j);

		if(type*player>0){//stop by our chess
			break;
		}
		next_step.push_back(i);
		next_step.push_back(j);

		if (type*player<0){
			break;//attack enemy
		}

		i=i+dx;
		j=j+dy*player;//reverse for player 2
	}
}
void MoveStraight::save(FILE* file){
	fprintf(file,"dx=%d,dy=%d\n",dx,dy);
}
void MoveStraight::load(FILE* file){
	fscanf(file,"dx=%d,dy=%d\n",&dx,&dy);
	set_delta(dx,dy);
}
void MoveStraight::set_delta(int _dx,int _dy){
	dx=_dx;
	dy=_dy;
	UI::EnterString *dxstr=dynamic_cast<UI::EnterString*>(ui->get_child("dx"));
	dxstr->set_string(Tim::String::to_string(dx));

	UI::EnterString *dystr=dynamic_cast<UI::EnterString*>(ui->get_child("dy"));
	dystr->set_string(Tim::String::to_string(dy));
}
void MoveStraight::update_UI(){
	ui->update_UIObject();

}
void MoveStraight::draw_UI(){

	Display::Draw *draw=Display::Draw::get_cur_object();

	UI::EnterString *dxstr=dynamic_cast<UI::EnterString*>(ui->get_child("dx"));
	dx=Tim::String::str_to_int(dxstr->get_string());
	UI::EnterString *dystr=dynamic_cast<UI::EnterString*>(ui->get_child("dy"));
	dy=Tim::String::str_to_int(dystr->get_string());

	ui->draw_UIObject(draw);
}
} /* namespace CM */
