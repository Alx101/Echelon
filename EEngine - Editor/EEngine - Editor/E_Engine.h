#ifndef _ENGINE_H_
#define _ENGINE_H_

#ifdef _RELEASE
#define WIN_32_LEAN_AND_MEAN
#endif

//#include "GameLayer.h"
#include "E_Core.h"
#include "common_header.h"
#include "E_Window.h"

namespace EEngine
{
class Engine
{
public:
	Engine();
	~Engine();

	Core* core; 
private:
	std::string logName;
};
}
#endif

//Thinking about design...