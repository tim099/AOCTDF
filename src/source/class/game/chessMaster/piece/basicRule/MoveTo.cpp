#include "class/game/chessMaster/piece/basicRule/MoveTo.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/display/draw/Draw.h"
#include "class/tim/string/String.h"
#include "class/display/UI/string/EnterString.h"
#include "class/tim/string/String.h"
namespace CM {

MoveTo::MoveTo() {
	dx=0;dy=0;
	ui=new UI::UI(CM::folder_path+"basicRule/"+get_name()+"/UI.txt");
}
MoveTo::~MoveTo() {
	delete ui;
}
void MoveTo::save(FILE* file){
	fprintf(file,"dx=%d,dy=%d\n",dx,dy);
}
void MoveTo::load(FILE* file){
	fscanf(file,"dx=%d,dy=%d\n",&dx,&dy);
	set_delta(dx,dy);
}
void MoveTo::set_delta(int _dx,int _dy){
	dx=_dx;
	dy=_dy;
	UI::EnterString *dxstr=dynamic_cast<UI::EnterString*>(ui->get_child("dx"));
	dxstr->set_string(Tim::String::to_string(dx));

	UI::EnterString *dystr=dynamic_cast<UI::EnterString*>(ui->get_child("dy"));
	dystr->set_string(Tim::String::to_string(dy));
}
void MoveTo::update_UI(){
	ui->update_UIObject();

}
void MoveTo::draw_UI(){

	Display::Draw *draw=Display::Draw::get_cur_object();

	UI::EnterString *dxstr=dynamic_cast<UI::EnterString*>(ui->get_child("dx"));
	dx=Tim::String::str_to_int(dxstr->get_string());
	UI::EnterString *dystr=dynamic_cast<UI::EnterString*>(ui->get_child("dy"));
	dy=Tim::String::str_to_int(dystr->get_string());

	ui->draw_UIObject(draw);
}
void MoveTo::get_next_step(CM::Board<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player){
	int i=x+dx;
	int j=y+dy*player;
	ChessBoard* board=ChessBoard::get_cur_object();
	if(board->bound_check(i,j)&&chess_board->get(i,j)*player<=0){//attack or move
		next_step.push_back(i);
		next_step.push_back(j);
	}

}
} /* namespace CM */
