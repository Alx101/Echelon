#include "E_Camera.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace EEngine;

const float BASE = 25.0;

//set up a camera at the "origin" with a default projection matrix
Camera::Camera(): Pos(0.0f, 0.0f, 0.0f), Foc(0.0f, 0.0f, 0.0f), Up(0.0f, 1.0f, 0.0f), fSpeed(BASE)
{
	mView - glm::lookAt(Pos, Foc, Up);
}

//setting up a camera with pre-determined parameters
Camera::Camera(glm::vec3 a_pos, glm::vec3 a_foc, glm::vec3 a_up, float a_fSpeed)
{
	Pos = a_pos;
	Foc = a_foc;
	Up = a_up;
	fSpeed = a_fSpeed;
	mView = glm::mat4(1.0);
}

//return 4x4 matrix to be used as the model matrix 
void Camera::look()
{
	mView = glm::lookAt(Pos, Foc, Up);
}

//rotate the camera upon the y axis(east/west)
void Camera::rotateViewY(float fAngle)
{
	glm::mat4 mRotation = glm::rotate(glm::mat4(1.0f), fAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 vDir = Foc - Pos;
	glm::vec4 vNewView = mRotation * glm::vec4(vDir, 1.0f);
	Foc = glm::vec3(vNewView.x, vNewView.y, vNewView.z);
	Foc += Pos;
}

//move the camera north/south
void Camera::move(glm::vec3 by)
{
	glm::vec3 vDir = Foc - Pos;
	vDir *= by;
	Pos += vDir;
	Foc += vDir;
}

glm::mat4 Camera::getView()
{
	return mView;
}