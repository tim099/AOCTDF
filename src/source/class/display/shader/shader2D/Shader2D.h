#ifndef SHADER2D_H_
#define SHADER2D_H_
#include <glm/glm.hpp>
#include "class/display/shader/Shader.h"
namespace Display{

//==================================
const int Format_RGB=0;
const int Format_RGBA=1;
const int Format_GrayScale=2;

class Texture;
class Shader2D : public Shader{
public:
	Shader2D(std::string name=std::string("default"));
	virtual ~Shader2D();
	void set_format(GLenum format);

protected:
	int textureData;

};
}
#endif /* SHADER2D_H_ */
