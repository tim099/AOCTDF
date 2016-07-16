#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/texture/Texture.h"
#include "class/display/buffer/Buffer.h"
namespace Display{
Shader2D::Shader2D(std::string _name) : Shader(_name) {
	textureData=0;

}
Shader2D::~Shader2D() {

}
void Shader2D::set_format(GLenum format){
	int textureFormat=0;
	switch(format){
		case GL_RGB:
			textureFormat=Format_RGB;
			break;
		case GL_RGBA:
			textureFormat=Format_RGBA;
			break;
		default:
			textureFormat=Format_RGB;
	}
	sent_Uniform("textureFormat",textureFormat);
}


}
