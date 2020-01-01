#ifndef _SUBSYSTEMS_H_
#define _SUBSYSTEMS_H_

#include "E_GL.h"
#include "E_ScriptAbstr.h"
#include "E_FileMgr.h"
#include "common_header.h"
#include "E_StateMgr.h"
#include "E_XMLParser.h"
#include "E_Testing.h"
#include "E_Testing.h"

namespace EEngine
{
class Subsystems
{
public:
	Subsystems();
	~Subsystems();

	bool initAllSubsystems(int wndW, int wndH);
	bool shutdownAllSubsystems();
	bool updateAllSubsystems();

private:
	tester* testing;

};
}

#endif