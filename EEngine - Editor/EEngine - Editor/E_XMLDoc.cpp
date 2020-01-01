#include "E_XMLDoc.h"
using namespace EEngine;
using namespace rapidxml;

XMLDoc::XMLDoc()
{
}

XMLDoc::~XMLDoc()
{
	delete doc;
}

xml_node<>* XMLDoc::getNode(char* nodeName)
{
	if(!doc->first_node(nodeName))
	{
		LogMgr::logMessage(LogMgr::CRITICAL, nodeName, " does not exist in this document. Notice: CaSe SeNsEtIvE!");
		return NULL;
	}
	return doc->first_node(nodeName);
}

xml_attribute<>* XMLDoc::getAttrib(char* nodeName, char* attrName)
{
	if(!doc->first_node(nodeName))
	{
		LogMgr::logMessage(LogMgr::CRITICAL, nodeName, " does not exist in this document! Notice: CaSe SeNsEtIvE!");
		return NULL;
	}
	if(!doc->first_node(nodeName)->first_attribute(attrName))
	{
		LogMgr::logMessage(LogMgr::CRITICAL, attrName, " does not exist in this document! Notice: CaSe SeNsEtIvE!");
		return NULL;
	}
	return doc->first_node(nodeName)->first_attribute(attrName);
}

void XMLDoc::addNode(string nodeName)
{
	char* name = doc->allocate_string(nodeName.c_str());
	rapidxml::xml_node<>* node = doc->allocate_node(rapidxml::node_element, name);
	doc->append_node(node);
}

void XMLDoc::addChildNode(string nodeName, char* parentNode)
{
	if(doc->first_node(parentNode))
	{
		char* name = doc->allocate_string(nodeName.c_str());
		rapidxml::xml_node<>* node = doc->allocate_node(rapidxml::node_element, name);
		doc->first_node(parentNode)->append_node(node);
	}
}

void XMLDoc::addChildNode(xml_node<>* node, string childNode)
{
	char* name = doc->allocate_string(childNode.c_str());
	xml_node<>* cNode = doc->allocate_node(rapidxml::node_element, name);
	node->append_node(cNode);
}

void XMLDoc::addAttrib(string attribName, char* nodeName)
{
	if(doc->first_node(nodeName))
	{
		char* name = doc->allocate_string(attribName.c_str());
		rapidxml::xml_attribute<>* attrib = doc->allocate_attribute(name);
		doc->first_node(nodeName)->append_attribute(attrib);
	}
}