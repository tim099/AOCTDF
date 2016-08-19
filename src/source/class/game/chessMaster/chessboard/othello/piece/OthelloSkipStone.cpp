#include "class/game/chessMaster/chessboard/othello/piece/OthelloSkipStone.h"
#include "class/display/draw/drawObject/AllDrawObjects.h"
namespace CM {

OthelloSkipStone::OthelloSkipStone() {
	draw_piece1=Display::AllDrawObjects::get_cur_object()->get("chess/black_skip");
	draw_piece2=Display::AllDrawObjects::get_cur_object()->get("chess/white_skip");
	weight=1;
}
OthelloSkipStone::~OthelloSkipStone() {

}

} /* namespace CM */
