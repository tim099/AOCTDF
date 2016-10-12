/*
 * Age Of Cube TowerDefense
 * Copyright (C) 2016, Tim Yeh<tim11251994@gmail.com>
 *					   LukeWu<apple894894@gmail.com>
 */


//#include "class/test/Test.h"

#include <iostream>
//#include <thread>
#include "class/game/ageOfCube/AgeOfCubes.h"
#include "class/game/chessMaster/ChessMaster.h"
#include "class/game/GamePlayer.h"
int main(){
	game::GamePlayer player;
	player.play(new ChessMaster());
	//player.play(new AOC::AgeOfCubes());
	//std::cout<<"main()"<<std::endl;
    return 0;
}
