#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARD_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARD_H_
#include "class/game/chessMaster/piece/Piece.h"
#include "class/tim/array/Array3D.h"
#include "class/tim/array/Array2D.h"
#include "class/display/draw/drawObject/DynamicDrawObject.h"
#include "class/display/model/cube/CubeModel.h"
#include "class/tim/math/Position.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/game/chessMaster/piece/Step.h"
#include "class/tim/lua/Lua.h"
#include "class/game/chessMaster/chessboard/rule/Rule.h"
#include "class/tim/thread/mutex/Mutex.h"
#include "class/game/chessMaster/chessboard/BoardMCT.h"
#include "class/game/chessMaster/chessboard/Board.h"
#include "class/tim/array/vector.h"
#include "class/tim/math/vec2.h"
namespace Display{
	class ModelBufferMap;
	class TextureMap;
	class DrawObjectMap;
}
namespace CM {

class ChessBoard : public Tim::GlobalObject<ChessBoard>{
	static const int max_pieces_num=1000;
public:
	ChessBoard(int sizex=8,int sizey=3,int sizez=8);
	virtual ~ChessBoard();

	void draw();

	void update_rule_UI();
	void draw_rule_UI();
	void set_rule_UI();

	bool set_type(int x,int y,int z,unsigned char val);
	int get_type(int x,int y,int z);

	bool set_type(int x,int y,short int val);

	Piece* get_piece(int x,int y);
	int get_type(int x,int y);
	void load_script(std::string path);


	void save_board(std::string path);
	void load_board(std::string path);

	void save_pieces(std::string path);
	void load_pieces(std::string path);

	void init_UI(UI::UI *UI);
	void update_UI(UI::UI *UI);
	void save_mct();
	void load_mct();
	void find_select_cube();

	void restart();
	void move(Step &step);
	void undo(Step &step);
	void undo();
	void clear();
	void clear_steps();

	void next_turn(CM::Step step);
	void prev_turn();

	inline void find_next_step(CM::Board<short int> *chess_board,
			int x,int y,int player,Tim::vector<CM::Step> &next_steps){
		pieces[abs(chess_board->get(x,y))-1]->next_step(chess_board,x,y,next_steps,player);
	}
	virtual void find_next_step(CM::Board<short int> *chess_board,
			int player,Tim::vector<CM::Step> &next_steps){
		next_steps.clear();
		int sx=chess_board->sizex;
		int sy=chess_board->sizey;

		for(int x=0;x<sx;x++){
			for(int y=0;y<sy;y++){
				if(pick_chess(chess_board,x,y,player)){//player's chess
					pieces[abs(chess_board->get(x,y))-1]->
					next_step(chess_board,x,y,next_steps,player);
				}
			}
		}
	}
	inline bool pick_chess(CM::Board<short int> *chess_board,int &x,int &y,int &player){
		short int type;
		bool flag=false;
		type=chess_board->get(x,y);
		if(type*player>0)flag=true;
		for(unsigned i=0;i<both_selectable_piece.size();i++){
			if(type==both_selectable_piece.at(i)){
				flag=true;
				break;
			}
		}
		return flag;
	}
	static int get_board(lua_State *L);
	//return the chess number difference between players
	static int get_chess_num_delta(lua_State *L);

	static int find_board(lua_State *L);

	bool bound_check(int x,int y);
	void backpropagation();
	void draw_backpropagation();
	inline int check_winner(CM::Board<short int> *chess_board){
		return rule->check_winner(chess_board);
	}
	virtual int evaluate_score(CM::Board<short int> *chess_board,int player){
		int total_score=0;
		for(int i=0;i<chess_board->piece_type_num;i++){
			total_score+=pieces_weight[i]*chess_board->piece_num[i];
		}
		return player*total_score;
	}
	inline Tim::Array2D<short int>* get_cur()const{
		return cur_board;
	}
	inline CM::StepNode *get_cur_node(){
		return cur_node;
	}
	inline void push_piece(Piece* piece){
		pieces.push_back(piece);
		piece->type=pieces.size();
	}
	void switch_rule(std::string name);

	void update();

	//cube being selected by mouse
	glm::ivec3 selected_cube;

	//cube being selected on(may near by the selected cube or equal to selected cube
	glm::ivec3 selected_on;

	glm::ivec2 selected_piece;
	double cube_size;
	std::vector<Piece*>pieces;
	math::vec2<int>board_size;
	math::vec2<int>board_start;
	CM::Board<short int>*chess_board;//all chess on the board
	//Tim::Array2D<short int> *chess_board;
	Tim::Array3D<unsigned char> *board;//the chess_board's structure
	std::vector<CM::Step*> steps;
	int cube_type_num;//number of cube type
	bool show_rule_ui;

	std::string game_name;
	CM::Rule *rule;
	CM::BoardMCT *mct;
	std::string dir_path;
	int winner,cur_player;
	glm::ivec3 size;

	std::string tex_path;
protected:
	void init_board();
	void init_pieces();
	void init_drawobject();
	void remove_drawobject();
	void gen_model();

	void gen_pieces_weight();


	void find_selected_on(glm::vec3 pos);
	void find_selected_cube(glm::vec3 pos);


	int pieces_weight[max_pieces_num];

	std::string normal_path;

	Display::DynamicDrawObject *dboard;
	Display::CubeModel *cube;
	math::Position *pos;
	math::Position table_pos;
	Display::ModelBufferMap* model_map;
	Display::TextureMap* tex_map;
	Display::DrawObjectMap *draw_map;
	CM::StepNode *cur_node;


	std::string rule_path;
	bool updated;

	std::vector<short int>both_selectable_piece;
	Tim::Array2D<short int> *cur_board;
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_CHESSBOARD_H_ */
