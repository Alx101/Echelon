#ifndef _E_CONFIG_H_
#define _E_CONFIG_H_

#include "common_header.h"
#include "E_XMLParser.h"
using namespace EEngine;
namespace EEngine
{
class Config
{
	public:
		Config();
		~Config();

		bool OpenConfig(string cnfgName);
		void closeConfig();
		void LoadDefaultSettings();
		template<typename T> void setDefaultSetting(string settingName, T value);
		template<typename T> void addSetting(string settingName, T value);
		template<typename T> void setSetting(rapidxml::xml_node<>* node, T value);
		template<typename T> void setSetting(string settingName, T value);
		void loadSettings(char* settingBuffer[]);
		char* getSetting(string settingName);

		XMLDoc* doc;
	private:
		map<string, char*> defaultSettings; 
};
}

template<typename O> void EEngine::Config::setDefaultSetting(string settingName, O value)
{
	defaultSettings[settingName] = (char*)value;
}

template<typename T> void EEngine::Config::addSetting(string settingName, T value)
{
	doc->addNode(settingName);
	doc->addValue(settingName.c_str(), value);
}

template<typename U> void EEngine::Config::setSetting(string settingName, U value)
{
	doc->getNode(settingName.c_str())->value((char*)value);
}

template<typename U> void EEngine::Config::setSetting(rapidxml::xml_node<>* node, U value)
{
	node->value((char*)value);
}

#endif