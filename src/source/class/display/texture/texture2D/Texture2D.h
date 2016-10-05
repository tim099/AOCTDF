#ifndef TEXTURE2D_H_
#define TEXTURE2D_H_
#include "class/display/texture/Texture.h"

namespace Display{
template <class DataType>class Image;

class Texture2D : public Texture {
public:
	Texture2D();
	Texture2D(unsigned char *pixels,glm::ivec2 size,GLint internalformat,GLenum format
			,GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_MipMap);
	Texture2D(Image<unsigned char>* image,GLint internalformat,
			GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_MipMap);
	Texture2D(std::string imagepath,int Parameteri=P_MipMap);
	virtual ~Texture2D();

	virtual Texture* clone(){
		return new Texture2D();
	}
	virtual std::string get_type(){
		return "Texture";
	}
	virtual void load(std::istream &is,std::string folder_path);
	void load(std::string imagepath,int Parameteri=P_MipMap);
	void init(unsigned char *pixels,glm::ivec2 size,GLint internalformat,GLenum format
			,GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_MipMap);

	virtual int get_texture_type();

	virtual Texture2D* Tex2D();
	virtual int get_layer()const;
	virtual double get_aspect();
	Image<unsigned char>* convert_to_image(GLenum format=GL_RGB);
	glm::ivec2 size;
protected:
	virtual void draw(Shader2D* shader2D,DrawData *data);
};
}
#endif /* TEXTURE2D_H_ */
