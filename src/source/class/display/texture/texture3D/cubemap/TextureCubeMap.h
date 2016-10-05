#ifndef TEXTURECUBEMAP_H_
#define TEXTURECUBEMAP_H_
#include "class/display/texture/Texture.h"
#include <vector>
#include <string>
namespace Display{
class TextureCubeMap : public Texture{
public:
	TextureCubeMap();
	TextureCubeMap(glm::ivec2 size,GLint internalformat,GLenum format,
			GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_Linear);
	TextureCubeMap(std::vector<std::string>&path,glm::ivec2 size,GLint internalformat,GLenum format,
			GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_Linear);
	virtual ~TextureCubeMap();

	virtual void load(std::istream &is,std::string folder_path);
	void load(std::vector<std::string>&path,glm::ivec2 size,GLint internalformat,GLenum format,
			GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_Linear);

	virtual Texture* clone(){
		return new TextureCubeMap();
	}
	virtual std::string get_type(){
		return "TextureCubeMap";
	}
	void init(glm::ivec2 size,GLint internalformat,GLenum format,
			GLenum type=GL_UNSIGNED_BYTE,int Parameteri=P_Linear);
	virtual int get_layer()const;
protected:
	//void init();
	std::vector<std::string> paths;
	glm::ivec2 size;
};
}
#endif /* TEXTURECUBEMAP_H_ */
