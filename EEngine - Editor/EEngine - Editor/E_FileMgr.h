#ifndef _FILE_MGR_H_
#define _FILE_MGR_H_

#include "common_header.h"

namespace EEngine
{
class FileMgr
{
public:
	FileMgr();
	~FileMgr();
	//Adds a file to the fileList map and opens it. If the file is already added, it opens the file
	//When addFile adds a new file it stores the file contents to a buffer, which is later delted (cleanUp)
	static bool addFile(string fileName);  
	//Clears a file, this can be done manually, but it is nice to have a function for it
	static bool clearFile(string fileName);
	//Closes an open file but does NOT remove it from the list
	static bool closeFile(string fileName);
	//Removes a file from the fileList map, if it is open, it closes it too
	static bool popFile(string filename);
	//Sets the target of which the operators will work on (remember to always re-set this after use)
	static bool setTarget(string filename);
	//Sets the target path of the file (ex. ..\\Resources\\\Files\\)
	static bool setFilePath(string sPath);
	//Returns full contents of a file
	static char* getFileContent(string filename);
	//Same as above, only uses FILE* (specific for shader files)
	static char* getShaderContent(string filename);
	//Get fstream pointer
	static fstream* getFilePtr(string filename);
	//General startUp function (optional)
	static bool startUp();
	//Gemeral cleanUp function (optional but strongly recommended)
	static bool cleanUp();

	//Input operator which acts on the currently set target
	struct Io
	{
		template<typename T>
		Io& operator<< (const T& object)
		{
			*fileList[target] << object;
			return *this;
		}
		template<typename T>
		Io& operator>> (const T& object)
		{
			*fileList[target] >> object;
			return *this;
		}
	};
	static Io io;

private:
	static string path;
	static string target;
	static int fileLength;
	static map<string, fstream*> fileList;
	static map<string, char*> fileConts;
	static map<string, fstream*>::iterator it;
	static map<string, char*>::iterator cIt;

};
}

#endif