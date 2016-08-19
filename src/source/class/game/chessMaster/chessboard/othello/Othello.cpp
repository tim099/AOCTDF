#include "class/game/chessMaster/chessboard/othello/Othello.h"
#include "class/game/chessMaster/chessboard/othello/OthelloRule.h"
#include "class/game/chessMaster/chessboard/othello/piece/OthelloStone.h"
#include "class/game/chessMaster/chessboard/othello/piece/OthelloSkipStone.h"
#include <iostream>
namespace CM {

Othello::Othello() {
	dir_path="files/game/chessMaster/game/othello/";
	game_name="Othello";
	init_drawobject();

	create_pieces();

	load_board(dir_path+"chessBoard/board.txt");
	cube_type_num=2;

	tex_path="chess/board_textures";
	normal_path="chess/board_normals";

	dboard->init_drawObject("",tex_path,normal_path,true);
	if(rule)delete rule;
	rule=new CM::OthelloRule();
	load_mct();
}
Othello::~Othello() {

}
int Othello::evaluate_score(CM::Board<short int> *chess_board,int player){
	int score=0;
	int base_score;
	for(unsigned i=0;i<8;i++){
		for(unsigned j=0;j<8;j++){
			base_score=1;
			if(i==0||i==7){
				base_score=8;
			}
			if(j==0||j==7){
				base_score*=8;
			}

			score+=base_score*player*chess_board->get(i,j);

		}
	}
	return score;
}
void Othello::create_pieces(){
	pieces.push_back(new OthelloStone());
	pieces.push_back(new OthelloSkipStone());
}
} /* namespace CM */
