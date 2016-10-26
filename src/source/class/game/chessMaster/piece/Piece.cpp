#include "class/game/chessMaster/piece/Piece.h"
#include "class/tim/string/String.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/game/chessMaster/piece/basicRule/BasicRuleCreator.h"
#include "class/tim/file/File.h"
#include "class/display/UI/page/AutoPageControl.h"
#include "class/tim/string/String.h"
#include "class/game/chessMaster/common.h"
#include "class/display/UI/string/EnterString.h"
#include "class/display/draw/Draw.h"

#include <fstream>
namespace CM {

Piece::Piece() {
	weight=1;
	draw_piece1=0;
	draw_piece2=0;
	type=1;
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
void Piece::init(std::string _name){
	set_name(_name);
	if(!draw_piece1){
		if(draw_piece_str1==""){
			draw_piece_str1="chess/"+name+"_p1";
		}
		if(!Display::AllDrawObjects::get_cur_object()->find(draw_piece_str1)){
			Display::DrawObject *obj=new Display::DrawObject();
			std::vector<std::string> path_vec;
			Tim::String::split(draw_piece_str1, "/", path_vec);
			obj->name=path_vec.back();
			Display::AllDrawObjects::get_cur_object()->push(draw_piece_str1,obj);
			Display::Draw::get_cur_object()->push(obj);
		}
		set_draw_piece1(draw_piece_str1);
	}
	if(!draw_piece2){
		if(draw_piece_str2==""){
			draw_piece_str2="chess/"+name+"_p2";
		}
		if(!Display::AllDrawObjects::get_cur_object()->find(draw_piece_str2)){
			Display::DrawObject *obj=new Display::DrawObject();
			std::vector<std::string> path_vec;
			Tim::String::split(draw_piece_str2, "/", path_vec);
			obj->name=path_vec.back();
			Display::AllDrawObjects::get_cur_object()->push(draw_piece_str2,obj);
			Display::Draw::get_cur_object()->push(obj);
		}
		set_draw_piece2(draw_piece_str2);
	}
}
void Piece::set_draw_piece1(std::string draw_piece_str){
	Display::DrawObject *obj=Display::AllDrawObjects::get_cur_object()->get(draw_piece_str);
	if(obj){
		draw_piece_str1=draw_piece_str;
		draw_piece1=obj;
	}
}
void Piece::set_draw_piece2(std::string draw_piece_str){
	Display::DrawObject *obj=Display::AllDrawObjects::get_cur_object()->get(draw_piece_str);
	if(obj){
		draw_piece_str2=draw_piece_str;
		draw_piece2=obj;
	}
}
void Piece::update_rule_UI(UI::UI *rule_UI){
	rule_UI->update_UIObject();
}
void Piece::init_rule_page(UI::UI *rule_UI){
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
	page->update_UIObject();
}
void Piece::init_piece_UI(UI::UI *ui){
	UI::EnterString *str=dynamic_cast<UI::EnterString*>(ui->get_child("weight"));
	str->set_string(Tim::String::to_string(weight));

	if(draw_piece1){
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p1tex"));
		str->set_string(draw_piece1->texture_name);
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p1model"));
		str->set_string(draw_piece1->modelbuffer_name);

		str=dynamic_cast<UI::EnterString*>(ui->get_child("p1matx"));
		str->set_string(Tim::String::to_string(draw_piece1->mat.x));

		str=dynamic_cast<UI::EnterString*>(ui->get_child("p1maty"));
		str->set_string(Tim::String::to_string(draw_piece1->mat.y));

		str=dynamic_cast<UI::EnterString*>(ui->get_child("p1matz"));
		str->set_string(Tim::String::to_string(draw_piece1->mat.z));

		str=dynamic_cast<UI::EnterString*>(ui->get_child("p1matw"));
		str->set_string(Tim::String::to_string(draw_piece1->mat.w));
	}
	if(draw_piece2){
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p2tex"));
		str->set_string(draw_piece2->texture_name);
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p2model"));
		str->set_string(draw_piece2->modelbuffer_name);

		str=dynamic_cast<UI::EnterString*>(ui->get_child("p2matx"));
		str->set_string(Tim::String::to_string(draw_piece2->mat.x));

		str=dynamic_cast<UI::EnterString*>(ui->get_child("p2maty"));
		str->set_string(Tim::String::to_string(draw_piece2->mat.y));

		str=dynamic_cast<UI::EnterString*>(ui->get_child("p2matz"));
		str->set_string(Tim::String::to_string(draw_piece2->mat.z));

		str=dynamic_cast<UI::EnterString*>(ui->get_child("p2matw"));
		str->set_string(Tim::String::to_string(draw_piece2->mat.w));
	}


}
void Piece::update_piece_UI(UI::UI *ui){
	UI::EnterString *str=dynamic_cast<UI::EnterString*>(ui->get_child("weight"));
	weight=Tim::String::str_to_int(str->get_string());

	//str=dynamic_cast<UI::EnterString*>(ui->get_child("p1model"));
	//set_draw_piece1(str->get_string());

	//str=dynamic_cast<UI::EnterString*>(ui->get_child("p2model"));
	//set_draw_piece2(str->get_string());

	if(draw_piece1){
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p1tex"));
		draw_piece1->set_texture(str->get_string());
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p1model"));
		draw_piece1->set_model(str->get_string());

		str=dynamic_cast<UI::EnterString*>(ui->get_child("p1matx"));
		draw_piece1->mat.x=Tim::String::str_to_float(str->get_string());
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p1maty"));
		draw_piece1->mat.y=Tim::String::str_to_float(str->get_string());
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p1matz"));
		draw_piece1->mat.z=Tim::String::str_to_float(str->get_string());
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p1matw"));
		draw_piece1->mat.w=Tim::String::str_to_float(str->get_string());

	}
	if(draw_piece2){
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p2tex"));
		draw_piece2->set_texture(str->get_string());
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p2model"));
		draw_piece2->set_model(str->get_string());

		str=dynamic_cast<UI::EnterString*>(ui->get_child("p2matx"));
		draw_piece2->mat.x=Tim::String::str_to_float(str->get_string());
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p2maty"));
		draw_piece2->mat.y=Tim::String::str_to_float(str->get_string());
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p2matz"));
		draw_piece2->mat.z=Tim::String::str_to_float(str->get_string());
		str=dynamic_cast<UI::EnterString*>(ui->get_child("p2matw"));
		draw_piece2->mat.w=Tim::String::str_to_float(str->get_string());
	}
}
void Piece::get_rule_names(std::vector<std::string> &names){
	for(unsigned i=0;i<basic_rules.size();i++){
		names.push_back(basic_rules.at(i)->get_name());
	}
}
void Piece::save_script(std::string dir_path,std::string path){
	std::filebuf file;
	file.open((dir_path+path+".txt").c_str(), std::ios::out);
	if (!file.is_open()) {
		std::cerr << "Piece::save_script fail,file:" << dir_path+path
				<< " open fail" << std::endl;
		return;
	}
	std::ostream os(&file);
	if(draw_piece_str1!=""){
		os<<"draw_piece1:"<<std::endl;
		os<<"	"<<draw_piece_str1<<std::endl;
	}
	if(draw_piece_str2!=""){
		os<<"draw_piece2:"<<std::endl;
		os<<"	"<<draw_piece_str2<<std::endl;
	}

	os<<"weight:"<<std::endl;
	os<<"	"<<weight<<std::endl;
	if(!rule){
		os<<"#no_lua_rule"<<std::endl;
	}

	os<<"#END"<<std::endl;
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
	bool no_lua_rule=false;
	while(Tim::String::get_line(is, line, true, true)&&line!="#END"){
		if(line=="draw_piece1:"){
			Tim::String::get_line(is,draw_piece_str1, true, true);
		}else if(line=="draw_piece2:"){
			Tim::String::get_line(is,draw_piece_str2, true, true);
		}else if(line=="weight:"){//.lua file
			Tim::String::get_line(is, line, true, true);
			sscanf(line.c_str(),"%d",&weight);
		}else if(line=="#no_lua_rule"){
			no_lua_rule=true;
		}else if(line!=""){
			std::cerr<<"Piece::load_script unknown script:"<<line<<std::endl;
		}
	}
	if(!draw_piece1){
		if(draw_piece_str1==""){
			draw_piece_str1="chess/"+name+"_p1";
		}
		if(!Display::AllDrawObjects::get_cur_object()->find(draw_piece_str1)){
			Display::DrawObject *obj=new Display::DrawObject();
			std::vector<std::string> path_vec;
			Tim::String::split(draw_piece_str1, "/", path_vec);
			obj->name=path_vec.back();
			Display::AllDrawObjects::get_cur_object()->push(draw_piece_str1,obj);
			Display::Draw::get_cur_object()->push(obj);
		}
		set_draw_piece1(draw_piece_str1);
	}
	if(!draw_piece2){
		if(draw_piece_str2==""){
			draw_piece_str2="chess/"+name+"_p2";
		}
		if(!Display::AllDrawObjects::get_cur_object()->find(draw_piece_str2)){
			Display::DrawObject *obj=new Display::DrawObject();
			std::vector<std::string> path_vec;
			Tim::String::split(draw_piece_str2, "/", path_vec);
			obj->name=path_vec.back();
			Display::AllDrawObjects::get_cur_object()->push(draw_piece_str2,obj);
			Display::Draw::get_cur_object()->push(obj);
		}
		set_draw_piece2(draw_piece_str2);
	}
	if(rule){
		delete rule;
		rule=0;
	}
	if(!no_lua_rule){
		if(Tim::File::check_if_file_exist(dir_path+path+".lua")){
			rule=new Tim::Lua();
			rule->loadfile((dir_path+path+".lua"));
			rule->rigister_function("get_board",ChessBoard::get_board);
			rule->p_call(0,0,0);
		}
	}else{

		std::cout<<"Piece::load_script no lua rule:"<<name<<std::endl;
	}
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
	push_rule(rule);
}
void Piece::push_rule(BasicRule* rule){
	rule->parent=this;
	basic_rules.push_back(rule);
}
void Piece::load_basic_rule(std::string path){
	if(!Tim::File::check_if_file_exist(path)){// no file exist
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
		push_rule(rule);
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
	if(!rule)return;

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
		if(draw_piece1)draw_piece1->push_temp_drawdata(new Display::DrawDataObj(pos,true,true));
	}else{
		if(draw_piece2)draw_piece2->push_temp_drawdata(new Display::DrawDataObj(pos,true,true));
	}
}


} /* namespace CM */
