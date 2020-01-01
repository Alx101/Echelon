#ifndef _XML_PARSER_H_
#define _XML_PARSER_H_

#include "common_header.h"
#include <rapidxml_print.hpp>
#include "E_XMLDoc.h"
#include "E_FileMgr.h"

namespace EEngine
{
class XMLParser
{
	public:
		XMLParser();
		~XMLParser();

		static XMLDoc* addDocument(string docName);
		static XMLDoc* getDoc(string docName);
		static void printFile(string docName);

	private:
		static map<string, XMLDoc*> docList;
		static map<string, XMLDoc*>::iterator it;
		
};
}

#endif