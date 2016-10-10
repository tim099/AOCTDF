#ifndef TEXTURE_H_
#define TEXTURE_H_
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <string>
#include "class/display/texture/image/Image.h"
#include "class/display/texture/texture2D/DrawData2D.h"

namespace Display{
const int P_NONE=0;
const int P_MipMap=1;
const int P_Linear=2;
const int P_Nearest=3;
//===========================

class Texture2D;
class Shader2D;
class Shader;
class Texture {
public:
	Texture(GLuint TexID,GLenum target,GLenum type,GLenum format,GLint internalformat=0);
	Texture();
	virtual ~Texture();
	virtual std::string get_type(){
		return "Texture";
	}
	virtual Texture* clone()=0;
	virtual int get_texture_type(){return 0;}

	virtual void save(std::ostream &os){}
	virtual void load(std::istream &is,std::string folder_path){}

	virtual Texture2D* Tex2D();
	virtual void draw_texture(Shader2D* shader2D,DrawData *data);
	virtual int get_layer()const;
	virtual void sent_uniform(Shader* shader,int num,const char *name);

	virtual double get_aspect();


	static void sent_textureVec(Shader* shader,std::vector<Texture*>& texvec,int num,const char *name);
	static GLuint gen_texture_vertex(glm::vec2 size);
	static GLuint gen_texture_uv();

	void bind_texture();

	std::string name;
	std::string path;

	GLuint TexID;
	GLenum target;
	GLint internalformat;
	GLenum format;
	GLenum type;
protected:
	void init(GLuint TexID,GLenum target,GLenum type,GLenum format,GLint internalformat=0);
	virtual void draw(Shader2D* shader2D,DrawData *data);
	static void TexFilterParameteri(GLenum target,int Parameteri);
};
}
#endif /* TEXTURE_H_ */
