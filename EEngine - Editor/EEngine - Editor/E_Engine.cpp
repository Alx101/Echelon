#include "E_Engine.h"
using namespace EEngine;

Engine::Engine()
{
	logName = "log.txt";
	LogMgr::LogMgr();
	LogMgr::createLog(logName);
	core = new Core();
}

Engine::~Engine()
{
	if(core) delete core;
	LogMgr::closeLog();
}