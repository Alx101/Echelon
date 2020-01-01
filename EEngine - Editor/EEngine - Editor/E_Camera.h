//SEE CAMERA.TXT IN PROGRAMMER_ECHOES FOR AN EXPLANATION AND EXAMPLE USE OF THE CLASS
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "common_header.h"
#include "E_SceneMgr.h"

namespace EEngine
{
class Camera : public SceneNode
{
	public:
		void look();
		void rotateViewY(float fAngle);
		void move(glm::vec3 by);

		glm::mat4 getView();
		glm::mat4 getProj();

		Camera();
		Camera(glm::vec3 a_pos, glm::vec3 a_foc, glm::vec3 a_up, float a_fSpeed);
	private:
		glm::mat4 mView;		//Camera View Matrix
		glm::vec3 Pos, Foc, Up;//Eye, Field of View, Up
		float fSpeed;			//Speed of user
};
}

#endif