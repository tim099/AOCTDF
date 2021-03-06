#ifndef SOURCE_CLASS_GAME_SCENE_SCENE_H_
#define SOURCE_CLASS_GAME_SCENE_SCENE_H_
#include <string>
#include "class/input/Input.h"
#include "class/tim/thread/ThreadPool.h"
#include "class/controller/ControllerSystem.h"
#include "class/display/draw/Draw.h"
#include "class/input/signal/Receiver.h"

class Scene {
public:
	Scene();
	void initialize(Display::Draw* draw,Input::Input* input,Tim::ThreadPool *thread_pool);
	void terminate();
	virtual ~Scene();

	virtual void loading(){//provide for some loading which took long time

	}

	virtual std::string scene_name()const=0;

	//define behavior when other scene switch to active scene, and pause this scene
	virtual void pause(){

	}

	//define behavior when this scene resume from pause state
	virtual void resume(){

	}
	//this function will be called by Game after controller_system updated
	virtual void scene_update_end(){}

	void update();
	void draw_scene();

protected:
	virtual void scene_update()=0;
	virtual void scene_draw()=0;
	virtual void scene_initialize()=0;
	virtual	void scene_terminate()=0;

	virtual void handle_signal(Input::Signal *sig);

	void get_signal();

	Display::Draw* draw;
	Input::Input* input;
	Input::Receiver* receiver;
	Tim::ThreadPool *thread_pool;
};

#endif /* SOURCE_CLASS_GAME_SCENE_SCENE_H_ */
