#include "class/display/texture/texture3D/Texture2DArr/Texture2DArr.h"
#include "class/display/texture/image/Image.h"
#include "class/display/shader/shader2D/Shader2D.h"
#include "class/display/buffer/Buffer.h"
#include "class/display/window/ViewPort.h"
#include <iostream>
namespace Display{
Texture2DArr::Texture2DArr(GLuint _TexID,glm::ivec3 _size,GLenum _type,GLenum _format)
: Texture(_TexID,GL_TEXTURE_2D_ARRAY,_type,_format){
	size=_size;
}
Texture2DArr::~Texture2DArr() {

}
int Texture2DArr::layer()const{
	return size.z;
}
int Texture2DArr::get_texture_type(){
	return Shader::Type_TextureArr;
}
Texture2DArr* Texture2DArr::gen_texture2DArr(std::vector<std::string>&path,glm::ivec3 size,GLint internalformat,GLenum format,
		GLenum type,int Parameteri){
	Texture2DArr* texarr=Texture2DArr::gen_texture2DArr(size,internalformat,format,type,P_NONE);
	for(unsigned i=0;i<path.size();i++){
		Image<unsigned char>::load_sub_image3D(path.at(i).c_str(),texarr->target,i,type);
	}
	TexFilterParameteri(GL_TEXTURE_2D_ARRAY,Parameteri);
	return texarr;
}
Texture2DArr* Texture2DArr::gen_texture2DArr(glm::ivec3 size,GLint internalformat,GLenum format,
		GLenum type,int Parameteri){
	GLuint texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D_ARRAY,texture);
	glTexImage3D(GL_TEXTURE_2D_ARRAY,0,internalformat,size.x,size.y,size.z,0,format,type,NULL);//0=level,0=border

	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	TexFilterParameteri(GL_TEXTURE_2D_ARRAY,Parameteri);

	Texture2DArr *tex=new Texture2DArr(texture,size,type,format);

	return tex;
}
void Texture2DArr::draw(Shader2D* shader2D,DrawData *data){
	DrawData2D *dat=(DrawData2D*)data;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	float targetaspect=ViewPort::get_cur_viewport_aspect();

    glm::vec2 tsize;
    float aspect=Tim::Math::aspect(glm::ivec2(size.x,size.y))/targetaspect;
    tsize=Tim::Math::get_size(dat->width,aspect);
    if(!dat->height==DrawData2D::AutoHeight){
    	tsize.y*=dat->height;
    }

	GLuint tex_vt=gen_texture_vertex(tsize),tex_uv=gen_texture_uv();

	Buffer::bind_vtbuffer(tex_vt);
	Buffer::bind_uvbuffer(tex_uv);

	shader2D->sent_Uniform("Texture",0);
	sent_uniform(shader2D,1,"TextureArr");
	math::vec2<float> pos=(dat->pos)*2.0f+
			math::vec2<float>(tsize.x,-tsize.y)-
			math::vec2<float>(1.0,1.0);
	shader2D->sent_Uniform("position",pos);
	shader2D->sent_Uniform("alpha",dat->alpha);
	shader2D->sent_Uniform("tex_layer",dat->layer);
	//shader2D->set_type(Display::Type_TextureArr);
	glDrawArrays(GL_TRIANGLES,0,2*3);


    glDeleteBuffers(1,&tex_vt);
    glDeleteBuffers(1,&tex_uv);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}
}
