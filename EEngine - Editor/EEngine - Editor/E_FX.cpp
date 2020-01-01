#include "E_FX.h"
using namespace EEngine;

FX::FX(std::string name, char* source)
{
	data.activationID = "";
	data.dataID.clear();
	data.dataType.clear();
	data.uniforms.clear();
	foundVertGlobal = false;
	foundFragGlobal = false;
	foundGeomGlobal = false;
	foundVertBody = false;
	foundFragBody = false;
	foundGeomBody = false;
	foundVertFunc = false;
	foundFragFunc = false;
	foundGeomFunc = false;
	foundID = false;
	fxSource = new stringstream();
	fxName = name;
	*fxSource << source;
	fxVertGlobal = NULL;
	fxFragGlobal = NULL;
	fxGeomGlobal = NULL;
	fxVertBody = NULL;
	fxFragBody = NULL;
	fxGeomBody = NULL;
	fxVertFunctions = NULL;
	fxFragFunctions = NULL;
	fxGeomFunctions = NULL;
	fxID = NULL;
	
	fxGlobalVertId = "ECHOES_GLOBAL_FX_VERT_DEFINE";
	fxGlobalFragId = "ECHOES_GLOBAL_FX_FRAG_DEFINE";
	fxGlobalGeomId = "ECHOES_GLOBAL_FX_GEOM_DEFINE";
	fxBodyVertId = "ECHOES_BODY_FX_VERT_DEFINE";
	fxBodyFragId = "ECHOES_BODY_FX_FRAG_DEFINE";
	fxBodyGeomId = "ECHOES_BODY_FX_GEOM_DEFINE";
	fxFuncVertId = "ECHOES_FUNC_FX_VERT_DEFINE";
	fxFuncFragId = "ECHOES_FUNC_FX_FRAG_DEFINE";
	fxFuncGeomId = "ECHOES_FUNC_FX_GEOM_DEFINE";
	fxIdentId = "ECHOES_FX_ID_DEFINE";
}

FX::FX()
{
	data.activationID = "";
	data.dataID.clear();
	data.dataType.clear();
	data.uniforms.clear();
	foundVertGlobal = false;
	foundFragGlobal = false;
	foundGeomGlobal = false;
	foundVertBody = false;
	foundFragBody = false;
	foundGeomBody = false;
	foundVertFunc = false;
	foundFragFunc = false;
	foundGeomFunc = false;
	foundID = false;

	fxSource = new stringstream();
	fxName = "";
	fxSource->clear();
	fxVertGlobal = NULL;
	fxFragGlobal = NULL;
	fxGeomGlobal = NULL;
	fxVertBody = NULL;
	fxFragBody = NULL;
	fxGeomBody = NULL;
	fxVertFunctions = NULL;
	fxFragFunctions = NULL;
	fxGeomFunctions = NULL;
	fxID = NULL;

	fxGlobalVertId = "ECHOES_GLOBAL_FX_VERT_DEFINE";
	fxGlobalFragId = "ECHOES_GLOBAL_FX_FRAG_DEFINE";
	fxGlobalGeomId = "ECHOES_GLOBAL_FX_GEOM_DEFINE";
	fxBodyVertId = "ECHOES_BODY_FX_VERT_DEFINE";
	fxBodyFragId = "ECHOES_BODY_FX_FRAG_DEFINE";
	fxBodyGeomId = "ECHOES_BODY_FX_GEOM_DEFINE";
	fxFuncVertId = "ECHOES_FUNC_FX_VERT_DEFINE";
	fxFuncFragId = "ECHOES_FUNC_FX_FRAG_DEFINE";
	fxFuncGeomId = "ECHOES_FUNC_FX_GEOM_DEFINE";
	fxIdentId = "ECHOES_FX_ID_DEFINE";
}

FX::~FX()
{
	data.activationID = "";
	data.dataID.clear();
	data.dataType.clear();
	data.uniforms.clear();
	if(fxSource) delete fxSource;
	if(fxVertGlobal) delete fxVertGlobal;
	if(fxFragGlobal) delete fxFragGlobal;
	if(fxGeomGlobal) delete fxGeomGlobal;
	if(fxVertBody) delete fxVertBody;
	if(fxFragBody) delete fxFragBody;
	if(fxGeomBody) delete fxGeomBody;
	if(fxVertFunctions) delete fxVertFunctions;
	if(fxFragFunctions) delete fxFragFunctions;
	if(fxGeomFunctions) delete fxGeomFunctions;
}

void FX::setName(std::string name)
{
	fxName = name;
}

void FX::setSource(char* source)
{
	fxSource->clear();
	*fxSource << source;
}

bool FX::trimSource()
{
	bool foundGlobal = false;
	bool foundBody = false;
	bool foundFunc = false;
	bool foundAll = false;
	if(fxSource->bad())
		return false;
	fxSource->seekg(0, ios::beg);
	fxSource->seekg(0, ios::end);
	fxVertLen = fxSource->tellg();
	if(fxVertLen < 0)
		return false;
	fxVertGlobal = new char[fxVertLen];
	fxVertBody = new char[fxVertLen];
	fxVertFunctions = new char[fxVertLen];
	char* gId = new char[fxVertLen];
	fxID = new char[fxVertLen];
	fxSource->seekg(0, ios::beg);
	fxSource->clear();
	char* dataNr = new char[fxVertLen];
	char* dataName = new char[fxVertLen];
	char* dataType = new char[fxVertLen];
	char* isUniform = new char[fxVertLen];
	char* dataForm = new char[fxVertLen];
	char* isVec = new char[fxVertLen];
	bool foundId = false;
	string dataID = "ECHOES_FX_DATA_DEFINE";

	while(!foundAll)
	{
		fxSource->getline(gId, fxVertLen, '¤');
		if(gId == fxGlobalVertId && !foundGlobal)
		{
			foundGlobal = true;
			fxSource->getline(fxVertGlobal, fxVertLen, '¤');
			foundVertGlobal = true;
		}
		else if(gId == fxBodyVertId && !foundBody)
		{
			foundBody = true;
			fxSource->getline(fxVertBody, fxVertLen, '¤');
			foundVertBody = true;
		}
		else if(gId == fxFuncVertId && !foundFunc)
		{
			foundFunc = true;
			fxSource->getline(fxVertFunctions, fxVertLen, '¤');
			foundVertFunc = true;
		}
		else if(gId == fxIdentId)
		{
			foundID = true;
			fxSource->getline(fxID, fxVertLen, '¤');
		}
		else if(gId == dataID)
		{
			while(!foundId)
			{
				fxSource->getline(dataNr, fxVertLen, '¤');
				if(dataNr == dataID)
				{
					foundId = true;
					break;
				}
				fxSource->getline(dataName, fxVertLen, '¤');
				if(dataName == dataID)
				{
					foundId = true;
					break;
				}
				fxSource->getline(dataType, fxVertLen, '¤');
				if(dataType == dataID)
				{
					foundId = true;
					break;
				}
				fxSource->getline(isUniform, fxVertLen, '¤');
				if(isUniform == dataID)
				{
					foundId = true;
					break;
				}
				if(atoi(dataType) != POSITION && (atoi(dataType) > 16 || atoi(dataType) <= 4))
				{
					fxSource->getline(dataForm, fxVertLen, '¤');
					if(dataForm == dataID)
					{
						foundId = true;
						break;
					}
					data.dataForm.assign(atoi(dataNr), dataForm);
				}
				if(atoi(dataType) != POSITION && (atoi(dataType) > 18 && atoi(dataType) <= 1))
				{
					fxSource->getline(isVec, fxVertLen, '¤');
					if(isVec == dataID)
					{
						foundId = true;
						break;
					}
				}
				else
				{
					isVec = "0";
				}
				data.dataID.assign(atoi(dataNr), dataName);
				data.idName[dataName] = atoi(dataNr);
				data.dataType.assign(atoi(dataNr), atoi(dataType));
				data.uniforms.assign(atoi(dataNr), atoi(isUniform));
				data.vectors.assign(atoi(dataNr), atoi(isVec));
			}

		}
		else if(gId == "ECHOES_FX_ACTIVATION_DEFINE")
		{
			fxSource->getline(dataName, fxVertLen, '¤');
			data.activationID = dataName;
		}
		else if(fxSource->eof())
				foundAll = true;
	}

	delete gId;

	foundGlobal = false;
	foundBody = false;
	foundFunc = false;
	foundAll = false;
	if(fxSource->bad())
		return false;
	fxSource->seekg(0, ios::beg);
	fxSource->seekg(0, ios::end);
	fxFragLen = fxSource->tellg();
	if(fxFragLen < 0)
		return false;
	fxFragGlobal = new char[fxFragLen];
	fxFragBody = new char[fxFragLen];
	fxFragFunctions = new char[fxFragLen];
	gId = new char[fxFragLen];
	fxSource->seekg(0, ios::beg);
	fxSource->clear();
	while(!foundAll)
	{
		fxSource->getline(gId, fxFragLen, '¤');
		if(gId == fxGlobalFragId && !foundGlobal)
		{
			foundGlobal = true;
			fxSource->getline(fxFragGlobal, fxFragLen, '¤');
			foundFragGlobal = true;
		}
		else if(gId == fxBodyFragId && !foundBody)
		{
			foundBody = true;
			fxSource->getline(fxFragBody, fxFragLen, '¤');
			foundFragBody = true;
		}
		else if(gId == fxFuncFragId && !foundFunc)
		{
			foundFunc = true;
			fxSource->getline(fxFragFunctions, fxFragLen, '¤');
			foundFragFunc = true;
		}
		else if(fxSource->eof())
				foundAll = true;
	}

	delete gId;

	foundGlobal = false;
	foundBody = false;
	foundFunc = false;
	foundAll = false;
	if(fxSource->bad())
		return false;
	fxSource->seekg(0, ios::beg);
	fxSource->seekg(0, ios::end);
	fxGeomLen = fxSource->tellg();
	if(fxGeomLen < 0)
		return false;
	fxGeomGlobal = new char[fxGeomLen];
	fxGeomBody = new char[fxGeomLen];
	fxGeomFunctions = new char[fxGeomLen];
	gId = new char[fxGeomLen];
	fxSource->seekg(0, ios::beg);
	fxSource->clear();
	while(!foundAll)
	{
		fxSource->getline(gId, fxGeomLen, '¤');
		if(gId == fxGlobalGeomId && !foundGlobal)
		{
			foundGlobal = true;
			fxSource->getline(fxGeomGlobal, fxGeomLen, '¤');
			foundGeomGlobal = true;
		}
		else if(gId == fxBodyGeomId && !foundBody)
		{
			foundBody = true;
			fxSource->getline(fxGeomBody, fxGeomLen, '¤');
			foundGeomBody = true;
		}
		else if(gId == fxFuncGeomId && !foundFunc)
		{
			foundFunc = true;
			fxSource->getline(fxGeomFunctions, fxGeomLen, '¤');
			foundGeomFunc = true;
		}
		else if(fxSource->eof())
				foundAll = true;
	}

	delete gId;
	return true;
}

string FX::getName()
{
	return fxName;
}

char* FX::getGlobal(int shaderType)
{
	switch(shaderType)
	{
		case VERTEX_SHADER:
			return fxVertGlobal;
		case FRAGMENT_SHADER:
			return fxFragGlobal;
		case GEOMETRY_SHADER:
			return fxGeomGlobal;
		default:
			return NULL;
			break;
	}
	return NULL;
}

char* FX::getBody(int shaderType)
{
	switch(shaderType)
	{
		case VERTEX_SHADER:
			return fxVertBody;
		case FRAGMENT_SHADER:
			return fxFragBody;
		case GEOMETRY_SHADER:
			return fxGeomBody;
		default:
			return NULL;
			break;
	}
	return NULL;
}

char* FX::getFunctions(int shaderType)
{
	switch(shaderType)
	{
		case VERTEX_SHADER:
			return fxVertFunctions;
		case FRAGMENT_SHADER:
			return fxFragFunctions;
		case GEOMETRY_SHADER:
			return fxGeomFunctions;
		default:
			return NULL;
			break;
	}
	return NULL;
}

char* FX::getID()
{
	return fxID;
}

FX_DataStruct* FX::getData()
{
	return &data;
}