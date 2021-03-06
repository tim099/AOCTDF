#include "class/game/chessMaster/scene/SceneStart.h"
#include "class/game/chessMaster/common.h"


#include "class/game/chessMaster/chessboard/chineseChess/ChineseChess.h"
#include "class/game/chessMaster/chessboard/renju/Renju.h"
#include "class/display/light/LightControl.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
#include "class/game/chessMaster/AI/AI.h"
#include "class/tim/math/Position.h"
#include "class/tim/string/String.h"
#include "class/display/draw/drawObject/drawData/drawDateEX/SkyMap.h"
#include "class/audio/AudioController.h"
#include "class/game/chessMaster/scene/ScenePlay.h"
#include "class/game/chessMaster/scene/SceneEdit.h"
#include "class/game/chessMaster/scene/SceneMultiPlayer.h"
#include "class/game/chessMaster/scene/SceneCreateGame.h"
#include <stdlib.h>
#include <time.h>
namespace CM {
namespace scene{
SceneStart::SceneStart() {
	UI = 0;
	local_path = std::string("scene/start/");
	back_music=0;
}
SceneStart::~SceneStart() {

}
void SceneStart::scene_initialize() {
	//draw->Enable3D=false;
	back_music=new Audio::AudioPlayer();
	back_music->set_source("default_music/prepare_your_swords.wav");
	back_music->set_volume(0.2);
	back_music->set_loop(true);

	resume();
	//std::cout<<"SceneStart::scene_initialize() 2"<<std::endl;
}
void SceneStart::loading(){

}
void SceneStart::scene_terminate() {
	if(back_music){
		delete back_music;
	}
	if(UI){
		delete UI;
		UI=0;
	}
}
void SceneStart::pause(){
	if(UI){
		delete UI;
		UI=0;
	}
	back_music->pause();
}
void SceneStart::resume(){
	std::cout<<"SceneStart::resume()"<<std::endl;
	if(UI){
		delete UI;
		UI=0;
	}
	UI = new UI::UI(CM::folder_path+local_path+"UI/UI.txt");
	back_music->play();
	draw->Enable3D = false;
}
void SceneStart::handle_signal(Input::Signal *sig){
	if(sig->get_data()=="edit_chess"){
		Input::Signal sig("push_scene","Game");
		sig.ex_data=new SceneEdit();
		sig.sent();
	}else if(sig->get_data()=="play_chess"){
		Input::Signal sig("push_scene","Game");
		sig.ex_data=new ScenePlay();
		sig.sent();
	}else if(sig->get_data()=="multi_player"){
		Input::Signal sig("push_scene","Game");
		sig.ex_data=new SceneMultiPlayer();
		sig.sent();
	}else if(sig->get_data()=="create_game"){
		Input::Signal sig("push_scene","Game");
		sig.ex_data=new SceneCreateGame();
		sig.sent();
	}
}
void SceneStart::handle_input(){

}
void SceneStart::scene_update(){
	UI->update_UIObject();
}
void SceneStart::scene_draw(){
	UI->draw_UIObject(draw);
}


}
} /* namespace CM */
