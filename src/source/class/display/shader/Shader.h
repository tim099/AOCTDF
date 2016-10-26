#ifndef SHADER_H_
#define SHADER_H_
#include <vector>
#include <string>
#include <GL/glew.h>
#include "class/display/uniform/Uniform.h"
#include "class/tim/math/vec2.h"
namespace Display{

class Shader {
public:
	static constexpr int NormalMapping=1<<0;
	static constexpr int LayerTexture=1<<1;
	static constexpr int AlphaTexture=1<<2;
	static constexpr int Clipping=1<<3;
	static constexpr int SkyMap=1<<4;
	static constexpr int Back_culling=1<<5;
	static constexpr int BillBoard=1<<6;
	static constexpr int Particle=1<<7;
	static constexpr int Atlas=1<<8;
	static constexpr int ModelMatArr=1<<9;

	static constexpr int SobelMode=1<<10;
	static constexpr int AddOnMode=1<<11;
	static constexpr int ColorAlterMode=1<<12;

	static constexpr int Type_Texture=0;
	static constexpr int Type_TextureArr=1;

	Shader(std::string name=std::string("default"));
	virtual ~Shader();
	void LoadShader(const char* vertex,const char* fragment);
	void LoadShader(const char* vertex,const char* geometry,const char* fragment);
	void active_shader();
	void Enable(int flag);
	void Disable(int flag);
	void EnableNormapping();
	void DisableNormapping();

	void sent_Uniform(std::string name,int i);
	void sent_Uniform(std::string name,glm::vec4 pos);
	void sent_Uniform(std::string name,glm::vec3 pos);
	void sent_Uniform(std::string name,math::vec2<float> pos);
	void sent_Uniform(std::string name,float val);

	void sent_Uniform(std::string name,float x,float y);


	void set_texture_type(int textureType);
	std::string Name()const;
	GLuint programID;
protected:
	static GLuint create_shader(const char* src,GLenum type);
	static void read_shader(std::string &ShaderCode,const char* path);
	static void check_shader(GLuint VertexShaderID,GLint &Result,int &InfoLogLength);
	static GLuint create_program(std::vector<GLuint>&shaders);
	static void check_program(GLuint ProgramID);
	static void compile_shader(GLuint ShaderID,std::string &ShaderCode);
	int shaderData;
	std::string name;
};
}
#endif /* SHADER_H_ */
