#ifndef SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_BORADDATA_H_
#define SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_BORADDATA_H_

namespace CM {

class BoradData {
public:
	BoradData();
	virtual ~BoradData();
	virtual BoradData* clone(){
		return 0;
	}
};

} /* namespace CM */

#endif /* SOURCE_CLASS_GAME_CHESSMASTER_CHESSBOARD_BORADDATA_H_ */
