#include "E_FileMgr.h"
using namespace EEngine;

FileMgr::FileMgr()
{
}

FileMgr::~FileMgr()
{
}

string FileMgr::path = "";
string FileMgr::target = "";
int FileMgr::fileLength = 0;
map<string, std::fstream*> FileMgr::fileList;
map<string, char*> FileMgr::fileConts;
map<string, std::fstream*>::iterator FileMgr::it;
map<string, char*>::iterator FileMgr::cIt;
FileMgr::Io FileMgr::io;


bool FileMgr::addFile(string filename)
{
	if(fileList.count(filename))
	{
		LogMgr::out << ts << filename << " already exists! Opening file...\n";
		fileList[filename]->open(path+filename);
		return true;
	}
	fstream* file = new fstream();
	//Assumes both reading and writing (true in most cases)
	file->open(path+filename, ios::in | ios::out);
	if(file->bad())
		return false;
	fileList[filename] = file;
	file->seekg(0, ios::beg);
	file->seekg(0, ios::end);
	fileLength = file->tellg();
	if(fileLength < 0)
		return false;
	char* buffer = new char[fileLength];
	file->seekg(0, ios::beg);
	file->read(buffer, fileLength);
	fileConts[filename] = buffer;
	return true;
}

bool FileMgr::clearFile(string filename)
{
	if(fileList.count(filename))
	{
		LogMgr::out << "[ts]Clearing " << filename << "\n";
		fileList[filename]->clear();
	}
	else
	{
		LogMgr::out << ts << filename << " does not exist! Skipping file\n";
		return false;
	}
	return true;
}

bool FileMgr::closeFile(string filename)
{
	if(fileList.count(filename))
	{
		if(fileList[filename]->is_open())
		{
			LogMgr::out << "[ts]Closing " << filename << "\n";
			fileList[filename]->close();
		}
	}
	else
	{
		LogMgr::out << ts << filename << " does not exist! Skipping file...\n";
		return false;
	}
	return true;
}

bool FileMgr::popFile(string filename)
{
	if(fileList.count(filename))
	{
		LogMgr::out << ts << "Popping " << filename << lEnd;
		delete fileList[filename];
		fileList.erase(filename);
	}
	else
	{
		LogMgr::out << ts << filename << " does not exist! Skipping file...\n";
		return false;
	}
	return true;
}

bool FileMgr::setTarget(string filename)
{
	if(fileList.count(filename))
	{
		target = filename;
		addFile(filename);
	}
	else
		return false;
	return true;
}

bool FileMgr::setFilePath(string sPath)
{
	LogMgr::out << "[ts]Setting filepath to :" << sPath << "\n";
	path = sPath;
	LogMgr::addIndent(1);
	LogMgr::setLogPrio(SUCCESS);
	LogMgr::decrIndent(1);
	return true;
}


char* FileMgr::getFileContent(string filename)
{
	LogMgr::out << "[ts]Looking for file " << filename << lEnd;
	LogMgr::addIndent(1);
	if(fileList.count(filename))
	{
		if(fileConts.count(filename))
		{
			LogMgr::setLogPrio(SUCCESS);
			LogMgr::out << ts << filename << " found! Returning contents\n";
			LogMgr::decrIndent(1);
			return fileConts[filename];
		}
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << ts << filename << " does not exist! Setting buffer to \"\"\n";
		LogMgr::decrIndent(1);
		return NULL;
	}
	else
	{
		LogMgr::setLogPrio(FAILURE);
		LogMgr::out << ts << filename << " does not exist! Setting buffer to \"\"\n";
		LogMgr::decrIndent(1);
		return NULL;
	}
}

char* FileMgr::getShaderContent(string filename)
{
	FILE* fp;
	char *content = NULL;

	int count=0;
	string fullpath = path+filename;
	fopen_s( &fp, fullpath.c_str(),"rt");
	if (fp != NULL) 
	{
		fseek(fp, 0, SEEK_END);
		count = ftell(fp);
		rewind(fp);
		if (count > 0) 
		{
			content = (char *)malloc(sizeof(char) * (count+1));
			count = fread(content,sizeof(char),count,fp);
			content[count] = '\0';
		}
		fclose(fp);
	}
	fileConts[filename] = content;
	return content;
}

fstream* FileMgr::getFilePtr(string filename)
{
	if(fileList.count(filename))
	{
		if(!fileList[filename]->is_open())
			fileList[filename]->open(path+filename);
		return fileList[filename];
	}
	LogMgr::setLogPrio(FAILURE);
	LogMgr::out << ts << filename << " has not been registered to FileMgr!\n";
	return NULL;
}

bool FileMgr::startUp()
{
	fileList.clear();
	fileConts.clear();
	fileLength = 0;
	path = "";
	fstream* file = new fstream();
	file->open("garbage.txt", 'rw');
	fileList[""] = file;
	return true;
}

bool FileMgr::cleanUp()
{
	LogMgr::out << "[ts]Cleaning up after open files, this may take a while...\n";
	LogMgr::addIndent(1);
	for(it = fileList.begin(); it != fileList.end(); it++)
	{
		if(it == fileList.end())
		{
			LogMgr::setLogPrio(SUCCESS);
			LogMgr::decrIndent(1);
			LogMgr::out << "[ts]Done!\n";
			return true;
		}
		if(it->second->is_open())
		{
			LogMgr::out << "[ts]Closing " << it->first << "\n";
			it->second->flush();
			it->second->close();
		}
		delete it->second;
	}
	for(cIt = fileConts.begin(); cIt != fileConts.end(); ++cIt)
	{
		delete cIt->second;
	}
	fileConts.clear();
	fileList.clear();
	LogMgr::setLogPrio(SUCCESS);
	LogMgr::decrIndent(1);
	LogMgr::out << "[ts]Done!\n";
	return true;
}