#include "E_SceneNode.h"
using namespace EEngine;

SceneNode::SceneNode()
{
	shaderCount = 0;
	ID = 0;
	name = "";
	mesh = new Mesh();
}

SceneNode::~SceneNode()
{
	if(mesh) delete mesh;
}

bool SceneNode::drawNode()
{
	//This is ONLY temporary code, this WILL be changed'
	glUseProgram(shader);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->getVBO(Mesh::VERTEX_VBO));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	glUseProgram(0);
	return true;
}

void SceneNode::attachShader(GLuint a_shader)
{
	shader = a_shader;
}

void SceneNode::setID(long int id)
{
	//Set the ID of the sceneNode
	ID = id;
}

long int SceneNode::getID()
{
	//Return the ID of the sceneNode
	return ID;
}

void SceneNode::setName(string nodeName)
{
	name = nodeName;
}

string SceneNode::getName()
{
	return name;
}

glm::mat4 SceneNode::getMatrix()
{
	return modelMat;
}

void SceneNode::setMatrix(glm::mat4 mat)
{	
	modelMat = mat;
}

//Function for handling events
void SceneNode::handleEvent(InputEvent& evt)
{
	//Will be filled with actions to each event (customizable)
}