#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_SHOGI_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_SHOGI_H_

#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/game/chessMaster/chessboard/Rule.h"
namespace CM {
namespace shogi {
class Shogi: public ChessBoard {
public:
	Shogi();
	virtual ~Shogi();
	void create_pieces();
	virtual void find_next_step(CM::Board<short int> *chess_board,
			int player,Tim::vector<CM::Step> &next_steps){
		next_steps.clear();
		for(int x=0;x<9;x++){
			for(int y=0;y<9;y++){
				if(pick_chess(chess_board,x,y,player)){//player's chess
					pieces[abs(chess_board->get(x,y))-1]->
					next_step(chess_board,x,y,next_steps,player);
				}
			}
		}
		///*
		bool used[8]={false};
		int type,utype;
		for(int x=10;x<15;x++){
			for(int y=0;y<9;y++){
				type=chess_board->get(x,y);
				utype=abs(type)-1;
				if(!used[utype]&&pick_chess(chess_board,x,y,player)){//player's chess
					pieces[utype]->next_step(chess_board,x,y,next_steps,player);
					used[utype]=true;
				}
			}
		}
		//*/

	}
	virtual int evaluate_score(CM::Board<short int> *chess_board,int player){
		int total_score=0;
		for(int i=0;i<chess_board->piece_type_num;i++){
			total_score+=pieces_weight[i]*chess_board->piece_num[i];
		}
		/*,type
		for(int i=10;i<15;i++){
			for(int j=0;j<9;j++){
				type=chess_board->get(i,j);
				if(type>0){
					total_score-=0.5*pieces_weight[type-1];
				}else if(type<0){
					total_score+=0.5*pieces_weight[-type-1];
				}
			}
		}
		*/
		/*

		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				type=chess_board->get(i,j);
				if(type>0){
					total_score+=pieces_weight[type-1];
				}else if(type<0){
					total_score-=pieces_weight[-type-1];
				}
			}
		}

		for(int i=10;i<15;i++){
			for(int j=0;j<9;j++){
				type=chess_board->get(i,j);
				if(type>0){
					total_score+=0.5*pieces_weight[type-1];
				}else if(type<0){
					total_score-=0.5*pieces_weight[-type-1];
				}
			}
		}
		*/
		return player*total_score;
	}
};
}
} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_SHOGI_SHOGI_H_ */
