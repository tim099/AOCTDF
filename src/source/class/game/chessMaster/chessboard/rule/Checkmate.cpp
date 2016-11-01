#include "class/game/chessMaster/chessboard/rule/Checkmate.h"
#include "class/display/draw/Draw.h"
#include "class/display/UI/string/EnterString.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
namespace CM {

Checkmate::Checkmate() {
	ui=new UI::UI(CM::folder_path+"rule/"+get_name()+"/UI.txt");
	king=0;
}
Checkmate::~Checkmate() {
	delete ui;
}
void Checkmate::save(std::ostream &os){
	os<<king<<std::endl;
}
void Checkmate::load(std::istream &is){
	is>>king;
}
void Checkmate::set_king(std::string name){
	UI::EnterString *str=dynamic_cast<UI::EnterString*>(ui->get_child("king_name"));
	str->set_string(name);
	ChessBoard *board=ChessBoard::get_cur_object();
	for(unsigned i=0;i<board->pieces.size();i++){
		if(board->pieces.at(i)->get_name()==name){
			king=i;
		}
	}
}
int Checkmate::check_winner(CM::Board<short int> *chess_board){
	if(chess_board->piece_type_num<=king)return 0;

	if(chess_board->piece_num[king]>0){
		return 1;
	}else if(chess_board->piece_num[king]<0){
		return -1;
	}
	return 0;
}
void Checkmate::init_UI(){
	ChessBoard *board=ChessBoard::get_cur_object();
	if((int)board->pieces.size()<=king)return;

	std::string name=board->pieces.at(king)->get_name();
	UI::EnterString *str=dynamic_cast<UI::EnterString*>(ui->get_child("king_name"));
	str->set_string(name);
}
void Checkmate::set_UI(){
	UI::EnterString *str=dynamic_cast<UI::EnterString*>(ui->get_child("king_name"));
	set_king(str->get_string());
}
void Checkmate::update_UI(){
	ui->update_UIObject();
}
void Checkmate::draw_UI(){
	ui->draw_UIObject(Display::Draw::get_cur_object());
}

} /* namespace CM */
