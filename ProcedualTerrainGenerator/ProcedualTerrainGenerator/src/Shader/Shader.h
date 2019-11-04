#pragma once
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader(const char* const vertShaderPath, const char* const fragShaderPath);
	~Shader();

	bool isGood();
	void activate();
	void setMat4(const char* name, glm::mat4 &mat);

private:
	// Handle to the compiled and linked GL shader program.
	GLuint mProgram = GL_NONE;

	// Did we encounter an error during compile/linking?
	bool mError = false;

	GLuint loadAndComplileShaderFromFile(const char* path, GLuint shaderType);
	bool isShaderCompiled(GLuint shader);
	bool isProgramLinked(GLuint program);
};
