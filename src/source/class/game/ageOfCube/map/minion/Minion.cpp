#include "class/game/ageOfCube/map/minion/Minion.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/ageOfCube/map/Map.h"
#include "class/game/ageOfCube/map/DisplayMap.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/ageOfCube/map/ai/search/Astar.h"
#include "class/display/draw/Draw.h"
#include "class/tim/string/String.h"
#include <iostream>
namespace AOC {

Minion::Minion() {
	//std::cout<<"Minion::Minion()="<<this<<std::endl;
	minion_created=false;
	finder=0;
	timer=0;

	stuck_timer=0;
	stuck_times=0;
	colli_timer=0;
	ai=new MinionAI(this);
}
Minion::~Minion() {
	if(finder)delete finder;
	delete ai;
	//std::cout<<"Minion::~Minion()="<<this<<std::endl;
}
void Minion::save(FILE * file){
	save_unit(file);
	rigid_body.save_rigid_body(file);
	fprintf(file,"%d\n",timer);
	if(finder&&finder->get()->find){
		AI::search::FindPath* path=dynamic_cast<AI::search::FindPath*>(finder->get());
		fprintf(file,"1\n");
		path->save(file);
	}else{
		fprintf(file,"0\n");
	}
	save_minion(file);
}
void Minion::load(FILE * file){
	load_unit(file);
	rigid_body.load_rigid_body(file);
	fscanf(file,"%d\n",&timer);
	int flag;
	fscanf(file,"%d\n",&flag);
	if(flag){
		if(finder)delete finder;
		AI::search::FindPath* path=new AI::search::FindPath();
		path->load(file);
		finder=new Tim::SmartPointer<AI::search::Finder>(path);
	}
	load_minion(file);
}
double Minion::get_attack_size(){
	return rigid_body.radius;
}
math::vec3<double> Minion::get_rotate(){
	return rigid_body.rotate;
}
void Minion::create_minion(){
	minion_created=true;
	create_unit();

	push_component(&rigid_body);
	minion_create();
}
math::vec3<int> Minion::get_pos_int(){
	return math::vec3<int>(
			get_pos().x/Map::CUBE_SIZE,
			get_pos().y/Map::CUBE_SIZE,
			get_pos().z/Map::CUBE_SIZE);
}
void Minion::draw_hp(){
	int max_hp_bar=50;
	double width=0.5,height=0.1;

	double cur_hp=get_max_hp();
	int i=1;
	for(;i<=7&&cur_hp>max_hp_bar;i++){
		cur_hp*=0.5;
	}

	double hp_percent=((double)get_hp()/(double)get_max_hp());

	Display::Draw::get_cur_object()->draw_bill_board("misc/hp"+Tim::String::to_string(i),
			rigid_body.pos+math::vec3<double>(0,1.5*rigid_body.radius+0.1,0),
			math::vec2<double>(width*hp_percent,height));

}
void Minion::draw(){
	if(is_dead){
		return;
	}
	dp_pos.set_ry((180.0/M_PI)*atan2(rigid_body.vel.x,rigid_body.vel.z));
	math::vec3<double> s=Map::get_cur_object()->dp_map->dp_start;
	math::vec3<double> e=Map::get_cur_object()->dp_map->dp_end;
	math::vec3<double> pos=get_pos();
	if(pos>=s&&pos<=e){
		draw_unit();
		draw_hp();
		draw_minion();
	}else{
		//draw_minion();
		//std::cout<<"Minion::draw() not display"<<std::endl;
	}

}
void Minion::move_to(math::vec3<double> target,double vel){
	math::vec3<double>pos_del=target-get_pos();
	math::vec3<double>pos_del_xz=pos_del;
	pos_del_xz.y=0;
	rigid_body.vel*=0.85;
	rigid_body.vel+=vel*pos_del_xz.normalize();
	rigid_body.vel.y+=0.016*pos_del.normalize().y;
}
void Minion::unit_update(){
	//std::cout<<"unit_update()"<<std::endl;
	timer++;

	rigid_body.set_detect_collision();
	AI_update();
	minion_update();

	if(timer>5000)set_hp(0);
}
void Minion::find_path(){
	Unit* target;
	target=UnitController::get_cur_object()->search_unit("MainTower",rigid_body.pos);
	if(target){
		math::vec3<int>des(target->get_mid_pos_int());
		//std::cout<<"get_pos_int():"<<des.x<<","<<des.y<<","<<des.z<<std::endl;
		AI::search::FindPath *find=new AI::search::FindPath(
				rigid_body.pos,2*rigid_body.radius,des,3);
		if(finder)delete finder;

		finder=new Tim::SmartPointer<AI::search::Finder>(find);
		finder->get()->max_search_times=40000;
		finder->get()->min_search_times=2000;
		AI::search::SearchTask *task=new AOC::AI::search::SearchTask(*finder);
		AI::search::Astar::get_cur_object()->push_task(task);
	}
}
void Minion::moving(){
	AI::search::FindPath* path=dynamic_cast<AI::search::FindPath*>(finder->get());
	if(path&&path->cur_at<path->path.size()){
		if((get_pos()-(path->path.at(path->cur_at))).get_length()<0.5*Map::CUBE_SIZE){//reach!!
			path->cur_at++;
			stuck_timer=0;
		}
		if(path->cur_at<path->path.size()){
			if(rigid_body.collided_id.size()>0){
				colli_timer=10;
			}
			if(colli_timer<=0&&Map::get_cur_object()->get_cube_down(get_pos()-rigid_body.radius)->standable()){
				math::vec3<double> target=path->path.at(path->cur_at);
				move_to(target,0.008);
				stuck_timer++;
			}else{
				colli_timer--;
				rigid_body.vel.y+=gravity;
			}
		}else{
			if(finder)delete finder;
			finder=0;
			attack_main_tower();
		}
	}
}
void Minion::attack_main_tower(){
	Unit* target;
	target=UnitController::get_cur_object()->search_unit("MainTower",rigid_body.pos);
	if(target){
		target->hp_alter(-500);
		set_hp(0);
	}
}
void Minion::move(){
	if(stuck_timer>100){
		stuck_times++;
		stuck_timer=0;
		if(stuck_times<2){
			find_path();
		}else{
			if(finder&&finder->get()->search_done){
				delete finder;
				finder=0;
			}
		}
	}
	if(timer==50){
		//std::cout<<"Ball::minion_update() find path timer="<<timer<<std::endl;
		find_path();
		//std::cout<<"Ball::minion_update() find path end"<<std::endl;
	}
	if(finder&&(*finder)->search_done){
		if((*finder)->find){
			moving();
		}else{
			if(finder&&finder->get()->search_done){
				delete finder;
				finder=0;
			}
		}
	}else{
		rigid_body.vel.y+=gravity;
	}
}
void Minion::AI_update(){
	move();
}
} /* namespace AOC */
