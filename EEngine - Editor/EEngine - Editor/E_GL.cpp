#include "E_GL.h"
using namespace EEngine;

E_GL::E_GL()
{	
}

E_GL::~E_GL()
{
}

glm::mat4 E_GL::projMat;
int E_GL::scrW = 0;
int E_GL::scrH = 0;

bool E_GL::startup(int windowWidth, int windowHeight)
{
	LogMgr::out << "[ts]Initializing OpenGL subsystem...\n";
	LogMgr::addIndent(1);
	LogMgr::out << "[ts]Initializing GLEW\n";
	glewExperimental = true;
	if(glewInit() != GLEW_OK)
	{
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << "[ts]Could not initialize GLEW!\n";
		LogMgr::decrIndent(1);
		return false;
	}
	LogMgr::setLogPrio(SUCCESS);
	LogMgr::out << "[ts]Initialized GLEW\n";
	glClearColor(0.3, 0.3, 0.3, 1.0);
	projMat = glm::perspective(60.0f, (float)windowWidth / (float)windowHeight, 0.1f, 100.f);
	resize(windowWidth, windowHeight);
	LogMgr::setLogPrio(SUCCESS);
	LogMgr::decrIndent(1);
	LogMgr::out << "[ts]Initialized OpenGL subsystem!\n";
	return true;
}

bool E_GL::shutdown()
{
	LogMgr::out << "[ts]Shutting down OpenGL subsystem...\n";
	LogMgr::setLogPrio(SUCCESS);
	LogMgr::out << "[ts]Done!\n";
	return true;
}

void E_GL::resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	scrW = w;
	scrH = h;
}

GLuint E_GL::triangle(GLuint vbo, GLuint vao)
{
	const float vertexPositions[] = 
	{
		0.75f, 0.75f, 0.0f, 1.0f,
		0.75f, -0.75f, 0.0f, 1.0f,
		-0.75f, -0.75f, 0.0f, 1.0f,
	};
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vbo;
}

GLuint E_GL::E_GLSL::loadBasicShader()
{
	GLuint program = NULL;
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char *vs_source = 
    "#version 330\n"
    "in vec3 vPosition;                "
    "void main(void) {                        "
    "  gl_Position = vec4(vPosition, 1.0); "
    "}";
	int infologLength = 0;
	int maxLength;
	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH,&maxLength);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
	char* buffer = new char[maxLength];
	glGetShaderInfoLog(vs, maxLength, &infologLength, buffer);
	if (0 == compile_ok)
	{
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << "[ts]Error in vertex shader: " << buffer << "\n";
		return false;
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fs_source =
		"#version 330           \n"
		"out vec4 outputColor;"
		"void main(void) {        "
		"  outputColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); "
		"}";
	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH,&maxLength);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
	buffer = new char[maxLength];
	glGetShaderInfoLog(vs, maxLength, &infologLength, buffer);
	if (!compile_ok) 
	{
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << "[ts]Error in fragment shader: " << buffer << "\n";
		return false;
	}

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if(!link_ok) 
	{
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << "[ts]Could not link shaders\n";
		return false;
	}
	return program;
}

GLuint E_GL::E_GLSL::compileShader(const char* vertCont, const char* fragCont)
{
	GLuint program = NULL;
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertCont, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
	char logBuf[1024];
	int len;
	if (0 == compile_ok)
	{
		glGetShaderInfoLog(vs, sizeof(logBuf), &len, logBuf);
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << "[ts]Error in vertex shader\n" << logBuf << "\n";
		return false;
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragCont, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
	if (!compile_ok) 
	{
		glGetShaderInfoLog(fs, sizeof(logBuf), &len, logBuf);
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << ts << "Error in fragment shader" << logBuf << "\n";
		return false;
	}
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if(!link_ok) 
	{
		glGetProgramInfoLog(program, sizeof(logBuf), &len, logBuf);
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << ts << "Could not link basic shaders!" << logBuf << "\n";
		return false;
	}
	return program;
}

E_GL::E_MVP::E_MVP()
{
}

E_GL::E_MVP::~E_MVP()
{
}

glm::mat4 E_GL::E_MVP::getMVP(glm::mat4 view, glm::mat4 modl)
{
	glm::mat4 proj = glm::perspectiveFov(45.0f, (float)scrW, (float)scrH, 0.1f, 100.0f);
	glm::mat4 mvp = proj * view * modl;
	return mvp;
}

void E_GL::renderFrame()
{
	//Main render function
	glClear(GL_COLOR_BUFFER_BIT);
}