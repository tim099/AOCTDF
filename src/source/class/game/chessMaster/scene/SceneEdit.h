#ifndef SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEEDIT_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEEDIT_H_

#include "class/game/scene/Scene.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/display/UI/UI.h"
#include "class/display/UI/page/PageControl.h"
#include "class/display/camera/Camera.h"
#include "class/game/chessMaster/piece/Step.h"
#include "class/tim/array/vector.h"
#include "class/audio/AudioPlayer.h"
namespace CM {
namespace scene{
class SceneEdit: public Scene {
public:
	SceneEdit();
	virtual ~SceneEdit();
	virtual std::string scene_name()const{
		return "SceneEdit";
	}

	virtual void pause();
	/*
	 * define behavior when this scene resume from pause state
	 */
	virtual void resume();

	virtual void loading();
	virtual void scene_update_end();
	std::string init_game;
	std::string local_path;
protected:
	virtual void scene_update();

	virtual void scene_draw();

	virtual void scene_initialize();
	virtual	void scene_terminate();
	virtual void handle_signal(Input::Signal *sig);

	void set_chess_board(ChessBoard* board);
	void set_selected_rule(BasicRule* selected_rule);
	void set_selected_piece(Piece *piece);
	void handle_input();
	void camera_control();
	void add_piece();

	void init_board();


	void set_chess_type(int type);
	void load_UI();
	enum Mode{
		edit_piece,edit_board,edit_rule,import_texture
	};

	Mode mode;

	math::Position back_ground_pos;
	UI::UI *UI;
	UI::UI *edit_chess_UI;
	UI::UI *edit_board_UI;
	UI::UI *edit_rule_UI;
	UI::UI *import_texture_UI;
	UI::UI *rule_UI;

	ChessBoard *chess_board;
	Piece *selected_piece;
	glm::ivec2 piece_at;
	BasicRule* selected_rule;
	Display::Camera* camera;
	Audio::AudioPlayer *back_music;


	Display::LightControl* light_control;

	bool destruct_mode;
	int type;
	int chess_type;
	glm::ivec2 s;
};
}
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEEDIT_H_ */
