#pragma once
#include <GLFW/glfw3.h>
// #include <msxml.h>


class VertexArray
{
public:
	VertexArray(const float* vertexPos, int vertexount);
	~VertexArray();

	void draw();

private:
	GLuint mVBO = GL_NONE;
	GLuint mVAO = GL_NONE;

	int mVertexCount = 0;
};

