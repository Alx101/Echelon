#ifndef _E_RESOURCE_MGR_H_
#define _E_RESOURCE_MGR_H_

#include "common_header.h"
#include "E_FileMgr.h"
#include "E_GL.h"

namespace EEngine
{
class ResourceMgr
{
	public:
		ResourceMgr();
		~ResourceMgr();

		static GLuint loadShader(string vertname, string fragName, string shaderName);
		static GLuint loadShader(string shaderName);
		static void setResourcePath(string path);
		static void setShaderPath(string path);
		static void setModelPath(string path);

	private:
		static map<string, GLuint> shaderMap;
		static string topPath;
		static string shaderPath;
		static string modelPath;
};
}

#endif