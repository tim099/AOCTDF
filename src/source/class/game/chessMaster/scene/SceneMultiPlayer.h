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
namespace CM {

class SceneMultiPlayer {
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

};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_SCENE_SCENEMULTIPLAYER_H_ */
