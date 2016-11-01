#include "class/game/chessMaster/chessboard/darkChess/DarkChess.h"
#include "class/game/chessMaster/chessboard/darkChess/DarkChessRule.h"

#include "class/game/chessMaster/chessboard/darkChess/piece/Dark.h"
#include "class/game/chessMaster/chessboard/darkChess/piece/General.h"
#include "class/game/chessMaster/chessboard/darkChess/piece/Advisor.h"
#include "class/game/chessMaster/chessboard/darkChess/piece/Soildier.h"
#include "class/game/chessMaster/chessboard/darkChess/piece/Cannon.h"
#include "class/game/chessMaster/chessboard/darkChess/piece/Chariot.h"
#include "class/game/chessMaster/chessboard/darkChess/piece/Elephant.h"
#include "class/game/chessMaster/chessboard/darkChess/piece/Horse.h"
#include <cstdlib>
#include <ctime>
namespace CM {
namespace darkChess {
DarkChess::DarkChess() {
	dir_path="files/game/chessMaster/game/darkChess/";
	game_name="darkChess";
	board_size=math::vec2<int>(8,4);
	init_drawobject();

	//rule_path=dir_path+"chessBoard/rule.lua";

	create_pieces();

	load_board(dir_path+"chessBoard/board.txt");
	cube_type_num=6;

	tex_path="chess/board_textures";
	normal_path="chess/board_normals";

	dboard->init_drawObject("",tex_path,normal_path,true);
	if(rule)delete rule;
	rule=new DarkChessRule();
	load_mct();
	srand(time(NULL));
	both_selectable_piece.push_back(1);
	table_pos.set_pos(glm::vec3(0.5*chess_board->sizex,-6,0.5*chess_board->sizey));
}
DarkChess::~DarkChess() {

}
void DarkChess::create_pieces(){
	push_piece(new Dark());
	push_piece(new Soildier());

	push_piece(new Cannon());

	push_piece(new Horse());
	push_piece(new Chariot());
	push_piece(new Elephant());
	push_piece(new Advisor());
	push_piece(new General());
	init_pieces();

}
}
} /* namespace CM */
