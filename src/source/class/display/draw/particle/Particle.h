#ifndef SOURCE_CLASS_DISPLAY_DRAW_PARTICLE_PARTICLE_H_
#define SOURCE_CLASS_DISPLAY_DRAW_PARTICLE_PARTICLE_H_
#include <string>
#include <vector>
#include "class/tim/math/vec3.h"
#include "class/tim/math/vec2.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/camera/Camera.h"
namespace Display {


class Shader;
class Particle {
	struct particle {
		particle(math::vec3<double> _pos,math::vec3<double> _vel,int _life){
			pos=_pos;
			vel=_vel;
			life=_life;
			tex=0;
			camdis=0;
		}
		int tex;
		math::vec3<double> pos;
		math::vec3<double> vel;
		float camdis;
		int life;
	};
	struct particleCmp{
		bool operator()(const particle* p1, const particle* p2) const{
			if(p1->camdis<p2->camdis)return true;

			return false;
		}
	};
public:
	Particle(std::string texture,math::vec3<double> pos,math::vec2<double> size,int timer=10);
	virtual ~Particle();

	void update();
	bool end();
	void draw(Shader *shader,glm::vec3 l,glm::vec3 r,glm::vec3 u,Camera *camera);
protected:
	void sent_uniform(Shader *shader,glm::vec3 l,glm::vec3 r,glm::vec3 u);
	void particles_update();
	math::vec3<double> pos;
	math::vec2<double> size;
	std::string texture;
	std::vector<particle*> particles;
	GLuint vn_buffer;
	int create_timer;
	int timer;
};

} /* namespace Display */

#endif /* SOURCE_CLASS_DISPLAY_DRAW_PARTICLE_PARTICLE_H_ */
