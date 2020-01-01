#ifndef _E_FX_SYSTEM_H_
#define _E_FX_SYSTEM_H_

#include "common_header.h"
#include "E_FileMgr.h"
#include "E_FXprofile.h"
#include <dirent.h>
#include "E_FX.h"

namespace EEngine
{
class FXsystem
{
	public:
		FXsystem();
		~FXsystem();

		bool addFX(FX* fx, string name);
		bool popFX(std::string name);
		EEngine::FX_DataStruct* getFXData(string name);
		bool importFX(string path);
		bool makeBigFile();

		void addProfile(EEngine::FXprofile* profile, int nodeID);
		EEngine::FXprofile* getProfile(int nodeID);

		void prepProfile(int nodeID);

		void preRender();
		void postRender();

		GLuint& getShader();

	private:
		std::map<std::string, FX*> fxList;
		std::map<std::string, FX*>::iterator fxIt;
		std::map<int, EEngine::FXprofile*> profiles;
		char* version;
		char* bodyBeg;
		char* bodyEnd;
		bool hasGeom;
		GLuint shader;

};
}

#endif