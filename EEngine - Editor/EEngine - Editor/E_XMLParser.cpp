#include "E_XMLParser.h"
using namespace EEngine;

XMLParser::XMLParser()
{
	docList.clear();
	
}

XMLParser::~XMLParser()
{
	LogMgr::logMessage(LogMgr::NORMAL, "Cleaning up after XML files, this may take a while...");
	for(it = docList.begin(); it != docList.end(); it++)
	{
		LogMgr::logMessage(LogMgr::NORMAL, "Killing: ", it->first);
		delete it->second;
	}
	docList.clear();
}

map<string, XMLDoc*> XMLParser::docList;
map<string, XMLDoc*>::iterator XMLParser::it;

XMLDoc* XMLParser::addDocument(string docName)
{
	XMLDoc* Doc = new XMLDoc();
	Doc->name = docName;
	FileMgr::addFile(docName);
	Doc->content = FileMgr::getFileContent(docName);
	rapidxml::xml_document<>* tDoc = new rapidxml::xml_document<>;
	tDoc->parse<rapidxml::parse_no_data_nodes>(Doc->content);
	Doc->doc = tDoc;
	docList[docName] = Doc; //Will sort this after BST later
	FileMgr::closeFile(docName);
	return Doc;
}

XMLDoc* XMLParser::getDoc(string docName)
{
	if(docList.count(docName))
	{
		return docList[docName];
	}
	else
	{
		LogMgr::logMessage(LogMgr::CRITICAL, docName, " does not exist! Add document first!");
		return NULL;
	}
}

void XMLParser::printFile(string docName)
{	
	string buffer;
	rapidxml::print(std::back_inserter(buffer), *docList[docName]->doc);
	FileMgr::setTarget(docName);
	FileMgr::io << buffer;
	FileMgr::closeFile(docName);
}