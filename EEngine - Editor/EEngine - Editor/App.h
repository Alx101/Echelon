#ifndef _APP_H_
#define _APP_H_

#include "EchoesEngine.h"
#include "E_Input.h"
#include "E_Camera.h"
#include "E_FXsystem.h"

class App
{
public:
	App();
	~App();

	bool run();
	bool init();
	static void shutDown(EvtMsg msg);

private:
	EEngine::Engine* engine;
	EEngine::Core* core;
	EEngine::E_Window window;
	EEngine::SceneMgr* sceneMgr;
	EEngine::SceneNode* node;
	EEngine::Input* inputSystem;
	sf::Event evt;
	FXsystem fxSystem;
};

#endif