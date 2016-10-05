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
		void gen_cam_dis(Camera *camera){
			camdis=(math::vec3<double>(camera->pos.x,camera->pos.y,camera->pos.z)-pos).get_length();
		}
		int tex;
		math::vec3<double> pos;
		math::vec3<double> vel;
		float camdis;
		int life;
	};
	struct particleCmp{
		bool operator()(const particle* p1, const particle* p2) const{
			if(p1->camdis>p2->camdis)return true;

			return false;
		}
	};
public:
	Particle(std::string texture,math::vec3<double> pos,math::vec2<double> size,int timer=10);
	virtual ~Particle();

	void update();
	bool end();
	void draw(Shader *shader,glm::vec3 l,glm::vec3 r,glm::vec3 u,Camera *camera);
	void set_atlas(int _x_seg,int _y_seg,int _play_speed){
		atlas=true;
		x_seg=_x_seg;
		y_seg=_y_seg;
		play_speed=_play_speed;
	}
protected:
	void sent_uniform(Shader *shader,glm::vec3 l,glm::vec3 r,glm::vec3 u);
	void particles_update();
	math::vec3<double> pos;
	math::vec2<double> size;
	std::string texture;
	std::vector<particle*> particles;

	bool atlas;
	int x_seg,y_seg;
	int play_speed;
	int create_timer;
	int timer;
};

} /* namespace Display */

#endif /* SOURCE_CLASS_DISPLAY_DRAW_PARTICLE_PARTICLE_H_ */
