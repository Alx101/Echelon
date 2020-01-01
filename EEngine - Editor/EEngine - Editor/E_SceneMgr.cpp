#include "E_SceneMgr.h"
using namespace EEngine;

SceneMgr::SceneMgr()
{
	//Initialize variables
	nodeID = 0;
	nodeList.clear();
	nodeIDList.clear();
}

SceneMgr::~SceneMgr()
{
	//When SceneMgr is not needed anymore, ModelImporter won't be needed either
	LogMgr::out << ts << "Destroying scene nodes, this may take a while..." << lEnd;
	LogMgr::addIndent(1);
	for(ndLstIt = nodeList.begin(); ndLstIt != nodeList.end(); ++ndLstIt)
	{
		LogMgr::out << ts <<  "Killing: " << ndLstIt->second->getName() << lEnd;
		delete ndLstIt->second;
	}
	LogMgr::decrIndent(1);
	LogMgr::setLogPrio(SUCCESS);
	LogMgr::out << ts << "Done!" << lEnd;
	nodeIDList.clear();
	nodeList.clear();
}

SceneNode* SceneMgr::getNodePtr(int ID)
{
	if(nodeList.count(ID))
	{
		return nodeList[ID];
	}
	else
	{
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << ts << "No node with the ID of " << intToString(ID) << " exists!" << lEnd;
		return NULL;
	}
}

SceneNode* SceneMgr::getNodePtr(string name)
{
	if(nodeIDList.count(name))
	{
		return getNodePtr(nodeIDList[name]);
	}
	else
	{
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << ts << "No node with the name of " << name << " exists!(getNodePtr)" << lEnd;
		return NULL;
	}
}

long int SceneMgr::getNodeID(string name)
{
	if(nodeIDList.count(name))
	{
		return nodeIDList[name];
	}
	else
	{
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << ts << "No node with the name of " << name << " exists!(getNodeID)" << lEnd;
		return NULL;
	}
}

SceneNode* SceneMgr::addSceneNode(string nodeName)
{
	//Add a new sceneNode to the sceneNode list (node pointer, ID)
	SceneNode* node = new SceneNode;
	nodeID++;
	node->setID(nodeID);
	node->setName(nodeName);
	string nameBuffer = nodeName;
	nodeList[nodeID] = node;
	nodeIDList[nameBuffer] = nodeID;
	return node;
}

bool SceneMgr::addNodeShader(SceneNode* node, string shaderName)
{
	GLuint i = ResourceMgr::loadShader(shaderName);
	if(i == NULL)
	{
		return false;
	}
	node->attachShader(i);
	return true;
}

bool SceneMgr::addNodeShader(SceneNode* node, GLuint shader)
{
	node->attachShader(shader);
	return true;
}

bool SceneMgr::addNodeShader(SceneNode* node, string vertName, string fragName, string shaderName)
{
	GLuint i = ResourceMgr::loadShader(vertName, fragName, shaderName);
	if(i == NULL)
	{
		return false;
	}
	node->attachShader(i);
	return true;
}

bool SceneMgr::addNodeModel(SceneNode* node)
{
	//Add a model to the sceneNode specified
	node->mesh->setVBO(E_GL::triangle(node->mesh->getVBO(Mesh::VERTEX_VBO), node->mesh->getVAO()), Mesh::VERTEX_VBO);
	return true;
}

bool SceneMgr::drawNodes()
{
	for(ndLstIt = nodeList.begin(); ndLstIt != nodeList.end(); ++ndLstIt)
	{
		ndLstIt->second->drawNode();
	}
	return true;
}