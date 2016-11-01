#include "class/game/ageOfCube/map/attack/railgun/Bullet.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/display/draw/Draw.h"
#include "class/game/ageOfCube/map/unit/Unit.h"
#include "class/audio/AudioController.h"
#include "class/display/light/LightControl.h"
namespace AOC {

Bullet::Bullet() {
	timer=0;
	explode_timer=0;
	//be_collide_off=true;
	speed=0.3f;
}
Bullet::~Bullet() {

}
void Bullet::save_attack(FILE* file){
	fprintf(file,"%d %d\n",timer,explode_timer);
}
void Bullet::load_attack(FILE* file){
	fscanf(file,"%d %d\n",&timer,&explode_timer);
}
Display::DrawObject* Bullet::get_bullet_drawobj(){
	return Display::AllDrawObjects::get_cur_object()->get("attack/cube_missile_1");
}
void  Bullet::explode(){
	//std::cout<<"Missile::explode()"<<std::endl;
	bool exploded=false;
	for(unsigned i=0;i<collied_units.size();i++){
		if(target==collied_units.at(i)){
			damage_target(damage);
			exploded=true;
		}else if(collied_units.at(i)->get_player()==target->get_player()){
			collied_units.at(i)->hp_alter(-damage);
			exploded=true;
		}
	}
	/*
	Attack* attack=AttackCreator::get_cur_object()->create("Bullet");
	attack->radius=radius;
	attack->pos=pos;
	attack->vel=vel+math::vec3<>(0,0,0);
	attack->set_target(target);
	attack->set_damage(damage);
	attack->set_player(player_id);
	attack->create_attack();
	*/
	if(exploded){
		Audio::AudioController::get_cur_object()->
				play_by_dis("default_sound_effect/Bomb.wav",pos,100);
		explode_timer++;
	}
}
void Bullet::draw_attack(){
	if(explode_timer){
		Display::PointLight *light=new Display::PointLight(
				glm::vec3(pos.x,pos.y,pos.z),
				glm::vec3(fabs(4.0-explode_timer)*8.0,1.0,1.0),false);
		Display::Draw::get_cur_object()->lightControl->push_temp_light(light);
	}else{
		Display::DrawObject *missile_Drawobj=get_bullet_drawobj();
		math::Position *dp_pos=new math::Position();
		dp_pos->set_pos(glm::vec3(pos.x,pos.y,pos.z));
		dp_pos->set_scale(glm::vec3(2*radius,2*radius,2*radius));
		dp_pos->set_r(glm::vec3((180.0/M_PI)*atan2(sqrt(vel.x*vel.x+vel.z*vel.z),vel.y),
				(180.0/M_PI)*atan2(vel.x,vel.z),0));
		missile_Drawobj->push_temp_drawdata(new Display::DrawDataObj(dp_pos,true,true));
	}

}
void Bullet::fire(){
	if(!target)return;
	math::vec3<double> del_vec=(target->get_mid_pos()-pos);
	double time_require=del_vec.get_length()/speed;
	math::vec3<double> del_vec2=(target->get_mid_pos()+time_require*target->get_speed()-pos);
	this->vel=speed*del_vec2.normalize();
}
void Bullet::attack_update(){
	if(explode_timer){
		explode_timer++;
		if(explode_timer>3)die=true;
		return;
	}
	timer++;
	vel.y-=0.05;

	if(timer<10){//(target->get_mid_pos()-pos).get_length()>3.0
		collision_off=true;
	}else{
		collision_off=false;
	}
	if(((be_collided==true||collided==true)&&collied_units.size())){
		explode();
	}
	if(timer>1000){
		die=true;
	}
}
} /* namespace AOC */
