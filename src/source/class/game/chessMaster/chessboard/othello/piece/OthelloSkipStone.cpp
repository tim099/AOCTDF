#include "class/game/chessMaster/chessboard/othello/piece/OthelloSkipStone.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace CM {

OthelloSkipStone::OthelloSkipStone() {
	set_draw_piece1("chess/black_skip");
	set_draw_piece2("chess/white_skip");
	weight=1;
	name="skip_stone";
}
OthelloSkipStone::~OthelloSkipStone() {

}

} /* namespace CM */
