#ifndef _E_FX_PROFILE_
#define _E_FX_PROFILE_

#include "common_header.h"

namespace EEngine
{
class FXprofile
{
	public:
		FXprofile();
		~FXprofile();

		bool addFX(string name, FX_DataStruct fds);
		bool toggleFX(string fxName, bool opt); //Toggle wether an FX should be enabled or disabled
		template<typename T>
		void setAttributeData(string fxName, string attribName, T& data, char type) //For single values
		{
			if(fxMap.count(fxName) && fxMap[fxName].idName.count(attribName) && fxMap[fxName].)
			{
				
				dataTypeMap[attribName] = type; //Assigns the data to be used when rendering
				switch(type)
				{
					case 'f':
						dataF[attribName] = data;
						break;
					case 'i':
						dataI[attribName] = data;
						break;
					case 'd':
						dataD[attribName] = data;
						break;
					case 'u':
						dataUI[attribName] = data;
						break;
					case 'b':
						dataB[attribName] = data;
						break;
					default:
						dataF[attribName] = data;
						break;
				}
			}
		}
		template<typename T>
		void setAttributeData(string fxName, string attribName, T* data, char type) //For arrays
		{
			if(fxMap.count(fxName) && fxMap[fxName].idName.count(attribName) && fxMap[fxName].)
			{
				
				dataTypeMap[attribName] = type; //Assigns the data to be used when rendering
				switch(type)
				{
					case 'f':
						dataFA[attribName] = data;
						break;
					case 'i':
						dataIA[attribName] = data;
						break;
					case 'd':
						dataDA[attribName] = data;
						break;
					case 'u':
						dataUIA[attribName] = data;
						break;
					case 'b':
						dataBA[attribName] = data;
						break;
					default:
						dataFA[attribName] = data;
						break;
				}
			}
		}
		void prepShaders();

	private:
		map<string, FX_DataStruct> fxMap;
		map<string, FX_DataStruct>::iterator mIt;

		map<string, char> dataTypeMap;

		map<string, GLbyte> dataB;
		map<string, GLint> dataI;
		map<string, GLfloat> dataF;
		map<string, GLdouble> dataD;
		map<string, GLuint> dataUI;

		map<string, GLbyte*> dataBA;
		map<string, GLint*> dataIA;
		map<string, GLfloat*> dataFA;
		map<string, GLdouble*> dataDA;
		map<string, GLuint*> dataUIA;

		map<string, bool> fxActiveMap;
		map<string, bool>::iterator aIt;

};
}

#endif