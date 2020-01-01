#include "E_Input.h"
using namespace EEngine;

//Minimal constructor
Input::Input(sf::Window* wnd, SceneMgr* sceneMgr, Core* aCore, bool defEvt)
{
	regCore(aCore);
	regSceneMgr(sceneMgr);
	window = wnd;
	defaultEvt = defEvt;
	keyList.clear();
	keyState.clear();
}

//Constructor with a pre-defined list of events
Input::Input(sf::Window* wnd, vector<InputEvent> evtList)
{
	window = wnd;
	keyList.clear();
	keyState.clear();
	for(eIt = evtList.begin(); eIt != evtList.end(); eIt++)
	{
		keyList[eIt->iKey] = *eIt;
		keyState[eIt->iKey] = false;
	}
}

Input::~Input()
{
	keyList.clear();
	keyState.clear();
}

//Important initialization step, registering core
void Input::regCore(Core* aCore)
{
	core = aCore;
}

//Important initialization step, registering sceneMgr
void Input::regSceneMgr(SceneMgr* sceneMgr)
{
	sMgr = sceneMgr;
}

//For adding a key event
void Input::addEvent(InputEvent& evt)
{
	keyList[evt.iKey] = evt;
	keyState[evt.iKey] = false;
}


//For removing a key event
void Input::popEvent(int keyEnum)
{
	keyList.erase(keyEnum);
	keyState.erase(keyEnum);
}

//Function for processing events
void Input::processEvt(InputEvent& evt)
{
	switch(evt.iEvtTarget)
	{
		case inputCode::NODE:
			sMgr->getNodePtr(evt.nodeName)->handleEvent(evt);
			break;
		case inputCode::CORE:
			for(iIt = evt.msg.iParam.begin(); iIt != evt.msg.iParam.end(); iIt++)
			{
				if(*iIt == inputCode::core::TOGGLEFPS)
				{
					if(!evt.bPrevPressed)
						core->toggleFPS();
					break;
				}
				if(*iIt == inputCode::core::SHUTDOWN)
				{
					if(!evt.msg.sParam.empty())
					{
						for(sIt = evt.msg.sParam.begin(); sIt != evt.msg.sParam.end(); sIt++)
						{
							LogMgr::logMessage(LogMgr::NORMAL, *sIt);
						}
					}
					core->releaseEngine();
				}
				break;
			}
			break;
		case inputCode::CUSTOM:
			evt.customFunc(evt.msg);
			break;
		default:
			break;
	}
}

//Main update function
void Input::processInputs()
{
	for(keyIt = keyList.begin(); keyIt != keyList.end(); keyIt++)
	{
		if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keyIt->first))
		{
			processEvt(keyList[keyIt->first]);
			if(!keyState[keyIt->first])
			{
				keyState[keyIt->first] = true;
				keyList[keyIt->first].bPrevPressed = keyState[keyIt->first];
			}
		}
		else
		{
			if(keyList.count(keyIt->first))
			{
				if(keyState[keyIt->first])
				{
					keyState[keyIt->first] = false;
					keyList[keyIt->first].bPrevPressed = keyState[keyIt->first];
				}
			}
		}
	}
}

bool Input::getKeystate(int key)
{
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}