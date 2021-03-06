#ifndef SOURCE_CLASS_GAME_CHESSMASTER_PIECE_PIECE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_PIECE_PIECE_H_
#include "class/tim/thread/mutex/Mutex.h"
#include "class/game/chessMaster/piece/Step.h"
#include "class/tim/array/vector.h"
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include "class/tim/lua/Lua.h"
#include "class/tim/array/vector.h"
#include "class/game/chessMaster/piece/basicRule/BasicRule.h"
#include "class/display/UI/UI.h"
#include <string>
namespace math{
class Position;
}
namespace Display{
class DrawObject;
}
namespace CM {
class ChessBoard;

class Piece {
public:
	friend ChessBoard;
	Piece();
	virtual ~Piece();

	void init(std::string name);
	virtual std::string get_name(){
		return name;
	}
	void set_name(std::string _name){
		name=_name;
	}
	virtual void next_step(CM::Board<short int> *chess_board,
			int x,int y,Tim::vector<CM::Step> &next_step,int player);

	void load_script(std::string dir_path,std::string path);
	void save_script(std::string dir_path,std::string path);

	void save_basic_rule(std::string path);
	void load_basic_rule(std::string path);

	void remove_basic_rule(BasicRule* rule);
	void add_rule(std::string rule_name);
	void push_rule(BasicRule* rule);
	void draw(math::Position* pos,int player);

	void get_rule_names(std::vector<std::string> &names);

	void update_rule_UI(UI::UI *rule_UI);
	void init_rule_page(UI::UI *rule_UI);

	void init_piece_UI(UI::UI *piece_UI);
	void update_piece_UI(UI::UI *piece_UI);

	int weight;
	int type;
	std::vector<BasicRule*> basic_rules;
protected:
	virtual void next_step(CM::Board<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player);
	void basic_next_step(CM::Board<short int> *chess_board,
			int x,int y,std::vector<int> &next_step,int player);
	void set_draw_piece1(std::string draw_piece_str);
	void set_draw_piece2(std::string draw_piece_str);


	//std::string dir_path,path;
	std::string draw_piece_str1,draw_piece_str2;
	Tim::Mutex* rule_mutex;
	Display::DrawObject *draw_piece1;//player1's piece EX:black king
	Display::DrawObject *draw_piece2;//player2's piece EX:white king
	std::string name;
	Tim::Lua *rule;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_PIECE_PIECE_H_ */
