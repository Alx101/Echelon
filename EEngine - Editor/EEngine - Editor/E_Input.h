#ifndef _E_INPUT_H_
#define _E_INPUT_H_

#include "common_header.h"
#include "E_SceneMgr.h"
#include "E_Core.h"

namespace EEngine
{
class Input
{
	public:

		Input(sf::Window* wnd, SceneMgr* sceneMgr, Core* aCore, bool defEvt = false);
		Input(sf::Window* wnd, vector<InputEvent> evtList);
		~Input();

		void regCore(Core* aCore);
		void regSceneMgr(SceneMgr* sceneMgr);
		void addEvent(InputEvent& evt);
		void popEvent(int keyEnum);
		void processInputs();
		void processEvt(InputEvent& evt);
		bool getKeystate(int key);

	private:
		Core* core;
		vector<int>::iterator iIt;
		vector<string>::iterator sIt;
		vector<InputEvent>::iterator eIt;
		map<int, InputEvent> keyList;
		map<int, InputEvent>::iterator keyIt;
		map<int, bool> keyState;
		bool defaultEvt;
		sf::Window* window;
		SceneMgr* sMgr;
};
}

#endif