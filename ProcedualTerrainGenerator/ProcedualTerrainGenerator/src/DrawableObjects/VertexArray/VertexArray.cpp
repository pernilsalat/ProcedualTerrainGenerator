#include <glad\glad.h>
#include "VertexArray.h"



VertexArray::VertexArray(const float* vertexPos, int vertexCunt)
{
	mVertexCount = vertexCunt / 3;
	
	// Generate a buffer and bind it for use.
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	// Allocate buffer of a certain size and copy vertex data into it.
	// Arguments are TARGET, SIZE, DATA, USAGE
	glBufferData(GL_ARRAY_BUFFER, vertexCunt * sizeof(float), vertexPos, GL_STATIC_DRAW);

	// Generate and bind our VAO.
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);
	// Enable vertex attribute 0 (vertex position data).
	glEnableVertexAttribArray(0);

	// Make sure VBO is bound, so the VAO knows what buffer to use in conjunction with the VAO.
	glBindBuffer(GL_ARRAY_BUFFER, mVAO);

	// Vertex attribute 0 (position data) has 3 components per vertex (x, y, z) and each is a float.
	// We don't want this data normalized (GL_FALSE), and the data is tightly packed (0).
	// There is no byte offset required (NULL).
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

VertexArray::~VertexArray()
{
	if (mVAO != GL_NONE) {
		glDeleteBuffers(1, &mVAO);
	}
	if (mVBO != GL_NONE) {
		glDeleteVertexArrays(1, &mVAO);
	}
}

void VertexArray::draw()
{
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, mVertexCount);
}
