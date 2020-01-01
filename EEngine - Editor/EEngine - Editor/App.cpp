#include "App.h"

App::App()
{
	engine = new EEngine::Engine();
	core = engine->core;
	sceneMgr = new EEngine::SceneMgr();
}

App::~App()
{
	delete inputSystem;
	delete sceneMgr;
	delete engine;
}

bool App::init()
{
	if(!core->initEngine()) 
		return false;
	if(!core->setMainWindow(window))
		return false;
	window.createMainWindow(800, 600, 0, "Der Ritter");
	inputSystem = new EEngine::Input(&window.window, sceneMgr, core, false);
	EEngine::InputEvent Evt;
	EEngine::InputEvent Evt2;
	EEngine::InputEvent Evt3;

	Evt.iEvtTarget = inputCode::CORE;
	Evt.msg.iParam.push_back(inputCode::core::SHUTDOWN);
	Evt.iKey = keyCode::Escape;

	Evt2.iEvtTarget = inputCode::CORE;
	Evt2.msg.iParam.push_back(inputCode::core::TOGGLEFPS);
	Evt2.iKey = keyCode::P;

	Evt3.iEvtTarget = inputCode::CUSTOM;
	Evt3.iKey = keyCode::Q;
	Evt3.customFunc = &shutDown;
	Evt3.msg.sParam.push_back("HI!");

	inputSystem->addEvent(Evt);
	inputSystem->addEvent(Evt2);
	inputSystem->addEvent(Evt3);
	core->registerSceneMgr(sceneMgr);
	core->toggleFPS();

	EEngine::ResourceMgr::setResourcePath("..\\Resources\\");
	EEngine::ResourceMgr::setShaderPath("Shaders\\");

	fxSystem.importFX("..\\Resources\\FX\\");


	node = sceneMgr->addSceneNode("Triangle");
	//fxSystem.makeBigFile();
	sceneMgr->addNodeModel(sceneMgr->getNodePtr("Triangle"));
	if(!sceneMgr->addNodeShader(node, EEngine::E_GL::E_GLSL::loadBasicShader()))
	{
		return false;
	}
	return true;
}

bool App::run()
{
	if(!init()) return false;
	while(!window.bClosed)
	{
		core->updateCore();
		inputSystem->processInputs();
		window.drawWindow();
	}
	return true;
}

void App::shutDown(EvtMsg msg)
{
	if(!msg.sParam.empty())
		LogMgr::logMessage(LogMgr::NORMAL, "I WAS CALLED, SHUTDOWN(): ", msg.sParam.begin()->c_str());
	else
		LogMgr::logMessage(LogMgr::NORMAL, "I WAS CALLED, SHUTDOWN(): NOTHING IN S-VECTOR");
}