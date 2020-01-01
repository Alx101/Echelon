#include "E_FXprofile.h"
using namespace EEngine;

FXprofile::FXprofile()
{
	fxMap.clear();
	fxActiveMap.clear();
}

FXprofile::~FXprofile()
{
	fxMap.clear();
	fxActiveMap.clear();
}

bool FXprofile::addFX(string name, FX_DataStruct fds)
{
	if(!fxMap.count(name))
	{
		fxMap[name] = fds; //Sets new data
		fxActiveMap[name] = true;
		return true;
	}
	else
	{
		fxMap[name] = fds; //Updates data
		return true;
	}
	return false;
}

bool FXprofile::toggleFX(string fxName, bool opt)
{
	if(fxActiveMap.count(fxName))
	{
		fxActiveMap[fxName] = opt;
		return true;
	}
	return false;
}

void FXprofile::prepShaders()
{
	for(aIt = fxActiveMap.begin(); aIt != fxActiveMap.end(); ++aIt)
	{
		if(aIt->second)
		{
			fxMap[aIt->first].idIt = fxMap[aIt->first].dataID.begin();
			fxMap[aIt->first].bIt = fxMap[aIt->first].uniforms.begin();
			for(fxMap[aIt->first].iIt = fxMap[aIt->first].dataType.begin(); fxMap[aIt->first].iIt != fxMap[aIt->first].dataType.end(); ++fxMap[aIt->first].iIt)
			{
				switch(*fxMap[aIt->first].iIt)
				{
					case POSITION:
						glVertexAttribPointer(fxMap[aIt->first].attributes[*fxMap[aIt->first].idIt], 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
						break;
					case TEXTURE1:
						break;
					case TEXTURE2:
						break;
					case TEXTURE3:
						break;
					case MATRIX4:
						break;
					case MATRIX3:
						break;
					case MATRIX2:
						break;
					case MATRIX4X2:
						break;
					case MATRIX4X3:
						break;
					case MATRIX3X2:
						break;
					case MATRIX3X4:
						break;
					case MATRIX2X3:
						break;
					case MATRIX2X4:
						break;
					case VECTOR2:
						break;
					case VECTOR3:
						break;
					case VECTOR4:
						break;
					case CUBEMAP:
						break;
					case SHADOW:
						break;
				}
				fxMap[aIt->first].idIt++;
				fxMap[aIt->first].bIt++;
			}
		}
	}
}