#include <iostream>

//// GLAD
//#include <glad/glad.h>
//
//// GLFW
//#include <GLFW/glfw3.h>
//using namespace std;
//
//// Function prototypes
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//
//// Window dimensions
//GLuint WIDTH, HEIGHT;

// The MAIN function, from here we start the application and run the game loop
//int main() {
//	cout << "Starting GLFW context, OpenGL 3.3" << endl;
//	// Init GLFW
//	glfwInit();
//	// Set all the required options for GLFW
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
//
//	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
//	HEIGHT = mode->height;
//	WIDTH = mode->width;
//	// Create a GLFWwindow object that we can use for GLFW's functions
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)	{
//		cout << "Failed to create GLFW window" << endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	// Set the required callback functions
//	glfwSetKeyCallback(window, key_callback);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		cout << "Failed to initialize OpenGL context" << endl;
//		return -1;
//	}
//
//	// Define the viewport dimensions
//	glViewport(0, 0, WIDTH, HEIGHT);
//
//	// Game loop
//	while (!glfwWindowShouldClose(window)) {
//		// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
//		glfwPollEvents();
//
//		// Render
//		// Clear the colorbuffer
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// Swap the screen buffers
//		glfwSwapBuffers(window);
//	}
//
//	// Terminates GLFW, clearing any resources allocated by GLFW.
//	glfwTerminate();
//	return 0;
//}

// Is called whenever a key is pressed/released via GLFW
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
//	cout << key << endl;
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//}
#include "./src/Engine/Engine.h"

int main(int argc, char* argv[]) {
	Engine engine;

	if (engine.initialize()) {
		engine.run();
	}
	
	engine.shutDown();

	return 0;
}