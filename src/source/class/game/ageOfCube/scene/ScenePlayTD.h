#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEPLAYTD_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEPLAYTD_H_

#include "class/game/scene/Scene.h"
#include "class/game/ageOfCube/field/Field.h"
#include "class/display/camera/Camera.h"
#include "class/display/UI/UI.h"
#include "class/game/timer/Timer.h"
#include "class/display/light/LightControl.h"
#include "class/game/ageOfCube/map/unit/UnitController.h"
#include "class/game/ageOfCube/player/Player.h"
#include "class/audio/AudioPlayer.h"

namespace AOC {

enum playMode{
	normal, constructing, removing
};
class Building;
class ScenePlayTD : public Scene{
public:
	ScenePlayTD(std::string _map_name, glm::ivec3 _map_size);
	virtual ~ScenePlayTD();
	virtual std::string scene_name()const{
		return "ScenePlayTD";
	}
	virtual void loading();
	virtual void pause();
	virtual void resume();
	virtual void scene_update_end();
	void reload_map();
protected:
	virtual void scene_update();

	virtual void scene_draw();

	virtual void scene_initialize();
	virtual	void scene_terminate();

	virtual void handle_signal(Input::Signal *sig);

	void camera_control();
	void handle_input();
	Field* field;
	Display::Camera *camera;
	Display::LightControl* lightControl;
	Display::CubeLight* cl;

	Audio::AudioPlayer *back_music;
	UI::UI *UI;
	std::string map_name;
	Building* constructing_building;
	playMode mode;
	glm::ivec3 map_size;
	bool pause_timer;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_SCENE_SCENEPLAYTD_H_ */
