#ifndef BUFFER_H_
#define BUFFER_H_
#include <GL/glew.h>
namespace Display{
class Buffer {
public:
	static const int vt=0;
	static const int uv=1;
	static const int vn=2;
	static const int ly=3;
	static const int m=4;
	Buffer(GLfloat* data,int datasize,GLuint index,GLint size,GLenum type
			,GLboolean normalized=GL_FALSE
			,GLsizei stride=0);
	virtual ~Buffer();
	static GLuint gen_buffer(GLfloat* data,int datasize);
	static GLuint GenVertexArray();

	static void bind_vtbuffer(GLuint vertexbuffer);
	static void bind_uvbuffer(GLuint uvbuffer);
	static void bind_vnbuffer(GLuint vnbuffer);

	static void bind_buffer(int index,int size,GLuint buffer);
	static void bind_buffer_mat4(int index,int size,GLuint buffer);

	static void unbind_buffer(int type);
	static void unbind_buffer_mat4(int type);
	static void unbind_vtbuffer();
	static void unbind_uvbuffer();
	static void unbind_vnbuffer();
	static void unbind_lybuffer();


	static void disable_all_buffer();
	void update_buffer(GLfloat* data,int datasize);
	void bind_buffer();
	void unbind_buffer();
protected:
	GLuint buffer;
	GLuint index;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
};
}
#endif /* BUFFER_H_ */
