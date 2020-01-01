#include "E_ScriptAbstr.h"
using namespace EEngine;

ScriptAbstr::ScriptAbstr()
{
	scriptEngine = asCreateScriptEngine( ANGELSCRIPT_VERSION );
	if( scriptEngine == 0 )
	{
		LogMgr::logMessage(LogMgr::CRITICAL, "Could not create script engine!");
	}
	LogMgr::logMessage(LogMgr::NORMAL, "Initialized AS subsystem");
	path = "";
	scriptList.clear();
}

ScriptAbstr::~ScriptAbstr()
{
	LogMgr::logMessage(LogMgr::NORMAL, "Shutting down AS subsystem");
	scriptEngine->Release();
	scriptList.clear();
}

bool ScriptAbstr::loadScript(char* filename, char* module)
{
	return true;
}

bool ScriptAbstr::compileScripts(string aScriptList[])
{	
	return true;
}