#ifndef _SCENE_NODE_H_
#define _SCENE_NODE_H_

#include "common_header.h"
#include "E_Mesh.h"

namespace EEngine
{
class SceneNode
{
	public:
		SceneNode();
		~SceneNode();

		void attachShader(GLuint a_shader);
		bool drawNode();
		void setID(long int id);
		long int getID();
		void setName(string nodeName);
		glm::mat4 getMatrix();
		void setMatrix(glm::mat4 mat);
		string getName();

		void handleEvent(InputEvent& evt);

		Mesh* mesh;

	private:
		glm::mat4 modelMat;
		string name;
		int shaderCount;
		GLuint shader;
		unsigned long int ID;

};
}

#endif