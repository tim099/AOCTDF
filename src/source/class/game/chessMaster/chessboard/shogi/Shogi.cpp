#include "class/game/chessMaster/chessboard/shogi/Shogi.h"
#include "class/game/chessMaster/chessboard/shogi/ShogiRule.h"

#include "class/game/chessMaster/chessboard/shogi/piece/Pawn.h"
#include "class/game/chessMaster/chessboard/shogi/piece/Bishop.h"
#include "class/game/chessMaster/chessboard/shogi/piece/Rook.h"
#include "class/game/chessMaster/chessboard/shogi/piece/Lance.h"
#include "class/game/chessMaster/chessboard/shogi/piece/Knight.h"
#include "class/game/chessMaster/chessboard/shogi/piece/Silver.h"
#include "class/game/chessMaster/chessboard/shogi/piece/Gold.h"
#include "class/game/chessMaster/chessboard/shogi/piece/King.h"
#include "class/game/chessMaster/chessboard/shogi/piece/Ppawn.h"
#include "class/game/chessMaster/chessboard/shogi/piece/Pbishop.h"
#include "class/game/chessMaster/chessboard/shogi/piece/Prook.h"
#include "class/game/chessMaster/chessboard/shogi/piece/Plance.h"
#include "class/game/chessMaster/chessboard/shogi/piece/Pknight.h"
#include "class/game/chessMaster/chessboard/shogi/piece/Psilver.h"
#include <iostream>
namespace CM {
namespace shogi {
Shogi::Shogi() {
	dir_path="files/game/chessMaster/game/shogi/";
	game_name="shogi";
	board_size=math::vec2<int>(9,9);
	init_drawobject();
	//rule_path=dir_path+"chessBoard/rule.lua";

	create_pieces();

	load_board(dir_path+"chessBoard/board.txt");
	cube_type_num=6;

	tex_path="chess/board_textures";
	normal_path="chess/board_normals";

	dboard->init_drawObject("",tex_path,normal_path,true);

	if(rule)delete rule;
	rule=new ShogiRule();
	load_mct();
	table_pos.set_pos(glm::vec3(0.5*chess_board->sizex,-6,0.5*chess_board->sizey));
}
Shogi::~Shogi() {

}
void Shogi::create_pieces(){
	push_piece(new Pawn());
	push_piece(new Bishop());
	push_piece(new Rook());
	push_piece(new Lance());
	push_piece(new Knight());
	push_piece(new Silver());
	push_piece(new Gold());
	push_piece(new King());

	push_piece(new Ppawn());
	push_piece(new Pbishop());
	push_piece(new Prook());
	push_piece(new Plance());
	push_piece(new Pknight());
	push_piece(new Psilver());
	init_pieces();
}
}
} /* namespace CM */
