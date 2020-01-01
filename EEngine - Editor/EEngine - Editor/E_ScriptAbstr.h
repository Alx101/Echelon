#ifndef _SCRIPT_ABSTR_H_
#define _SCRIPT_ABSTR_H_

#include "common_header.h"
#include "angelscript.h"

namespace EEngine
{
class ScriptAbstr
{
public:
	ScriptAbstr();
	~ScriptAbstr();

	bool loadScript(char* filename, char* module = "");
	bool compileScripts(string aScriptList[]);

	void setScriptPath(string sPath);
private:
	string path;
	asIScriptEngine* scriptEngine;
	map<string, fstream*> scriptList;
	
	string scriptContent;

};
}

#endif