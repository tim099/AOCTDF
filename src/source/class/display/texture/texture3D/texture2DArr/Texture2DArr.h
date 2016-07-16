#ifndef TEXTURE2DARR_H_
#define TEXTURE2DARR_H_
#include "class/display/texture/Texture.h"
#include <vector>
#include <string>
namespace Display{
template <class DataType>class Image;
class Texture2DArr : public Texture {
public:
	Texture2DArr(GLuint _TexID,glm::ivec3 size,GLenum type,GLenum format);
	virtual ~Texture2DArr();
	virtual int get_texture_type();
	virtual int layer()const;
	static Texture2DArr* gen_texture2DArr(glm::ivec3 size,GLint internalformat,GLenum format,
			GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_Linear);

	static Texture2DArr* gen_texture2DArr(std::vector<std::string>&path,glm::ivec3 size,GLint internalformat,GLenum format,
			GLenum type,int Parameteri);//=GL_UNSIGNED_BYTE,=P_MipMap,P_Linear
protected:
	virtual void draw(Shader2D* shader2D,DrawData *data);
	glm::ivec3 size;
};
}
#endif /* TEXTURE2DARR_H_ */
