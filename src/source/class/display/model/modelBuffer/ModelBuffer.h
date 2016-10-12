#ifndef BUFFEROBJECT_H_
#define BUFFEROBJECT_H_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "class/display/buffer/Buffer.h"
#include <string>


namespace Display{
class Model;
class Shader;
class ModelBuffer{
public:
	ModelBuffer();
	ModelBuffer(Model *m);

	virtual ~ModelBuffer();
	void initialize(Model *m);
	void initialize(std::string path, float size,bool align_center);

	std::string get_name()const{
		return name;
	}
	void save(std::ostream &os);
	void load(std::istream &is,std::string folder_path);

	void load_model(Model *m);

	void bind_buffer(Shader *shader);
	void unbind_buffer(Shader *shader);
	void draw(GLuint programID,GLenum mode=GL_TRIANGLES);
	void draw_instanced(GLuint programID,int num,GLenum mode=GL_TRIANGLES);
	int vertex_num;
	Buffer *vtbuffer;
	Buffer *uvbuffer;
	Buffer *vnbuffer;
	Buffer *lybuffer;
	//bool enable_lybuffer;
private:
	std::string path,name;
	float size;
	bool Align_center;
};
}
#endif /* BUFFEROBJECT_H_ */
