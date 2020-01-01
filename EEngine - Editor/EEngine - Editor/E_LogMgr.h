#pragma warning(disable: 4244)

#ifndef _LOG_MGR_HPP_
#define _LOG_MGR_HPP_
#include <fstream>
#include <string>
#include <assert.h>
#include <iostream>
#include <SFML\System.hpp>
#include <map>
#include <string>
using namespace std;

enum E_ENGINE_LOG_PRIO_ENUMS
{
	FAILURE,
	START,
	SUCCESS,
	NORMAL,
	DEBUG,
};

namespace EEngine
{
class LogMgr
{
public:
	static int E_ENGINE_LOG_PRIO;
	static void setLogPrio(int prio);

public:
	LogMgr();
	~LogMgr();

	static bool createLog(const std::string &sLogName);
	static bool closeLog();
	static void addIndent(int count);
	static void decrIndent(int count);

	static bool hasStarted;

	//DEPRECEATED!
	//__________________________________________________________________________________
	enum LOGP { LOW, NORMAL, CRITICAL };

	static bool logMessage(LOGP logp, std::string message, bool outPut = true);
	static bool logMessage(LOGP logp, std::string message, int nr, bool outPut = true);
	static bool logMessage(LOGP logp, std::string message, char xtra, bool outPut = true);
	static bool logMessage(LOGP logp, std::string message, std::string xtra, bool outPut = true);
	//__________________________________________________________________________________
	
	//Standard log output. The prefix string will be surrounded by '#' and ended with ':'
	struct Out
	{
		Out& operator<< (const std::string& message)
		{
			string object = message;
			string tmp = "";
			bool Ts = false;
			string timeStampID = "[ts]";
			if(message.size() >= 4)
			{
				for(int i = 0; i <4; ++i)
				{
					tmp += object[i];
				}
				if(tmp == timeStampID)
				{
					object.erase(object.begin(), object.begin()+4);
					Ts = true;
				}
			}
			runTime = runClock.getElapsedTime();
			milliseconds = runTime.asMilliseconds();
			while(milliseconds > 1000)
			{
				seconds++;
				milliseconds -= 1000;
			}
			seconds = runTime.asSeconds();
			while(seconds > 60)
			{
				minutes++;
				seconds -= 60;
			}
			if(Ts)
			{
				LogMgr::fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << '#' << prioString[E_ENGINE_LOG_PRIO] << "#: ";
				for(int i = 0; i < indent; ++i)
				{
					LogMgr::fLog << "\t";
				}
				assert(prioString.count(E_ENGINE_LOG_PRIO));
				LogMgr::fLog  << object;
			}
			else
				LogMgr::fLog  << object;
			fLog.flush();
	#ifdef _DEBUG
			if(Ts)
			{
				cout << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << '#' << prioString[E_ENGINE_LOG_PRIO] << "#: ";
				for(int i = 0; i < indent; ++i)
				{
					cout << "\t";
				}
				cout  << object;
			}
			else
				cout << object;
	#endif
			E_ENGINE_LOG_PRIO = NORMAL;
			return *this;
		}
	};

	static Out out;
private:
	static int indent;
	static int seconds;
	static int milliseconds;
	static int minutes;
	static sf::Time runTime;
	static sf::Clock runClock;
	static std::ofstream fLog;
	static map<int, string> prioString;
};
}
#endif