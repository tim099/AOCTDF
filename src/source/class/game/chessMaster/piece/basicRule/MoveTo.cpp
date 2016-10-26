#include "class/game/chessMaster/piece/basicRule/MoveTo.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/display/draw/Draw.h"
#include "class/tim/string/String.h"
#include "class/display/UI/string/EnterString.h"
#include "class/tim/string/String.h"
#include "class/input/Input.h"
namespace CM {

MoveTo::MoveTo() {
	dx=0;dy=0;type=type_move_and_attack;
	ui=new UI::UI(CM::folder_path+"basicRule/"+get_name()+"/UI.txt");
	setting_mode=false;
}
MoveTo::~MoveTo() {
	delete ui;
}
void MoveTo::save(FILE* file){
	fprintf(file,"dx=%d,dy=%d,type=%d\n",dx,dy,type);
}
void MoveTo::load(FILE* file){
	fscanf(file,"dx=%d,dy=%d,type=%d\n",&dx,&dy,&type);
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
void MoveTo::handle_input(int x,int y,int sx,int sy){
	Input::Input *input=Input::Input::get_cur_object();
	if(setting_mode&&input->mouse->get_left_click()){
		set_delta(sx-x,sy-y);
		setting_mode=false;
	}
}
void MoveTo::update(){
	Input::Input *input=Input::Input::get_cur_object();
	while(Input::Signal*sig=input->get_signal("rule")){
		if(sig->get_data()=="move"){
			type=type_move;
		}else if(sig->get_data()=="attack"){
			type=type_attack;
		}else if(sig->get_data()=="move&attack"){
			type=type_move_and_attack;
		}else if(sig->get_data()=="set"){
			setting_mode=true;
		}
		delete sig;
	}

}
void MoveTo::update_UI(){
	ui->update_UIObject();

}
void MoveTo::draw_UI(){
	UI::EnterString *dxstr=dynamic_cast<UI::EnterString*>(ui->get_child("dx"));
	dx=Tim::String::str_to_int(dxstr->get_string());
	UI::EnterString *dystr=dynamic_cast<UI::EnterString*>(ui->get_child("dy"));
	dy=Tim::String::str_to_int(dystr->get_string());


	UI::UIString *uistr=dynamic_cast<UI::UIString*>(ui->get_child("type"));
	if(type==type_move){
		uistr->set_string("move");
	}else if(type==type_attack){
		uistr->set_string("attack");
	}else if(type==type_move_and_attack){
		uistr->set_string("move&attack");
	}
	Display::Draw *draw=Display::Draw::get_cur_object();
	ui->draw_UIObject(draw);
}
void MoveTo::get_next_step(CM::Board<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player){
	ChessBoard* board=ChessBoard::get_cur_object();
	if(!board->bound_check(x,y))return;
	int i=x+dx;
	int j=y+dy*player;
	if(type==type_move){
		if(board->bound_check(i,j)&&chess_board->get(i,j)==0){//move
			next_step.push_back(i);
			next_step.push_back(j);
		}
	}else if(type==type_attack){
		if(board->bound_check(i,j)&&chess_board->get(i,j)*player<0){//attack
			next_step.push_back(i);
			next_step.push_back(j);
		}
	}else if(type==type_move_and_attack){
		if(board->bound_check(i,j)&&chess_board->get(i,j)*player<=0){//attack or move
			next_step.push_back(i);
			next_step.push_back(j);
		}
	}


}
} /* namespace CM */
