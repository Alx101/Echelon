#include "E_Subsystems.h"
using namespace EEngine;

Subsystems::Subsystems()
{
	//Any creation of subsystem objects should be done here
	testing = new tester();
}

Subsystems::~Subsystems()
{
	//Any deletion of subsystem objects should be done here
	delete testing;
}

bool Subsystems::initAllSubsystems(int wndW, int wndH)
{
	//Startup function for ALL subsystems
	LogMgr::out << ts << "Starting up all subsystems..." << lEnd;
	LogMgr::addIndent(1);
	if(!E_GL::startup(wndW, wndH))
		return false;
	if(!FileMgr::startUp())
		return false;
	LogMgr::decrIndent(1);
	LogMgr::setLogPrio(SUCCESS);
	LogMgr::out << ts << "Done!" << lEnd;
	return true;
}

bool Subsystems::shutdownAllSubsystems()
{
	//Shutdown function for ALL subsystems
	LogMgr::out << ts << "Shutting down all subsystems..." << lEnd;
	LogMgr::addIndent(1);
	if(!E_GL::shutdown())
		return false;
	if(!FileMgr::cleanUp())
		return false;
	LogMgr::decrIndent(1);
	LogMgr::setLogPrio(SUCCESS);
	LogMgr::out << ts << "Done!" << lEnd;
	return true;
}

bool Subsystems::updateAllSubsystems()
{
	E_GL::renderFrame();
	testing->Update();
	return true;
}