#ifndef SOURCE_CLASS_DISPLAY_DRAW_BILLBOARD_BILLBOARD_H_
#define SOURCE_CLASS_DISPLAY_DRAW_BILLBOARD_BILLBOARD_H_
#include <string>
#include "class/tim/math/vec3.h"
#include "class/tim/math/vec2.h"

namespace Display {
class Shader;
class BillBoard {
public:
	BillBoard(std::string texture,math::vec3<double> pos,math::vec2<double> size);
	virtual ~BillBoard();

	void draw(Shader *shader,glm::vec3 l,glm::vec3 r,glm::vec3 u);
protected:
	void sent_uniform(Shader *shader,glm::vec3 l,glm::vec3 r,glm::vec3 u);
	math::vec3<double> pos;
	math::vec2<double> size;
	std::string texture;
};

} /* namespace Display */

#endif /* SOURCE_CLASS_DISPLAY_DRAW_BILLBOARD_BILLBOARD_H_ */
