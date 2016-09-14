#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_PIECE_SHOGIPIECE_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_PIECE_SHOGIPIECE_H_
#include "class/game/chessMaster/piece/Piece.h"
namespace CM {
namespace shogi {

class ShogiPiece : public Piece{
public:
	ShogiPiece();
	virtual ~ShogiPiece();
	inline bool bound_check(const int& x,const int &y){
		if(x>=0&&y>=0&&x<9&&y<9){
			return true;
		}
		return false;
	}
	inline void capture(CM::Board<short int> *chess_board,CM::Step &cur_step,
			int &player,int &type){
		if(type==0)return;
		type=abs(type);
		if(type>8)type-=8;
		int y;
		for(int i=0;i<9;i++){
			for(int x=10;x<15;x++){
				if(player==1)y=i;
				else y=8-i;
				//std::cout<<"x="<<x<<",y="<<y<<std::endl;
				if(chess_board->get(x,y)==0){
					cur_step.add_move(x,y,player*type,-1);
					return;
				}
			}
		}
	}
	inline void move_straight(CM::Board<short int> *chess_board,
			int x,int y,int dx,int dy,int player
			,Tim::vector<CM::Step> &next_step){
		CM::Step cur_step;
		cur_step.add_move(x,y,0,-1);
		cur_step.add_move(0,0,chess_board->get(x,y),1);
		int i=x+dx;
		int j=y+dy*player;
		int n_type;
		while(bound_check(i,j)){
			n_type=chess_board->get(i,j);
			if (n_type*player>0)break;//stop by player's own piece

			if (n_type*player<0){
				cur_step.moves[1].x=i;
				cur_step.moves[1].y=j;
				capture(chess_board,cur_step,player,n_type);
				next_step.push_back(cur_step);

				if((player==1&&j>5)||(player==-1&&j<3)){
					cur_step.moves[1].z=player*(type+8);
					next_step.push_back(cur_step);
					cur_step.moves[1].z=player*type;
				}
				cur_step.move_num=2;
				break;//attack enemy and stop here
			}else{
				cur_step.moves[1].x=i;
				cur_step.moves[1].y=j;
				next_step.push_back(cur_step);
				if((player==1&&j>5)||(player==-1&&j<3)){
					cur_step.moves[1].z=player*(type+8);
					next_step.push_back(cur_step);
					cur_step.moves[1].z=player*type;
				}
			}
			i+=dx;
			j+=dy*player;
		}
	}
	inline void move_straight_p(CM::Board<short int> *chess_board,
			int x,int y,int dx,int dy,int player
			,Tim::vector<CM::Step> &next_step){
		CM::Step cur_step;
		cur_step.add_move(x,y,0,-1);
		cur_step.add_move(0,0,chess_board->get(x,y),1);
		int i=x+dx;
		int j=y+dy*player;
		int type;
		while(bound_check(i,j)){
			type=chess_board->get(i,j);
			if (type*player>0)break;//stop by player's own piece

			if (type*player<0){
				cur_step.moves[1].x=i;
				cur_step.moves[1].y=j;
				capture(chess_board,cur_step,player,type);
				next_step.push_back(cur_step);
				cur_step.move_num=2;
				break;//attack enemy and stop here
			}else{
				cur_step.moves[1].x=i;
				cur_step.moves[1].y=j;
				next_step.push_back(cur_step);
			}
			i+=dx;
			j+=dy*player;
		}
	}
};

} /* namespace shogi */
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_PIECE_SHOGIPIECE_H_ */
