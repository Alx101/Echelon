#ifndef _AI_
#define _AI_

#include "common_header.h"
#include "E_SceneMgr.h"
#include "E_Lines.h"


//Commented out till needed&fixed

namespace EEngine 
{

class Condition
{
	int test;
};

class Event
{
	int test;
};

class AI 
{
	
	public:
	//	AI(SceneMgr* SceneMgr);
	//	~AI();
		void check();

	/*
		void setStat();
		
		void setAllyType();
		void setEnemyType();
		
		void setDetectRange();
		void setFollowRange();
		void setIdleRange();
		void setAttackRange();

		void createCondition(char name, char script);
		void createEvent(char name, char script);
		
		void runCondition(char name);
		void runEvent(char name);
		
		void determinIfEntitieClose(int id);
		void addEntitie(int id);

		bool Updated;
	private:
		void update();

		SceneMgr* Mgr;
		int closestEntitie;
		SceneNode *curTarget;

		map<int, SceneNode*> closeEntities;
		map<char, Condition*> conditions;
		map<char, Event*> Events;

		vectors test1;
		vectors test2;

		pathline *path;
	*/
};

}

#endif