#include "E_StateMgr.h"
using namespace EEngine;

StateMgr::StateMgr()
{
	LogMgr::logMessage(LogMgr::NORMAL, "Setting rendering state to default(MENU)");
	state = 0;
}

StateMgr::~StateMgr()
{
	LogMgr::logMessage(LogMgr::NORMAL, "Shutting down StateMgr");
}

void StateMgr::setState(int istateEnum)
{
	LogMgr::logMessage(LogMgr::NORMAL, "Setting state to: ", istateEnum);
	state = istateEnum;
}

int StateMgr::getState()
{
	return state;
}