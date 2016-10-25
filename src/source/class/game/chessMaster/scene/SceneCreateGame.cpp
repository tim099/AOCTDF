#include "class/game/chessMaster/scene/SceneCreateGame.h"

#include "class/game/chessMaster/chessboard/ChessBoard.h"

#include "class/game/chessMaster/common.h"
#include "class/display/UI/string/EnterString.h"
#include "class/tim/string/String.h"

#include "class/game/chessMaster/scene/SceneEdit.h"
namespace CM {
namespace scene{
SceneCreateGame::SceneCreateGame() {
	UI=0;
	local_path = std::string("scene/createGame/");
}
SceneCreateGame::~SceneCreateGame() {

}
void SceneCreateGame::scene_initialize(){
	resume();
}
void SceneCreateGame::scene_terminate(){
	if(UI){
		delete UI;
		UI=0;
	}
}
void SceneCreateGame::pause(){

}
void SceneCreateGame::resume(){
	if(UI){
		delete UI;
		UI=0;
	}
	UI=new UI::UI(CM::folder_path+local_path+"UI/UI.txt");
}
void SceneCreateGame::create_game(){
	UI::EnterString *str=dynamic_cast<UI::EnterString*>(UI->get_child("chessBoardSizex"));
	int x=Tim::String::str_to_int(str->get_string());
	str=dynamic_cast<UI::EnterString*>(UI->get_child("chessBoardSizey"));
	int y=Tim::String::str_to_int(str->get_string());
	str=dynamic_cast<UI::EnterString*>(UI->get_child("chessName"));
	std::string game_name=str->get_string();
	std::cout<<"SceneCreateGame::create_game() game="<<game_name<<",x="<<x<<",y="<<y<<std::endl;
	std::string game_path=CM::folder_path+"game/"+game_name;

	if(!Tim::File::check_if_dir_exist(game_path)){
		Tim::File::create_dir(game_path);
	}
	Tim::File::copy_folder(CM::folder_path+"gametemplate/chessBoard",game_path);
	Tim::File::copy_folder(CM::folder_path+"gametemplate/drawobject",game_path);
	Tim::File::copy_folder(CM::folder_path+"gametemplate/model",game_path);
	Tim::File::copy_folder(CM::folder_path+"gametemplate/textures",game_path);

	ChessBoard* board=new ChessBoard(x,3,y);
	board->dir_path=game_path+"/";
	board->save_board(board->dir_path+"chessBoard/board.txt");
	delete board;
	{
		Input::Signal sig("pop_scene","Game");
		sig.sent();
	}
	{
		Input::Signal sig("push_scene","Game");
		SceneEdit* scene=new SceneEdit();
		scene->init_game=game_name;
		sig.ex_data=scene;

		sig.sent();
	}

}
void SceneCreateGame::loading(){

}
void SceneCreateGame::scene_update(){
	UI->update_UIObject();
}
void SceneCreateGame::scene_draw(){
	UI->draw_UIObject(draw);
}
void SceneCreateGame::handle_signal(Input::Signal *sig){
	if(sig->get_data()=="createGame"){
		create_game();
	}
}
void SceneCreateGame::handle_input(){

}
}
} /* namespace CM */
