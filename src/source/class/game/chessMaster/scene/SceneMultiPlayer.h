#ifndef SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEMULTIPLAYER_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEMULTIPLAYER_H_
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/game/scene/Scene.h"
#include "class/display/UI/UI.h"
#include "class/display/UI/page/PageControl.h"
#include "class/display/camera/Camera.h"
#include "class/game/chessMaster/piece/Step.h"
#include "class/tim/array/vector.h"
#include "class/audio/AudioPlayer.h"
#include "class/network/Server.h"
#include "class/network/Client.h"
namespace CM {

class SceneMultiPlayer : public Scene{
	static const int MAX=999999;
public:
	SceneMultiPlayer();
	virtual ~SceneMultiPlayer();

	virtual std::string scene_name()const{
		return "SceneMultiPlayer";
	}
	virtual void pause();

	virtual void resume();//define behavior when this scene resume from pause state

	virtual void loading();
	virtual void scene_update_end();
	std::string local_path;
protected:
	virtual void scene_initialize();
	virtual	void scene_terminate();
	virtual void scene_update();
	virtual void scene_draw();
	virtual void handle_signal(Input::Signal *sig);
	void restart();
	void init_board();
	void camera_control();
	void draw_step();
	void handle_input();
	void player_move_chess();
	void next_turn(CM::Step step);
	void switch_chess(std::string str);
	void handle_receive_data();
	void handle_receive_data(std::string str);
	void undo();
	bool promoting;
	UI::UI *promotedUI;
	CM::Step *selected_step;
	math::vec2<int> s;
	game::network::Client *client;
	game::network::Server *server;
	bool selected;
	bool player_move;
	Tim::vector<CM::Step> next_step;

	math::Position back_ground_pos;
	Display::LightControl* lightControl;
	Display::Camera* p1camera,*p2camera;
	Display::Camera* camera;
	ChessBoard *chess_board;
	UI::UI *UI;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEMULTIPLAYER_H_ */
