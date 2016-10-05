#include "class/game/chessMaster/piece/basicRule/IF.h"

#include "class/display/draw/Draw.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/tim/string/String.h"
#include "class/display/UI/string/EnterString.h"
#include "class/tim/string/String.h"
#include "class/game/chessMaster/piece/basicRule/BasicRuleCreator.h"
#include "class/game/chessMaster/piece/basicRule/condition/ConditionCreator.h"
#include "class/display/UI/page/AutoPageControl.h"
#include "class/display/UI/string/UIString.h"
#include "class/input/Input.h"
namespace CM {

IF::IF() {
	selected_rule=0;
	selected_condition=0;
	ui=new UI::UI(CM::folder_path+"basicRule/"+get_name()+"/UI.txt");
	true_mode=true;
}
IF::~IF() {
	delete ui;

	for(unsigned i=0;i<true_rules.size();i++){
		delete true_rules.at(i);
	}
	for(unsigned i=0;i<false_rules.size();i++){
		delete false_rules.at(i);
	}
	for(unsigned i=0;i<conditions.size();i++){
		delete conditions.at(i);
	}
}
void IF::save(FILE* file){
	fprintf(file,"conditions_number=%u\n",conditions.size());
	for(unsigned i=0;i<conditions.size();i++){
		fprintf(file,"%s\n",conditions.at(i)->get_name().c_str());
		conditions.at(i)->save(file);
	}

	fprintf(file,"true_rules_number=%u\n",true_rules.size());
	for(unsigned i=0;i<true_rules.size();i++){
		fprintf(file,"%s\n",true_rules.at(i)->get_name().c_str());
		true_rules.at(i)->save(file);
	}

	fprintf(file,"false_rules_number=%u\n",false_rules.size());
	for(unsigned i=0;i<false_rules.size();i++){
		fprintf(file,"%s\n",false_rules.at(i)->get_name().c_str());
		false_rules.at(i)->save(file);
	}

}
void IF::load(FILE* file){

	unsigned rule_number;
	char name[100];

	///*
	fscanf(file,"conditions_number=%u\n",&rule_number);
	for(unsigned i=0;i<rule_number;i++){
		fscanf(file,"%s\n",name);
		Condition* rule=ConditionCreator::get_cur_object()->create(name);
		rule->load(file);
		conditions.push_back(rule);
	}
	//*/

	fscanf(file,"true_rules_number=%u\n",&rule_number);
	for(unsigned i=0;i<rule_number;i++){
		fscanf(file,"%s\n",name);
		BasicRule* rule=BasicRuleCreator::get_cur_object()->create(name);
		rule->load(file);
		true_rules.push_back(rule);
	}

	fscanf(file,"false_rules_number=%u\n",&rule_number);
	for(unsigned i=0;i<rule_number;i++){
		fscanf(file,"%s\n",name);
		BasicRule* rule=BasicRuleCreator::get_cur_object()->create(name);
		rule->load(file);
		false_rules.push_back(rule);
	}
}
void IF::get_next_step(CM::Board<short int> *chess_board,
		int x,int y,std::vector<int> &next_step,int player){

	bool flag=true;
	for(unsigned i=0;i<conditions.size();i++){
		bool cond=conditions.at(i)->get_condition(chess_board,x,y,player);
		if(!cond){
			flag=false;
		}else{
			flag=true;
		}
		if((!flag&&conditions.at(i)->do_and)||(flag&&!conditions.at(i)->do_and)){
			break;
		}

	}

	if(flag){
		for(unsigned i=0;i<true_rules.size();i++){
			true_rules.at(i)->get_next_step(chess_board,x,y,next_step,player);
		}
	}else{
		for(unsigned i=0;i<false_rules.size();i++){
			false_rules.at(i)->get_next_step(chess_board,x,y,next_step,player);
		}
	}

}
void IF::draw_rule(CM::Board<short int> *chess_board,
		int x,int y){
	Tim::vector<CM::Step> next_steps;
	next_step(chess_board,x,y,next_steps);
	for(unsigned i=0;i<next_steps.size();i++){
		next_steps[i].draw_next_step();
	}
	for(unsigned i=0;i<conditions.size();i++){
		conditions.at(i)->draw(x,y);
	}

}
void IF::draw_UI(){
	Display::Draw *draw=Display::Draw::get_cur_object();
	ui->draw_UIObject(draw);
	if(selected_rule){
		selected_rule->draw_UI();
	}
	if(selected_condition){
		selected_condition->draw_UI();
	}
}
bool IF::get_edit_done(){
	if(!selected_rule&&!selected_condition){
		return true;
	}
	if(selected_condition){
		selected_condition=0;
		return false;
	}
	if(selected_rule&&!selected_rule->get_edit_done()){
		return false;
	}
	selected_rule=0;
	return false;
}
bool IF::get_remove_rule(){
	if(!selected_rule&&!selected_condition)return true;


	if(selected_rule){
		if(!selected_rule->get_remove_rule()){
			return false;
		}
		for(unsigned i=0;i<true_rules.size();i++){
			if(true_rules.at(i)==selected_rule){
				delete selected_rule;
				selected_rule=0;
				true_rules.at(i)=true_rules.back();
				true_rules.pop_back();
				return false;
			}
		}
		for(unsigned i=0;i<false_rules.size();i++){
			if(false_rules.at(i)==selected_rule){
				delete selected_rule;
				selected_rule=0;
				false_rules.at(i)=false_rules.back();
				false_rules.pop_back();
				return false;
			}
		}
	}
	if(selected_condition){
		for(unsigned i=0;i<conditions.size();i++){
			if(conditions.at(i)==selected_condition){
				delete selected_condition;
				selected_condition=0;
				conditions.at(i)=conditions.back();
				conditions.pop_back();
				return false;
			}
		}
	}
	return false;
}
void IF::add_rule(std::string rule_name){
	BasicRule* rule=BasicRuleCreator::get_cur_object()->create(rule_name);
	if(true_mode){
		true_rules.push_back(rule);
	}else{
		false_rules.push_back(rule);
	}
}
void IF::add_condition(std::string rule_name){
	Condition* condition=ConditionCreator::get_cur_object()->create(rule_name);
	conditions.push_back(condition);
}
void IF::get_rule_names(std::vector<std::string> &names){
	if(true_mode){
		for(unsigned i=0;i<true_rules.size();i++){
			names.push_back(true_rules.at(i)->get_name());
		}
	}else{
		for(unsigned i=0;i<false_rules.size();i++){
			names.push_back(false_rules.at(i)->get_name());
		}
	}

}
void IF::get_condition_names(std::vector<std::string> &names){
	for(unsigned i=0;i<conditions.size();i++){
		names.push_back(conditions.at(i)->get_name());
	}
}
void IF::deselected(){
	if(selected_rule){
		selected_rule->deselected();
	}
	selected_rule=0;
	selected_condition=0;
}
void IF::update(){
	if(selected_rule){
		selected_rule->update();
	}
	if(selected_condition){
		selected_condition->update();
	}

	Input::Input *input=Input::Input::get_cur_object();
	while(Input::Signal*sig=input->get_signal("add_rule")){
		add_rule(sig->get_data());
	}
	while(Input::Signal*sig=input->get_signal("if_add_condition")){
		add_condition(sig->get_data());
	}
	while(Input::Signal*sig=input->get_signal("rule_if")){
		if(sig->get_data()=="switch_if"){
			true_mode=true;
		}else if(sig->get_data()=="switch_else"){
			true_mode=false;
		}
	}
	while(Input::Signal*sig=input->get_signal("if_edit_rule")){
		unsigned num=Tim::String::str_to_int(sig->get_data());
		if(true_mode){
			if(num<true_rules.size()){
				selected_rule=true_rules.at(num);
				selected_condition=0;
			}
		}else{
			if(num<false_rules.size()){
				selected_rule=false_rules.at(num);
				selected_condition=0;
			}
		}

	}
	while(Input::Signal*sig=input->get_signal("if_edit_condition")){
		unsigned num=Tim::String::str_to_int(sig->get_data());
		if(num<conditions.size()){
			selected_condition=conditions.at(num);
			if(selected_rule){
				selected_rule->deselected();
				selected_rule=0;
			}
		}
	}
}
void IF::update_UI(){
	UI::AutoPageControl *page;
	page=dynamic_cast<UI::AutoPageControl*>(ui->get_child("rules_page"));
	if(page){
		std::vector<std::string> names;
		std::vector<std::string> sigs;
		get_rule_names(names);
		for(unsigned i=0;i<names.size();i++){
			sigs.push_back(Tim::String::to_string(i));
		}
		page->create_pages(names,&sigs);
	}
	page=dynamic_cast<UI::AutoPageControl*>(ui->get_child("conditions_page"));
	if(page){
		std::vector<std::string> names;
		std::vector<std::string> sigs;
		get_condition_names(names);
		for(unsigned i=0;i<names.size();i++){
			sigs.push_back(Tim::String::to_string(i));
		}
		page->create_pages(names,&sigs);
	}
	//
	UI::UIString *ui_str;
	ui_str=dynamic_cast<UI::UIString*>(ui->get_child("statement"));
	if(true_mode){
		ui_str->set_string("if rules");
	}else{
		ui_str->set_string("else rules");
	}
	ui->update_UIObject();

	if(selected_rule){
		selected_rule->update_UI();
	}
	if(selected_condition){
		selected_condition->update_UI();
	}
}
} /* namespace CM */
