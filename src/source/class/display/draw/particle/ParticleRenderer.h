#ifndef SOURCE_CLASS_DISPLAY_DRAW_PARTICLE_PARTICLERENDERER_H_
#define SOURCE_CLASS_DISPLAY_DRAW_PARTICLE_PARTICLERENDERER_H_
#include "class/display/draw/billboard/BillBoard.h"
#include "class/display/camera/Camera.h"
#include "class/display/draw/particle/Particle.h"
namespace Display {

class ParticleRenderer {
public:
	ParticleRenderer();
	virtual ~ParticleRenderer();
	void update();
	void clear();
	void clear_temp_drawdata();
	void draw(Shader *shader,Camera *camera);
	void push(Particle* particle){
		particles.push_back(particle);
	}
	std::vector<Particle*> particles;
};

} /* namespace Display */

#endif /* SOURCE_CLASS_DISPLAY_DRAW_PARTICLE_PARTICLERENDERER_H_ */
