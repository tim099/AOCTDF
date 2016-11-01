#include "class/game/chessMaster/chessboard/chineseChess/ChineseChess.h"

#include "class/game/chessMaster/chessboard/chineseChess/ChineseChessRule.h"
#include "class/game/chessMaster/chessboard/chineseChess/piece/Advisor.h"
#include "class/game/chessMaster/chessboard/chineseChess/piece/Cannon.h"
#include "class/game/chessMaster/chessboard/chineseChess/piece/Chariot.h"
#include "class/game/chessMaster/chessboard/chineseChess/piece/Elephant.h"
#include "class/game/chessMaster/chessboard/chineseChess/piece/General.h"
#include "class/game/chessMaster/chessboard/chineseChess/piece/Horse.h"
#include "class/game/chessMaster/chessboard/chineseChess/piece/Soildier.h"
namespace CM {

ChineseChess::ChineseChess() {
	dir_path="files/game/chessMaster/game/chineseChess/";
	game_name="chineseChess";
	board_size=math::vec2<int>(9,9);
	init_drawobject();

	create_pieces();

	load_board(dir_path+"chessBoard/board.txt");
	cube_type_num=21;

	tex_path="chineseChess/board_textures";
	normal_path="chineseChess/board_normals";

	dboard->init_drawObject("",tex_path,normal_path,true);
	if(rule)delete rule;
	rule=new CM::ChineseChessRule();
	load_mct();
	table_pos.set_pos(glm::vec3(0.5*chess_board->sizex,-6,0.5*chess_board->sizey));
	//rule->load_rule(rule_path);
}
ChineseChess::~ChineseChess() {

}
void ChineseChess::create_pieces(){
	push_piece(new General());
	push_piece(new Advisor());
	push_piece(new Elephant());
	push_piece(new Horse());
	push_piece(new Chariot());
	push_piece(new Cannon());
	push_piece(new Soildier());
	init_pieces();
}
} /* namespace CM */
