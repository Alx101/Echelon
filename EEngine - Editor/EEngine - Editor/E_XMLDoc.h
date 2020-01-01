#ifndef _XML_DOC_H_
#define _XML_DOC_H_

#include "common_header.h"
#include <rapidxml.hpp>
#include <rapidxml_iterators.hpp>

namespace EEngine
{
class XMLDoc
{
	public:
		XMLDoc();
		~XMLDoc();
		
		rapidxml::xml_node<>* getNode(char* nodeName);
		rapidxml::xml_attribute<>* getAttrib(char* nodeName, char* attrName);
		void addNode(string nodeName);
		void addChildNode(string nodeName, char* parentNode);
		void addChildNode(rapidxml::xml_node<>* node, string childNode);
		void addAttrib(string attribName, char* nodeName);
		template<typename T> void addValue(char* nodeName, char* attribName, T value);
		template<typename U> void addValue(char* nodeName, U value);


		//Public variables
		char* content;
		string name;
		rapidxml::xml_document<>* doc;
	private:
		
};
}

template<typename T> void EEngine::XMLDoc::addValue(char* nodeName, char* attribName, T value)
{
	if(doc->first_node(nodeName))
	{
		doc->first_node(nodeName)->first_attribute(attribName)->value((char*)value);
	}
}

template<typename U> void EEngine::XMLDoc::addValue(char* nodeName, U value)
{
	if(doc->first_node(nodeName))
	{
		doc->first_node(nodeName)->value((char*)value);
	}
}

#endif