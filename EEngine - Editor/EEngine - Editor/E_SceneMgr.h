#ifndef _SCENE_MGR_H_
#define _SCENE_MGR_H_

#include "common_header.h"
#include "E_SceneNode.h"
#include "E_ResourceMgr.h"
#include "E_GL.h"

//SceneMgr is to be used through either gameLayer or Editor
//No extra instances if SceneMgr is to be created

namespace EEngine
{
class SceneMgr
{
	public:
		SceneMgr();
		~SceneMgr();

		//SceneMgr does not handle it's own nodes, but rather the ones you supply it with
		//Nodes that needs to be added are noted in the map.xml file, then they are supplied to this manager
		SceneNode* getNodePtr(int ID);
		SceneNode* getNodePtr(string name);
		long int getNodeID(string name);

		SceneNode* addSceneNode(string nodeName);
		bool addTestNode(SceneNode* node);
		bool addNodeModel(SceneNode* node);
		bool addCameraNode(void* node);
		bool addNodeShader(SceneNode* node, string shaderName);
		bool addNodeShader(SceneNode* node, GLuint shader);
		bool addNodeShader(SceneNode* node, string vertName, string fragName, string shaderName);
		bool drawNodes();

	private:
		std::map<int, SceneNode*> nodeList;
		std::map<string, int> nodeIDList;
		std::map<int, SceneNode*>::iterator ndLstIt;
		
		unsigned long int nodeID;
};
}

#endif