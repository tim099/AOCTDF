#include "class/game/chessMaster/chessboard/ChessBoardCreator.h"
#include "class/game/chessMaster/chessboard/ChessBoard.h"
#include "class/game/chessMaster/chessboard/chineseChess/ChineseChess.h"
#include "class/game/chessMaster/chessboard/renju/Renju.h"
#include "class/game/chessMaster/chessboard/othello/Othello.h"
#include "class/game/chessMaster/chessboard/darkChess/DarkChess.h"
#include "class/game/chessMaster/chessboard/shogi/Shogi.h"
#include "class/game/chessMaster/common.h"

namespace CM {

ChessBoardCreator::ChessBoardCreator() {

}
ChessBoardCreator::~ChessBoardCreator() {

}
ChessBoard* ChessBoardCreator::create(std::string name){
	ChessBoard* chess_board=0;
	if(name=="chineseChess"){
		chess_board=new ChineseChess();
	}else if(name=="renju"){
		chess_board=new Renju();
	}else if(name=="othello"){
		chess_board=new Othello();
	}else if(name=="darkChess"){
		chess_board=new darkChess::DarkChess();
	}else if(name=="shogi"){
		chess_board=new shogi::Shogi();
	}else{
		chess_board=new ChessBoard();
		chess_board->load_script(CM::folder_path+"game/"+name+"/");
	}
	if(chess_board){
		chess_board->game_name=name;
	}
	return chess_board;
}
} /* namespace CM */
