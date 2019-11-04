#pragma once
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include "../Shader/Shader.h"
#include "../DrawableObjects/VertexArray/VertexArray.h"
#include "../Camera/Camera.h"

class Renderer
{
public:
	//Renderer();
	//~Renderer();

	bool initialize();
	void shutDown();

	void clear();
	void render();
	void present();

	GLFWwindow* getWindow();
	Camera* getCamera();

private:
	GLFWwindow* window = nullptr;
	Shader* mShader = nullptr;
	VertexArray* mTriangles = nullptr;
	Camera* mCamera = nullptr;
	int HEIGHT, WIDTH;
};
