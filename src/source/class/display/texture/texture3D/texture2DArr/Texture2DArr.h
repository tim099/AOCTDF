#ifndef TEXTURE2DARR_H_
#define TEXTURE2DARR_H_
#include "class/display/texture/Texture.h"
#include <vector>
#include <string>
namespace Display{
template <class DataType>class Image;
class Texture2DArr : public Texture {
public:
	Texture2DArr();
	Texture2DArr(glm::ivec3 size,GLint internalformat,GLenum format,
			GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_Linear);
	Texture2DArr(std::vector<std::string>&path,glm::ivec3 size,GLint internalformat,GLenum format,
			GLenum type,int Parameteri);//=GL_UNSIGNED_BYTE,=P_MipMap,P_Linear
	virtual ~Texture2DArr();
	virtual Texture* clone(){
		return new Texture2DArr();
	}

	virtual std::string get_type(){
		return "Texture2DArr";
	}
	virtual void save(std::ostream &os);
	virtual void load(std::istream &is,std::string folder_path);
	virtual int get_texture_type();
	virtual int get_layer()const;
protected:
	void init(glm::ivec3 size,GLint internalformat,GLenum format,
			GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_Linear);
	void load(std::vector<std::string>&path,glm::ivec3 size,GLint internalformat,
			GLenum format,GLenum type,int Parameteri);

	virtual void draw(Shader2D* shader2D,DrawData *data);
	std::vector<std::string> paths;
	glm::ivec3 size;
};
}
#endif /* TEXTURE2DARR_H_ */
