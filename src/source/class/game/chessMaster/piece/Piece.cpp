#include "class/game/chessMaster/piece/Piece.h"
#include "class/tim/string/String.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/game/chessMaster/piece/basicRule/BasicRuleCreator.h"
#include "class/tim/file/File.h"
#include "class/display/UI/page/AutoPageControl.h"
#include "class/tim/string/String.h"
#include "class/game/chessMaster/common.h"
//#include "class/display/UI/UIObjectCreator.h"
#include <fstream>
namespace CM {

Piece::Piece() {
	weight=1;
	draw_piece1=0;
	draw_piece2=0;
	//type=1;
	rule=0;
	name="default";
	rule_mutex=new Tim::Mutex();
}
Piece::~Piece() {
	//delete rule_UI;
	if(rule)delete rule;
	delete rule_mutex;
	for(unsigned i=0;i<basic_rules.size();i++){
		delete basic_rules.at(i);
	}
}
void Piece::update_rule_UI(UI::UI *rule_UI){
	UI::AutoPageControl *page=dynamic_cast<UI::AutoPageControl*>(rule_UI->get_child("rules_page"));
	if(page){
		//std::cout<<"Piece::update_rule_UI"<<std::endl;
		std::vector<std::string> names;
		std::vector<std::string> sigs;
		get_rule_names(names);
		for(unsigned i=0;i<names.size();i++){
			sigs.push_back(Tim::String::to_string(i));
		}
		page->create_pages(names,&sigs);
	}


	rule_UI->update_UIObject();
}
void Piece::get_rule_names(std::vector<std::string> &names){
	for(unsigned i=0;i<basic_rules.size();i++){
		names.push_back(basic_rules.at(i)->get_name());
	}
}
void Piece::load_script(std::string dir_path,std::string path){
	std::filebuf file;

	name=path;
	file.open((dir_path+path+".txt").c_str(), std::ios::in);
	if (!file.is_open()) {
		std::cerr << "Piece::load_script fail,file:" << dir_path+path
				<< " open fail" << std::endl;
		return;
	}
	std::istream is(&file);
	std::string line;
	while(Tim::String::get_line(is, line, true, true)&&line!="#END"){
		if(line=="draw_piece1:"){
			Tim::String::get_line(is, line, true, true);
			draw_piece1=Display::AllDrawObjects::get_cur_object()->get(line);
		}else if(line=="draw_piece2:"){
			Tim::String::get_line(is, line, true, true);
			draw_piece2=Display::AllDrawObjects::get_cur_object()->get(line);
		}else if(line=="weight:"){//.lua file
			Tim::String::get_line(is, line, true, true);
			sscanf(line.c_str(),"%d",&weight);
		}else if(line!=""){
			std::cerr<<"Piece::load_script unknown script:"<<line<<std::endl;
		}
	}
	if(rule){
		delete rule;
		rule=0;
	}
	rule=new Tim::Lua();
	rule->loadfile((dir_path+path+".lua"));
	rule->rigister_function("get_board",ChessBoard::get_board);
	rule->p_call(0,0,0);
	//load_basic_rule(dir_path+path+".rule");

}
void Piece::remove_basic_rule(BasicRule* rule){
	for(unsigned i=0;i<basic_rules.size();i++){
		if(basic_rules.at(i)==rule){
			for(unsigned j=i+1;j<basic_rules.size();j++){
				basic_rules.at(j-1)=basic_rules.at(j);
			}
			basic_rules.pop_back();
			delete rule;
			break;
		}
	}
}
void Piece::add_rule(std::string rule_name){
	BasicRule* rule=BasicRuleCreator::get_cur_object()->create(rule_name);
	basic_rules.push_back(rule);
}
void Piece::load_basic_rule(std::string path){
	//std::cout<<"Piece::load_basic_rule:"<<path<<std::endl;
	if(!Tim::File::check_if_file_exist(path)){// no file exist
		//std::cout<<"Piece::load_basic_rule fail!!,create:"<<path<<std::endl;
		save_basic_rule(path);
	}
	FILE * file = fopen(path.c_str(),"r");
	unsigned rule_number;
	char name[100];
	fscanf(file,"rule_number=%u\n",&rule_number);

	for(unsigned i=0;i<rule_number;i++){
		fscanf(file,"%s\n",name);
		BasicRule* rule=BasicRuleCreator::get_cur_object()->create(name);
		rule->load(file);
		basic_rules.push_back(rule);
	}

	fclose(file);
}
void Piece::save_basic_rule(std::string path){
	FILE * file = fopen(path.c_str(),"w+t");
	fprintf(file,"rule_number=%u\n",basic_rules.size());

	for(unsigned i=0;i<basic_rules.size();i++){
		fprintf(file,"%s\n",basic_rules.at(i)->get_name().c_str());
		basic_rules.at(i)->save(file);
	}
	fclose(file);
}
void Piece::next_step(CM::Board<short int> *chess_board,
		int x,int y,std::vector<int> &next_step,int player){
	rule_mutex->wait_for_this();
	//ChessBoard::get_cur_object()->set_current(chess_board);
	rule->pushlightuserdata(chess_board);
	rule->set_global("board");

	rule->get_global("next_step");
	rule->push_number(x);
	rule->push_number(y);
	rule->push_number(player);

	rule->p_call(3,1,0);

	rule->get_table(next_step);

	rule->pop(1);//pop next_step

	rule_mutex->release();
}
void Piece::basic_next_step(CM::Board<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player){
	for(unsigned i=0;i<basic_rules.size();i++){
		basic_rules.at(i)->get_next_step(chess_board,x,y,next_step,player);
	}
}
void Piece::next_step(CM::Board<short int> *chess_board,
		int x,int y,Tim::vector<CM::Step> &next_steps,int player){
	std::vector<int> next;
	next.reserve(120);
	next_step(chess_board,x,y,next,player);
	basic_next_step(chess_board,x,y,next,player);
	CM::Step next_step;
	int i=0;
	while(i<(int)next.size()){
		next_step.parse_step(chess_board,x,y,next,i);
		next_steps.push_back(next_step);
	}
}
void Piece::draw(math::Position* pos,int player){
	if(player==1){
		draw_piece1->push_temp_drawdata(new Display::DrawDataObj(pos,true,true));
	}else{
		draw_piece2->push_temp_drawdata(new Display::DrawDataObj(pos,true,true));
	}
}


} /* namespace CM */
