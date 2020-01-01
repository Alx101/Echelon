#ifndef _E_ENTITY_H_
#define _E_ENTITY_H_

#include "common_header.h"

class E_Entity
{
	public:
		E_Entity();
		~E_Entity();

		virtual void setId(int ID);
		virtual int getId(); 

		virtual bool update();

		virtual this getType()
		{
			return this;
		}

	private:
		unsigned long int id;

};

#endif