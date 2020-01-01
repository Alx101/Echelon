#ifndef _E_FX_H_
#define _E_FX_H_

#include "common_header.h"

class FX
{
	public:
		FX(std::string name, char* source);
		FX();
		~FX();

		void setName(std::string name);
		void setSource(char* source);
		bool trimSource();

		string getName();
		char* getGlobal(int shaderType);
		char* getBody(int shaderType);
		char* getFunctions(int shaderType);
		char* getID();
		EEngine::FX_DataStruct* getData();

		bool foundVertGlobal;
		bool foundFragGlobal;
		bool foundGeomGlobal;
		bool foundVertBody;
		bool foundFragBody;
		bool foundGeomBody;
		bool foundVertFunc;
		bool foundFragFunc;
		bool foundGeomFunc;
		bool foundID;
	private:
		string fxName;
		stringstream* fxSource;
		int fxVertLen;
		int fxFragLen;
		int fxGeomLen;
		char* fxVertGlobal;
		char* fxFragGlobal;
		char* fxGeomGlobal;
		char* fxVertBody;
		char* fxFragBody;
		char* fxGeomBody;
		char* fxVertFunctions;
		char* fxFragFunctions;
		char* fxGeomFunctions;
		char* fxID;
		string fxGlobalVertId;
		string fxGlobalFragId;
		string fxGlobalGeomId;
		string fxBodyVertId;
		string fxBodyFragId;
		string fxBodyGeomId;
		string fxFuncVertId;
		string fxFuncFragId;
		string fxFuncGeomId;
		string fxIdentId;
		EEngine::FX_DataStruct data;
};

#endif