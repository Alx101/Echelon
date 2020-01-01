#include "E_ResourceMgr.h"
using namespace EEngine;

ResourceMgr::ResourceMgr()
{
	shaderMap.clear();
}

ResourceMgr::~ResourceMgr()
{
	shaderMap.clear();
}

map<string, GLuint> ResourceMgr::shaderMap;
string ResourceMgr::topPath ="";
string ResourceMgr::shaderPath ="";
string ResourceMgr::modelPath ="";

GLuint ResourceMgr::loadShader(string vertName, string fragName, string shaderName)
{
	if(shaderMap.count(shaderName))
	{
		return shaderMap[shaderName];
	}
	else
	{
		FileMgr::setFilePath(topPath+shaderPath);
		char* tmpBufV = FileMgr::getShaderContent(vertName);
		if(tmpBufV == NULL)
			return NULL;
		char* tmpBufF = FileMgr::getShaderContent(fragName);
		if(tmpBufF == NULL)
			return NULL;
		shaderMap[shaderName] = E_GL::E_GLSL::compileShader(tmpBufV, tmpBufF); 
		if(shaderMap[shaderName] == false)
		{
			return NULL;
		}
		return shaderMap[shaderName];
	}
}

GLuint ResourceMgr::loadShader(string shaderName)
{
	if(shaderMap.count(shaderName))
	{
		return shaderMap[shaderName];
	}
	else
	{
		LogMgr::logMessage(LogMgr::CRITICAL, "Could not find the shader of the given name!");
		return NULL;
	}
}


void ResourceMgr::setModelPath(string path)
{
	//Setting the path to the models, full path is topPath + modelpath
	modelPath = path;
}

void ResourceMgr::setResourcePath(string path)
{
	//Setting the TOP path
	topPath = path;
}

void ResourceMgr::setShaderPath(string path)
{
	//Settinh the path to the shaders, full path is topPath + shaderPath
	shaderPath = path;
}