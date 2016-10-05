#include "class/game/chessMaster/piece/basicRule/condition/CheckBoard.h"
#include "class/display/draw/Draw.h"
#include "class/display/UI/string/EnterString.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/input/Input.h"
#include "class/display/light/LightControl.h"

namespace CM {

CheckBoard::CheckBoard() {
	ui=new UI::UI(CM::folder_path+"condition/"+get_name()+"/UI.txt");
	dx=0;
	dy=0;
	type=type_empty;
}
CheckBoard::~CheckBoard() {
	delete ui;
}
void CheckBoard::save_condition(FILE* file){
	fprintf(file,"dx=%d,dy=%d,type=%d\n",dx,dy,type);
}
void CheckBoard::load_condition(FILE* file){
	fscanf(file,"dx=%d,dy=%d,type=%d\n",&dx,&dy,&type);
	set_delta(dx,dy);
}
void CheckBoard::set_delta(int _dx,int _dy){
	dx=_dx;
	dy=_dy;
	UI::EnterString *dxstr=dynamic_cast<UI::EnterString*>(ui->get_child("dx"));
	dxstr->set_string(Tim::String::to_string(dx));

	UI::EnterString *dystr=dynamic_cast<UI::EnterString*>(ui->get_child("dy"));
	dystr->set_string(Tim::String::to_string(dy));
}
bool CheckBoard::get_condition(CM::Board<short int> *chess_board,
			int x,int y,int player){
	int i,j;
	i=x+dx;j=y+dy;
	ChessBoard* board=ChessBoard::get_cur_object();
	if(type==type_empty){
		if(board->bound_check(i,j)&&chess_board->get(i,j)==0){
			return true;
		}
	}else if(type==type_enemy){
		if(board->bound_check(i,j)&&chess_board->get(i,j)*player<0){
			return true;
		}
	}else if(type==type_player){
		if(board->bound_check(i,j)&&chess_board->get(i,j)*player>0){
			return true;
		}
	}else if(type==type_piece){
		if(board->bound_check(i,j)&&chess_board->get(i,j)!=0){
			return true;
		}
	}


	return false;
}
void CheckBoard::draw(int x,int y){
	//std::cout<<"CheckBoard::draw"<<std::endl;
	ChessBoard* chess_board=ChessBoard::get_cur_object();
	Display::CubeLight* cl;

	cl=new Display::CubeLight();
	cl->size=1.01f*chess_board->cube_size;
	cl->color=glm::vec3(0.2,0.2,0.8);

	cl->pos=glm::vec3((x+dx+0.5f)*chess_board->cube_size,
					(2.5f)*chess_board->cube_size,
					(y+dy+0.5f)*chess_board->cube_size);
	Display::Draw::get_cur_object()->lightControl->push_temp_light(cl);


}
void CheckBoard::draw_UI(){
	UI::UIString *uistr=dynamic_cast<UI::UIString*>(ui->get_child("type"));
	if(type==type_empty){
		uistr->set_string("empty");
	}else if(type==type_enemy){
		uistr->set_string("enemy");
	}else if(type==type_player){
		uistr->set_string("player");
	}else if(type==type_piece){
		uistr->set_string("piece");
	}
	uistr=dynamic_cast<UI::UIString*>(ui->get_child("operator"));
	if(do_and){
		uistr->set_string("and");
	}else{
		uistr->set_string("or");
	}


	UI::EnterString *dxstr=dynamic_cast<UI::EnterString*>(ui->get_child("dx"));
	dx=Tim::String::str_to_int(dxstr->get_string());
	UI::EnterString *dystr=dynamic_cast<UI::EnterString*>(ui->get_child("dy"));
	dy=Tim::String::str_to_int(dystr->get_string());

	Display::Draw *draw=Display::Draw::get_cur_object();
	ui->draw_UIObject(draw);
}
void CheckBoard::update(){
	Input::Input *input=Input::Input::get_cur_object();
	while(Input::Signal*sig=input->get_signal("rule")){
		if(sig->get_data()=="enemy"){
			type=type_enemy;
		}else if(sig->get_data()=="empty"){
			type=type_empty;
		}else if(sig->get_data()=="piece"){
			type=type_piece;
		}else if(sig->get_data()=="player"){
			type=type_player;
		}else if(sig->get_data()=="and"){
			do_and=true;
		}else if(sig->get_data()=="or"){
			do_and=false;
		}
	}
}
void CheckBoard::update_UI(){
	ui->update_UIObject();
}
} /* namespace CM */
