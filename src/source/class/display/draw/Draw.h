#ifndef DRAW_H_
#define DRAW_H_
#include <vector>
#include <queue>

#include "class/display/draw/texture/DrawTexture.h"
#include "class/tim/globalObject/GlobalObject.h"
#include "class/display/font/RenderString.h"
#include "class/tim/math/vec3.h"

namespace Tim{
	class Mutex;
}

namespace Display{
class DrawData;
class StringRenderer;
class Camera;
class FrameBuffer;
class Shader;
class LightControl;
class BillBoardRenderer;
class BillBoard;
class ParticleRenderer;
class Particle;
class DrawObject;

class Draw : public Tim::GlobalObject<Draw> {
public:
	Draw();
	virtual ~Draw();

	//render all object(3D Models)
	void draw3D(Shader *shader,Shader *shaderWater,Shader *shaderShadowMapping,
			Shader2D *shader2D,FrameBuffer *FBO,FrameBuffer *waterReflectFBO,
			FrameBuffer * waterRefractFBO);


	/*
	 * draw all 2D object(texture,font...etc)
	 */
	void draw2D(Shader2D *shader2D,FrameBuffer *FBO);

	void draw_shadow(Shader *shader,FrameBuffer *FBO);//render shadow map

	void update();//update all draw object

	void logical_update();
	void logical_clear();

	void remove(DrawObject* obj);

	void push(DrawObject* obj);
	void push(DrawTexture* tex);
	void push(RenderString* renderStr);
	void push(BillBoard* billboard);
	void push(Particle* particle);
	void draw_bill_board(std::string texture,math::vec3<double> pos,math::vec2<double> size);
	void draw_particle(std::string texture,math::vec3<double> pos,math::vec2<double> size,int timer=10);
	DrawData* push_as_tex(RenderString* renderStr);

	void set_lightControl(LightControl* lightControl);
	void set_camera(Camera *camera);

	unsigned obj_size() const;
	void clear_tmp_data();
	DrawObject* get_obj(unsigned i);
	Camera *camera;
	Display::LightControl* lightControl;
	bool Enable3D;
	float wave_height,wave_width;
	float water_height;
	bool real_water;
	float time;
protected:
	void draw_water(Shader *shader,Shader *shaderWater,FrameBuffer *FBO,
			FrameBuffer *waterReflectFBO,FrameBuffer *waterRefractFBO);
	void draw_billBoard(Shader *shader,Camera *camera);
	void draw_particle(Shader *shader,Camera *camera);
	std::vector<DrawObject*> d_objs;
	std::vector<DrawObject*> water_d_objs;
	std::vector<DrawTexture*> d_texs;
	//std::vector<BillBoard*> d_bill_board;

	StringRenderer* strRenderer;
	BillBoardRenderer* billBoardRenderer;
	ParticleRenderer* particleRenderer;
	Texture* sky_box;
	Tim::Mutex* d_objsMutex;
	Tim::Mutex* d_texsMutex;
};
}
#endif /* DRAW_H_ */
