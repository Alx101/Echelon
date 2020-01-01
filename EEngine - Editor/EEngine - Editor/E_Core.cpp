#include "E_Core.h"
using namespace EEngine;

Core::Core()
{
	sleepTime = sf::milliseconds(500);
	window = NULL;
	subsystems = new Subsystems();
	doneShutdown = false;
}

Core::~Core()
{
	if(!doneShutdown)
		releaseEngine(); //Safer way to remove all things
	if(subsystems) delete subsystems;
	//Shut down subsystems
}

bool Core::initEngine()
{
	//Initialize OpenGL subsystems (requires some extra initialization)
	LogMgr::out << "[ts]Starting up core systems..." << lEnd;
	LogMgr::addIndent(1);
	if(!subsystems->initAllSubsystems(1, 1))
	{
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << "[ts]Failed to initialize core systems!" << lEnd;
		LogMgr::decrIndent(1);
		return false;
	}
	LogMgr::decrIndent(1);
	LogMgr::setLogPrio(SUCCESS);
	LogMgr::out << ts << "Done!" << lEnd;
	
	STARTUPINFO          si = { sizeof(si) };
	PROCESS_INFORMATION  pi;
	char                 szExe[] = "glewinfo.exe";
 
	if(CreateProcess(0, szExe, 0, 0, FALSE, 0, 0, 0, &si, &pi))
	{
	   // optionally wait for process to finish
	   WaitForSingleObject(pi.hProcess, INFINITE); 
	   LogMgr::setLogPrio(SUCCESS);
	   LogMgr::addIndent(1);
	   LogMgr::out << ts << "Sucessfully executed gleinfo.exe" << lEnd;
	   LogMgr::decrIndent(1);
	   CloseHandle(pi.hProcess);
	   CloseHandle(pi.hThread);
	}
	return true;
}

bool Core::setMainWindow(E_Window &wnd)
{
	if(&wnd != NULL)
	{
		LogMgr::out << ts << "Setting main window " << lEnd;
		window = &wnd;
		E_GL::resize(window->width, window->height);
		return true;
	}
	else if(&wnd == NULL)
	{
		LogMgr::setLogPrio(FAILURE);
		LogMgr::addIndent(1);
		LogMgr::out << ts << "Provided window pointer is NULL!" << lEnd;
		LogMgr::decrIndent(1);
		return false;
	}
	return false;
}

bool Core::registerSceneMgr(SceneMgr* mgr)
{
	if(!mgr)
	{
		return false;
	}
	sceneMgr = mgr;
	return true;
}

void Core::updateCore()
{
	if(window->isFocused())
	{
		if(window->defaultEvtProc)
		{
			window->pumpMessages();
		}
		subsystems->updateAllSubsystems();
		sceneMgr->drawNodes();
	}
	else
	{
		if(window->defaultEvtProc)
		{
			window->pumpMessages();
			sf::sleep(sleepTime);
		}
	}
}

void Core::pumpEngineEvt()
{
	//E_EngineEvt::pumpMessageQueue();
}

void Core::releaseEngine()
{
	window->closeWindow();
	LogMgr::out << ts << "Shutting down Core" << lEnd;
	LogMgr::addIndent(1);
	if(!subsystems->shutdownAllSubsystems())
	{
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << ts << "Could not shut down core system! SOMETHING IS TERRIBLY WRONG!" << lEnd;
	}
	LogMgr::decrIndent(1);
	doneShutdown = true;
}

void Core::toggleFPS()
{
	window->toggleDrawFPS();
}