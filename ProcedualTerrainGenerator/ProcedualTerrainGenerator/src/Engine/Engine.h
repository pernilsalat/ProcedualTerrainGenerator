#pragma once
#include "../Rrenderer/Renderer.h"
#include "../../Keyboard.h"
#include "../../MousePosition.h"
#include "../../MouseScroll.h"

class Engine
{
public:
	//Engine();
	//~Engine();
	
	bool initialize();
	void shutDown();

	void run();

private:
	Renderer mRenderer;
	Keyboard* keyboard;
	MousePosition* mousePosition;
	MouseScroll* mouseScroll;
	bool mRunning = false;
	double deltaTime = 0.0f;		// Time between current frame and last frame
	double lastFrameTime = 0.0f;  	// Time of last frame
	double lastSec = 0.0;
	float frameCount = 0;

	map<int, function<void(map<int, bool>*)>> keyActions;

	void processInput();
	void update();
	void generateOutput();

	friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};
