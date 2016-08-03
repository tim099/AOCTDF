#ifndef SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_MINIONAI_H_
#define SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_MINIONAI_H_

namespace AOC {
class Minion;
class MinionAI {
public:
	MinionAI(Minion* minion);
	virtual ~MinionAI();
	void update();
	Minion* minion;
};

} /* namespace AOC */

#endif /* SOURCE_CLASS_GAME_AGEOFCUBE_MAP_MINION_MINIONAI_H_ */
