#include "E_Config.h"
using namespace EEngine;

Config::Config()
{
	defaultSettings.clear();
}

Config::~Config()
{
}

bool Config::OpenConfig(string cnfgName)
{
	doc = XMLParser::addDocument(cnfgName);
	return true;
}

void Config::closeConfig()
{
	XMLParser::printFile(doc->name);
}

void Config::LoadDefaultSettings()
{
	
}