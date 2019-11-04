#include <glad\glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Shader.h"
using namespace std;

Shader::Shader(const char* vertShaderPath, const char* fragShaderPath)
{
	// Compile default shader program.
	GLint vertexShader = loadAndComplileShaderFromFile(vertShaderPath, GL_VERTEX_SHADER);
	GLint fragmentShader = loadAndComplileShaderFromFile(fragShaderPath, GL_FRAGMENT_SHADER);

	if (!isShaderCompiled(vertexShader) || !isShaderCompiled(fragmentShader)) {
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		mError = true;
		return;
	}
	// Assemble shader program.
	mProgram = glCreateProgram();
	glAttachShader(mProgram, vertexShader);
	glAttachShader(mProgram, fragmentShader);

	// Link the program.
	glLinkProgram(mProgram);

	// If linking failed, clean up and return error.
	if (!isProgramLinked(mProgram)) {
		glDeleteProgram(mProgram);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		mError = true;
		return;
	}
	// Detach shaders after a successful link.
	glDetachShader(mProgram, vertexShader);
	glDetachShader(mProgram, fragmentShader);
}

Shader::~Shader()
{
	if (mProgram != GL_NONE) {
		glDeleteProgram(mProgram);
	}

}

bool Shader::isGood()
{
	return !mError;
}

void Shader::activate()
{
	glUseProgram(mProgram);
}

void Shader::setMat4(const char* name, glm::mat4 &mat)
{
	glUniformMatrix4fv(glGetUniformLocation(mProgram, name), 1, GL_FALSE, &mat[0][0]);
}

GLuint Shader::loadAndComplileShaderFromFile(const char* path, GLuint shaderType)
{
	ifstream file(path);
	if (!file.good()) {
		cout << "Couldn't open shader file for loading: " << path << endl;
		return GL_NONE;
	}
	// Read the file contents into a char buffer.
	stringstream buffer;
	buffer << file.rdbuf();
	string fileContentStr = buffer.str();
	const char* fileContents = fileContentStr.c_str();

	// Create shader, load file contents into it, and compile it.
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &fileContents, nullptr);
	glCompileShader(shader);
	
	return shader;
}

bool Shader::isShaderCompiled(GLuint shader)
{
	// Ask GL whether compile succeeded for this shader.
	GLint compiledSucceded = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiledSucceded);

	if (compiledSucceded == GL_FALSE) {
		GLint errorLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLength);
		
		GLchar* errorLog = new GLchar[errorLength];
		glGetShaderInfoLog(shader, errorLength, &errorLength, errorLog);

		cout << "Error compiling shader: " << errorLog << endl;
		delete[] errorLog;
	}

	return compiledSucceded != GL_FALSE;
}

bool Shader::isProgramLinked(GLuint program)
{
	// Ask GL whether link succeeded for this program.
	GLint linkSucceeded = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &linkSucceeded);

	// If not, we'll output the error log and fail.
	if (linkSucceeded == GL_FALSE) {
		GLint errorLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &errorLength);

		GLchar* errorLog = new GLchar[errorLength];
		glGetProgramInfoLog(program, errorLength, &errorLength, errorLog);

		cout << "Error linking shader program: " << errorLog << endl;
		delete[] errorLog;
	}

	return linkSucceeded != GL_FALSE;
}
