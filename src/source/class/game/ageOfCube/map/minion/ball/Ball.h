#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_BALL_BALL_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_BALL_BALL_H_

#include "class/game/ageOfCube/map/minion/Minion.h"


#include "class/audio/AudioPlayer.h"

namespace AOC {

class Ball: public Minion {

public:
	virtual void minion_pre_init();
	Ball();
	Ball(Ball* ball);
	virtual ~Ball();

	virtual Minion* clone(){
		return new Ball(this);
	}
	virtual std::string get_name()const{
		return "Ball";
	}

protected:
	virtual void save_minion(FILE * file);
	virtual void load_minion(FILE * file);
	virtual void draw_minion();
	virtual void minion_update();
	virtual void killed();
	virtual void unit_create();

	Display::DrawObject *ball_Drawobj;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_BALL_BALL_H_ */
