#ifndef SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEPLAY_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEPLAY_H_
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/game/scene/Scene.h"
#include "class/display/UI/UI.h"
#include "class/display/UI/page/PageControl.h"
#include "class/display/camera/Camera.h"
#include "class/game/chessMaster/piece/Step.h"
#include "class/tim/array/vector.h"
#include "class/audio/AudioPlayer.h"

namespace CM {
class AI;
namespace scene{
class ScenePlay: public Scene {
	static const int MAX=999999;
public:
	ScenePlay();
	virtual ~ScenePlay();
	virtual std::string scene_name()const{
		return "ScenePlay";
	}
	virtual void pause();


	virtual void resume();//define behavior when this scene resume from pause state

	virtual void loading();
	virtual void scene_update_end();
	std::string local_path;
protected:
	void init_board();
	virtual void scene_update();
	virtual void scene_draw();
	virtual void scene_initialize();
	virtual	void scene_terminate();
	virtual void handle_signal(Input::Signal *sig);
	void player_move_chess();
	void handle_input();
	void camera_control();
	void draw_step();
	void draw_prev_step();
	void draw_AI_difficulty();
	void draw_board_data();
	void restart();
	void AI_move(int player);
	void AI_update();
	void next_turn(CM::Step step);

	math::Position back_ground_pos;
	UI::UI *UI;
	UI::UI *promotedUI;
	ChessBoard *chess_board;
	Display::Camera* camera;
	Display::Camera* p1camera,*p2camera;
	Audio::AudioPlayer *back_music;
	CM::AI *ai;

	Display::LightControl* lightControl;
	Tim::vector<CM::Step> next_step;
	CM::Step *selected_step;
	int simulation_times;
	bool selected;
	bool promoting;
	bool player_move;
	math::vec2<int> prev_s,s;
	int difficulty;
	int AI_mode;
	bool lock_camera;
};
}
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEPLAY_H_ */
