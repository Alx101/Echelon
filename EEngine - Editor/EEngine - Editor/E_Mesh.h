#ifndef _MESH_H_
#define _MESH_H_

#include "common_header.h"

namespace EEngine
{
class Mesh
{
	public:
		Mesh();
		~Mesh();

		GLuint getVBO(int eVboType);
		void setVBO(GLuint eVBO, int eVboType);
		GLuint getVAO();
		void setVAO(GLuint VAO);

		enum vboType
		{
			VERTEX_VBO,
			COLOR_VBO,
			INDEX_VBO
		};
		//public variables
	private:
		GLuint vao;
		GLuint vboVertices;
		GLuint vboColors;
		GLuint vboIndices;

};
}

#endif