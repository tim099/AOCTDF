#include "class/game/ageOfCube/AgeOfCubes.h"
#include "class/game/ageOfCube/scene/SceneStart.h"
#include <windows.h>
#include <iostream>
namespace AOC{
AgeOfCubes::AgeOfCubes() {
	textures = 0;
	modelBuffers = 0;
	drawObjects = 0;
	audioSources = 0;
	folder_path="files/AgeOfCube/";
}
void AgeOfCubes::initialize_game(){

	//============================
	textures = new Display::AllTextures(folder_path+"texture/script/loadAllTexture.txt");
	textures->register_cur();	//set as cur using textures

	modelBuffers=new Display::AllModelBuffers(folder_path+"/models/script/loadAllModelBuffers.txt");
	modelBuffers->register_cur();

	drawObjects = new Display::AllDrawObjects(folder_path+"/drawObject/loadAllDrawObjects.txt");
	drawObjects->register_cur();

	//Display::DrawObjectMap* dobj = new Display::DrawObjectMap("files/test/dobj/default.txt");

	//Display::DrawObject* obj=new Display::DrawObject("default/cube","default/stars");
	//obj->name="testhaha";
	//dobj->push(obj);
	//dobj->Save_script("files/test/dobj/default.txt");
	//delete dobj;


	audioSources = new Audio::AllAudioSources(folder_path+"/audio/loadAllAudios.txt");
	audioSources->register_cur();

	push_scene(new AOC::SceneStart());
	/*std::string map_name = "TDF0";
	std::string map_folder_path="files/AgeOfCube/maps/";
	Input::Signal *sig=new Input::Signal("push_scene","Game");
	sig->ex_data=new AOC::SceneStart();
	sig->sent();*/

}
AgeOfCubes::~AgeOfCubes() {
	//all handle by AgeOfCubes::terminate_game()
}
void AgeOfCubes::terminate_game(){
	//delete in reverse of create order
	std::cout<<"terminate game start"<<std::endl;
	delete audioSources;
	delete drawObjects;
	delete modelBuffers;
	delete textures;
	//==================

	std::cout<<"terminate game end"<<std::endl;
}
void AgeOfCubes::game_update(){



}
}
