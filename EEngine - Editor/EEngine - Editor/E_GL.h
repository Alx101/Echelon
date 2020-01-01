#ifndef _E_GL_H_
#define _E_GL_H_

#include "common_header.h"

namespace EEngine
{
class E_GL
{
public:
	E_GL();
	~E_GL();

	static bool startup(int windowWidth, int windowHeight);
	static bool shutdown();
	static void renderFrame();
	static void resize(int w, int h);
	static GLuint triangle(GLuint vbo, GLuint vao);

	static glm::mat4 projMat;

	class E_GLSL
	{
	public:
		E_GLSL();
		~E_GLSL();

		static GLuint compileShader(const char* vertCont, const char* fragCont);
		static GLuint loadBasicShader();

	private:

	};

	class E_MVP
	{
	public:
		E_MVP();
		~E_MVP();

		static glm::mat4 getMVP(glm::mat4 view, glm::mat4 modl);
	};
private:
	static int scrW;
	static int scrH;

};
}

#endif