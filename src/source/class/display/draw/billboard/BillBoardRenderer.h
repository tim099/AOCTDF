#ifndef SOURCE_CLASS_DISPLAY_DRAW_BILLBOARD_BILLBOARDRENDERER_H_
#define SOURCE_CLASS_DISPLAY_DRAW_BILLBOARD_BILLBOARDRENDERER_H_
#include "class/display/draw/drawObject/DynamicDrawObject.h"
#include "class/display/draw/billboard/BillBoard.h"
#include "class/display/camera/Camera.h"
namespace Display {

class BillBoardRenderer{
public:
	BillBoardRenderer();
	virtual ~BillBoardRenderer();
	void push(BillBoard* billboard);
	void draw(Shader *shader,Camera *camera);
	void clear_temp_drawdata();
	std::vector<BillBoard*> billboards;
};

} /* namespace Display */

#endif /* SOURCE_CLASS_DISPLAY_DRAW_BILLBOARD_BILLBOARDRENDERER_H_ */
