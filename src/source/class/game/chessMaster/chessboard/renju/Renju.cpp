#include "class/game/chessMaster/chessboard/renju/Renju.h"
#include "class/game/chessMaster/chessboard/renju/piece/Stone.h"
#include "class/game/chessMaster/chessboard/renju/RenjuRule.h"
namespace CM {

Renju::Renju() {

	dir_path="files/game/chessMaster/game/renju/";
	game_name="renju";
	board_size=math::vec2<int>(9,9);
	init_drawobject();

	create_pieces();

	load_board(dir_path+"chessBoard/board.txt");
	cube_type_num=21;

	tex_path="renju/board_textures";
	normal_path="renju/board_normals";
	board_size=math::vec2<int>(board_width,board_width);
	dboard->init_drawObject("",tex_path,normal_path,true);
	if(rule)delete rule;
	rule=new CM::RenjuRule();
	load_mct();
	table_pos.set_pos(glm::vec3(0.5*chess_board->sizex,-6,0.5*chess_board->sizey));
}
Renju::~Renju() {

}
void Renju::create_pieces(){
	push_piece(new Stone());
}
} /* namespace CM */
