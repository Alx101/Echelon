#ifndef _E_MVP_KEEPER_
#define _E_MVP_KEEPER_

#include <glm\gtc\matrix_transform.hpp>

class MVPKeeper
{
	public:
		static void setModel(glm::mat4 M)
		{
			m = M;
		}
		static void setView(glm::mat4 V)
		{
			v = V;
		}
		static void setProj(glm::mat4 P)
		{
			p = P;
		}
		static glm::mat4 getMVP()
		{
			glm::mat4 mv = v*m;
			mvp = p*mv;
			return mvp;
		}

	private:
		static glm::mat4 mvp;
		static glm::mat4 p;
		static glm::mat4 v;
		static glm::mat4 m;
}

#endif