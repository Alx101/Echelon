#ifndef _CORE_H_
#define _CORE_H_

#include "common_header.h"
#include "E_Window.h"
#include "E_Subsystems.h"
#include "E_SceneMgr.h"
#include "E_Config.h"

namespace EEngine
{
class Core
{
public:
	Core();
	~Core();

	bool initEngine();
	bool setMainWindow(E_Window &wnd);
	void updateCore();
	void pumpEngineEvt();
	bool registerSceneMgr(EEngine::SceneMgr* mgr);
	void releaseEngine();
	void toggleFPS();

private:
	bool doneShutdown;
	Subsystems* subsystems;
	E_Window* window;
	sf::Time sleepTime;
	std::string title;
	SceneMgr* sceneMgr;

};
}

#endif