#ifndef DRAWOBJECT_H_
#define DRAWOBJECT_H_
#include <vector>
#include "class/display/draw/drawObject/drawData/DrawDataObj.h"
#include "class/tim/math/vec4.h"
#include <string>

namespace Display{
class Texture;
class Shader;
class Camera;
class ModelBuffer;
class FrameBuffer;
class DrawObject {
public:
	DrawObject(std::string _obj_str, std::string tex_str = "",
			std::string NormalTex_str = "", bool layer_texture = false);
	DrawObject();

	virtual ~DrawObject();
	virtual std::string get_type()const{
		return "DrawObject";
	}
	std::string get_name()const{
		return name;
	}
	void save(std::ostream &os);
	void load(std::istream &is);

	void init_drawObject(std::string obj, std::string tex_str,
			std::string NormalTex_str, bool layer_texture = false);
	void init_drawObject(ModelBuffer* obj, Texture* texture, Texture* NormalMap,
			bool layer_texture = false);


	static void sent_model_veiw_uniform(GLuint programID, const glm::mat4 &model_matrix);
	virtual void draw_object(Shader *shader);
	virtual void draw_shadow_map(Shader *shader);
	//update draw object if neccessary
	virtual void update();


	unsigned temp_pos_num() const;
	void push_temp_drawdata(DrawDataObj* data);
	void set_obj(ModelBuffer *obj);
	void clear_temp_drawdata();

	std::string name;
	bool draw_shadow;
	bool sky_map;
	//x=diffuse,y=specular_value,z=ambient,w=emissive
	math::vec4<float> mat;
protected:
	bool layer_texture;
	bool alpha_drawobject;
	ModelBuffer *model_buffer;
	Texture* texture;
	Texture* NormalMap;


	std::string texture_name,normalmap_name;
	std::string modelbuffer_name;
	//Camera* cur_camera;
	void draw_vec(Shader *shader, std::vector<DrawDataObj*> &data_v);
	void draw_vec_fast(Shader *shader, std::vector<DrawDataObj*> &data_v);
	void draw_shadow_vec(Shader *shader, std::vector<DrawDataObj*> &data_v);
	std::vector<DrawDataObj*> temp_datas;

};
}
#endif /* DRAWOBJECT_H_ */
