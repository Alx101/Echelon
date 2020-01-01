#include "E_Mesh.h"
using namespace EEngine;

Mesh::Mesh()
{
	vboVertices = NULL;
	vboColors = NULL;
	vboIndices = NULL;
}

Mesh::~Mesh()
{
}

GLuint Mesh::getVBO(int eVboType)
{
	if(eVboType == VERTEX_VBO)
		return vboVertices;
	if(eVboType == INDEX_VBO)
		return vboIndices;
	if(eVboType == COLOR_VBO)
		return vboColors;
	return NULL;
}

void Mesh::setVBO(GLuint eVBO, int eVboType)
{
	if(eVboType == VERTEX_VBO)
		vboVertices = eVBO;
	if(eVboType == INDEX_VBO)
		vboIndices = eVBO;
	if(eVboType == COLOR_VBO)
		vboColors = eVBO;	
}

GLuint Mesh::getVAO()
{
	return vao;
}

void Mesh::setVAO(GLuint VAO)
{
	vao = VAO;
}