#include <glad\glad.h>
#include <iostream>
#include "Renderer.h"
//#include <constants.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

GLfloat triangle_vertices[] = {
	0.0f,  0.5f,  0.0f,
	0.5f, -0.5f,  0.0f,
	-0.5f, -0.5f,  0.0f
};


bool Renderer::initialize()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	HEIGHT = mode->height;
	WIDTH = mode->width;
	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize OpenGL context" << endl;
		return false;
	}
	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	mCamera = new Camera(glm::vec3(0, 0, 3));

	// Load shader.
	mShader = new Shader(constants::VERT_SHADER_PATH, constants::FRAG_SHADER_PATH);
	if (mShader->isGood()) {
		// Create vertex array from triangle vertices.
		mTriangles = new VertexArray(triangle_vertices, 9);
	}
	return mShader->isGood();
}

void Renderer::shutDown()
{
	glfwTerminate();
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render()
{
	mShader->activate();

	// pass projection matrix to shader (note that in this case it could change every frame)
	mat4 projection = perspective(radians(mCamera->fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	mShader->setMat4("projection", projection);

	// camera/view transformation
	mat4 view = mCamera->getViewMatrix();
	mShader->setMat4("view", view);

	mTriangles->draw();
}

void Renderer::present()
{
	glfwSwapBuffers(window);
}

GLFWwindow* Renderer::getWindow()
{
	return window;
}

Camera* Renderer::getCamera()
{
	return mCamera;
}
