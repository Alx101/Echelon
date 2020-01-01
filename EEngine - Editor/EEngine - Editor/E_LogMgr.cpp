#include "E_LogMgr.h"
using namespace EEngine;

LogMgr::LogMgr()
{
}

LogMgr::~LogMgr()
{
}

int LogMgr::E_ENGINE_LOG_PRIO;
void LogMgr::setLogPrio(int prio)
{
	E_ENGINE_LOG_PRIO = prio;
}

void LogMgr::addIndent(int count)
{
	indent += count;
}

void LogMgr::decrIndent(int count)
{
	indent -= count;
}

int LogMgr::indent = 0;
sf::Clock LogMgr::runClock;
sf::Time LogMgr::runTime = sf::seconds(0);
bool LogMgr::hasStarted = false;
int LogMgr::seconds = 0;
int LogMgr::milliseconds = 0;
int LogMgr::minutes = 0;
std::ofstream LogMgr::fLog;
map<int, string> LogMgr::prioString;
LogMgr::Out LogMgr::out;

bool LogMgr::createLog(const std::string &sLogName)
{
	LogMgr();
	prioString.clear();
	prioString[FAILURE] = "FAILURE";
	prioString[SUCCESS] = "SUCCESS";
	prioString[NORMAL] = "NORMAL";
	prioString[DEBUG] = "DEBUG";
	fLog.open(sLogName.c_str());
	if(fLog == NULL)
		return false;
	hasStarted = true;
	setLogPrio(NORMAL);
	LogMgr::out << "[ts]Log has been created!\n";
	return true;
}

bool LogMgr::closeLog()
{
	LogMgr::out << "[ts]Shutting down log..\n";
	fLog.flush();
	fLog.close();
	return true;
}

#ifdef _RELEASE
bool LogMgr::logMessage(LOGP logp, std::string message, bool output)
{
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
	switch (logp)
		{
			case LOW :
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "#LOW# : " << message << std::endl;
				break;
			case NORMAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "##NORMAL## : " << message << std::endl;
				break;
			case CRITICAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "###CRITICAL### : " << message << std::endl;
				break;
			default:
				break;
		}
	fLog.flush();
	return true;
}

bool LogMgr::logMessage(LOGP logp, std::string message, int nr, bool output)
{
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
	switch (logp)
		{
			case LOW :
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "#LOW# : " << message << nr << std::endl;
				break;
			case NORMAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "##NORMAL## : " << message << nr << std::endl;
				break;
			case CRITICAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "###CRITICAL### : " << message << nr << std::endl;
				break;
			default:
				break;
		}
	fLog.flush();
	return true;
}

bool LogMgr::logMessage(LOGP logp, std::string message, char xtra, bool output)
{
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
	switch (logp)
		{
			case LOW :
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "#LOW# : " << message << xtra << std::endl;
				break;
			case NORMAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "##NORMAL## : " << message << xtra << std::endl;
				break;
			case CRITICAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "###CRITICAL### : " << message << xtra << std::endl;
				break;
			default:
				break;
		}
	fLog.flush();
	return true;
}

bool LogMgr::logMessage(LOGP logp, std::string message, std::string xtra, bool output)
{
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
	switch (logp)
		{
			case LOW :
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "#LOW# : " << message << xtra << std::endl;
				break;
			case NORMAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "##NORMAL## : " << message << xtra << std::endl;
				break;
			case CRITICAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "###CRITICAL### : " << message << xtra << std::endl;
				break;
			default:
				break;
		}
	fLog.flush();
	return true;
}
#endif
#ifdef _DEBUG
bool LogMgr::logMessage(LOGP logp, std::string message, bool output)
{
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
	switch (logp)
		{
			case LOW :
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "#LOW# : " << message << std::endl;
				if(output) cout << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "#LOW# : " << message << std::endl;
				break;
			case NORMAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "##NORMAL## : " << message << std::endl;
				if(output) cout << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "##NORMAL## : " << message << std::endl;
				break;
			case CRITICAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "###CRITICAL### : " << message << std::endl;
				if(output) cout << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "###CRITICAL### : " << message << std::endl;
				break;
			default:
				break;
		}
	fLog.flush();
	return true;
}

bool LogMgr::logMessage(LOGP logp, std::string message, int nr, bool output)
{
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
	switch (logp)
		{
			case LOW :
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "#LOW# : " << message << nr << std::endl;
				if(output) cout << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "#LOW# : " << message << nr << std::endl;
				break;
			case NORMAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "##NORMAL## : " << message << nr << std::endl;
				if(output) cout << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "##NORMAL## : " << message << nr << std::endl;
				break;
			case CRITICAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "###CRITICAL### : " << message << nr << std::endl;
				if(output) cout << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "###CRITICAL### : " << message << nr << std::endl;
				break;
			default:
				break;
		}
	fLog.flush();
	return true;
}

bool LogMgr::logMessage(LOGP logp, std::string message, char xtra, bool output)
{
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
	switch (logp)
		{
			case LOW :
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "#LOW# : " << message << xtra << std::endl;
				if(output) cout << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "#LOW# : " << message << xtra << std::endl;
				break;
			case NORMAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "##NORMAL## : " << message << xtra << std::endl;
				if(output) cout << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "##NORMAL## : " << message << xtra << std::endl;
				break;
			case CRITICAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "###CRITICAL### : " << message << xtra << std::endl;
				if(output) cout << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "###CRITICAL### : " << message << xtra << std::endl;
				break;
			default:
				break;
		}
	fLog.flush();
	return true;
}

bool LogMgr::logMessage(LOGP logp, std::string message, std::string xtra, bool output)
{
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
	switch (logp)
		{
			case LOW :
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "#LOW# : " << message << xtra << std::endl;
				if(output) cout << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "#LOW# : " << message << xtra << std::endl;
				break;
			case NORMAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "##NORMAL## : " << message << xtra << std::endl;
				if(output) cout << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "##NORMAL## : " << message << xtra << std::endl;
				break;
			case CRITICAL:
				fLog << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "###CRITICAL### : " << message << xtra << std::endl;
				if(output) cout << "[" << minutes << "|" << seconds << "|" << milliseconds << "]" << "###CRITICAL### : " << message << xtra << std::endl;
				break;
			default:
				break;
		}
	fLog.flush();
	return true;
}
#endif