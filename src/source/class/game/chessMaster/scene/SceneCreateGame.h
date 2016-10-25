#ifndef SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENECREATEGAME_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENECREATEGAME_H_

#include "class/game/scene/Scene.h"
#include "class/display/UI/UI.h"
#include "class/tim/file/File.h"
namespace CM {
namespace scene{
class SceneCreateGame: public Scene {
public:
	SceneCreateGame();
	virtual ~SceneCreateGame();

	virtual std::string scene_name()const{
		return "SceneCreateGame";
	}

	virtual void pause();
	virtual void resume();

	virtual void loading();
protected:
	virtual void scene_update();
	virtual void scene_draw();

	virtual void scene_initialize();
	virtual	void scene_terminate();
	virtual void handle_signal(Input::Signal *sig);

	void create_game();
	void handle_input();
	std::string local_path;
	UI::UI *UI;
};
}
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENECREATEGAME_H_ */
