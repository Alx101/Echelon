#ifndef _STATE_MGR_H_
#define _STATE_MGR_H_

#include "common_header.h"


namespace EEngine
{
class StateMgr
{
	public:
		StateMgr();
		~StateMgr();

		void setState(int istateEnum);
		int getState();

	private:
		int state;
		

};
}

#endif