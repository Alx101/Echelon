#include "E_FXsystem.h"
using namespace EEngine;

FXsystem::FXsystem()
{
	fxList.clear();
	version = "#version 330 core\n";
	bodyBeg = "\nvoid main()\n{";
	bodyEnd = "\n}\n";
	hasGeom = false;
}

FXsystem::~FXsystem()
{
	glDeleteShader(shader);
	for(fxIt = fxList.begin(); fxIt != fxList.end(); ++fxIt)
	{
		delete fxIt->second;
	}
	fxList.clear();
}



bool FXsystem::addFX(FX* fx, string name)
{
	if(fxList.count(name))
	{
		LogMgr::out << "[ts]An FX with the name " << name << " already exists!\n";
		return false;
	}
	fxList[name] = fx;
	return true;
}

bool FXsystem::popFX(string name)
{
	if(fxList.count(name))
	{
		LogMgr::out << "[ts]Popping " << name << lEnd;
		fxList.erase(name);
		return true;
	}
	LogMgr::out << "[ts]No FX with the name " << name << " is registered!\n";
	return false;
}

FX_DataStruct* FXsystem::getFXData(string name)
{
	if(fxList.count(name))
		return fxList[name]->getData();
	return NULL;
}

bool FXsystem::importFX(string path)
{
	DIR* dir;
	FX* fx;
	string posfix = "xf.";
	LogMgr::out << "[ts]Loading FX files...\n";
	LogMgr::addIndent(1);
	struct dirent* ent;
	if ((dir = opendir (path.c_str())) != NULL) 
	{
		FileMgr::setFilePath(path);
		while ((ent = readdir (dir)) != NULL) 
		{
			string name(ent->d_name);
			string tmp = "";
			if(name.length() > 4)
			{
				for(string::reverse_iterator it = name.rbegin(); it != (name.rbegin()+3); ++it)
				{
					if(it == name.rend())
						break;
					tmp += *it;
				}
			}
			if(tmp == posfix)
			{
				if(!FileMgr::addFile(name))
					return false;
				fx = new FX(name, FileMgr::getFileContent(name));
				fx->trimSource();
				fxList[name] = fx;
				FileMgr::closeFile(name);
				FileMgr::popFile(name);
			}
		}
		closedir (dir);
		LogMgr::setLogPrio(SUCCESS);
		LogMgr::decrIndent(1);
		LogMgr::out << "[ts]Done!\n";
		return true;
	} 
	else 
	{
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << "[ts]Could not find directory provided!\n";
		return false;
	}
}

bool FXsystem::makeBigFile()
{
	shader = NULL;
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

	int len = 0;
	char logBuf[1024];

	string Source = "";

	Source += version;
	for(fxIt = fxList.begin(); fxIt != fxList.end(); ++fxIt)
	{
		if(fxIt->second->foundID)
			Source += fxIt->second->getID();
	}
	for(fxIt = fxList.begin(); fxIt != fxList.end(); ++fxIt)
	{
		if(fxIt->second->foundVertGlobal)
			Source += fxIt->second->getGlobal(VERTEX_SHADER);
	}

	Source += bodyBeg;
	for(fxIt = fxList.begin(); fxIt != fxList.end(); ++fxIt)
	{
		if(fxIt->second->foundVertBody)
			Source += fxIt->second->getBody(VERTEX_SHADER);
	}

	Source += bodyEnd;
	for(fxIt = fxList.begin(); fxIt != fxList.end(); ++fxIt)
	{
		if(fxIt->second->foundVertFunc)
			Source += fxIt->second->getFunctions(VERTEX_SHADER);
	}

	const char* vsSource = Source.c_str();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
	if(!compile_ok)
	{
		glGetShaderInfoLog(vs, sizeof(logBuf), &len, logBuf);
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << ts << "Error in vertex shader\n" << logBuf << lEnd;
		return false;
	}

	Source = "";

	Source += version;
	for(fxIt = fxList.begin(); fxIt != fxList.end(); ++fxIt)
	{
		if(fxIt->second->foundFragGlobal)
			Source += fxIt->second->getGlobal(FRAGMENT_SHADER);
	}

	Source += bodyBeg;
	for(fxIt = fxList.begin(); fxIt != fxList.end(); ++fxIt)
	{
		if(fxIt->second->foundFragBody)
			Source += fxIt->second->getBody(FRAGMENT_SHADER);
	}

	Source += bodyEnd;
	for(fxIt = fxList.begin(); fxIt != fxList.end(); ++fxIt)
	{
		if(fxIt->second->foundFragFunc)
			Source += fxIt->second->getFunctions(FRAGMENT_SHADER);
	}

	const char* fsSource = Source.c_str();
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
	if(!compile_ok)
	{
		glGetShaderInfoLog(fs, sizeof(logBuf), &len, logBuf);
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << ts << "Error in fragment shader\n" << logBuf << lEnd;
		return false;
	}

	Source = "";

	Source += version;
	for(fxIt = fxList.begin(); fxIt != fxList.end(); ++fxIt)
	{
		if(fxIt->second->foundGeomGlobal)
		{
			Source += fxIt->second->getGlobal(GEOMETRY_SHADER);
			hasGeom = true;
		}
	}

	Source += bodyBeg;
	for(fxIt = fxList.begin(); fxIt != fxList.end(); ++fxIt)
	{
		if(fxIt->second->foundGeomBody)
		{
			Source += fxIt->second->getBody(GEOMETRY_SHADER);
			hasGeom = true;
		}
	}

	Source += bodyEnd;
	for(fxIt = fxList.begin(); fxIt != fxList.end(); ++fxIt)
	{
		if(fxIt->second->foundGeomFunc)
		{
			Source += fxIt->second->getFunctions(GEOMETRY_SHADER);
			hasGeom = true;
		}
	}

	const char* gsSource = Source.c_str();
	GLuint gs = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(gs, 1, &gsSource, NULL);
	glCompileShader(gs);
	glGetShaderiv(gs, GL_COMPILE_STATUS, &compile_ok);
	if(!compile_ok)
	{
		glGetShaderInfoLog(fs, sizeof(logBuf), &len, logBuf);
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << ts << "Error in geometry shader (if no geometry shader is attached, this warning is harmless)\n" << logBuf << lEnd;
		gs = NULL;
	}

	shader = glCreateProgram();
	glAttachShader(shader, vs);
	glAttachShader(shader, fs);
	if(hasGeom)
		glAttachShader(shader, gs);

	for(fxIt = fxList.begin(); fxIt != fxList.end(); ++fxIt)
	{
		FX_DataStruct* tmp = fxIt->second->getData();
		for(tmp->idIt = tmp->dataID.begin(); tmp->idIt != tmp->dataID.end(); ++tmp->idIt)
		{
			GLuint at;
			glBindAttribLocation(shader, at, tmp->idIt->c_str());
			tmp->attributes.insert(pair<string, GLuint>(*tmp->idIt, at));
		}
	}
	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &link_ok);
	if(!link_ok)
	{
		glGetProgramInfoLog(shader, sizeof(logBuf), &len, logBuf);
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << ts <<  "Could not link shaders!" << logBuf << lEnd;
		return false;
	}

	return true;
}

void FXsystem::addProfile(EEngine::FXprofile* profile, int nodeID)
{
	profiles[nodeID] = profile;
}

EEngine::FXprofile* FXsystem::getProfile(int nodeID)
{
	if(profiles.count(nodeID))
		return profiles[nodeID];
	else
		return NULL;
}

void FXsystem::prepProfile(int nodeID)
{
	if(profiles.count(nodeID))
	{
		profiles[nodeID]->prepShaders();
	}
}

void FXsystem::preRender()
{
	glUseProgram(shader);
}

void FXsystem::postRender()
{
	glUseProgram(0);
}

GLuint& FXsystem::getShader()
{
	return shader;
}