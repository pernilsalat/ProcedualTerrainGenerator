//#include <constants.h>
#include "./Engine.h"
#include "../../InputEvents.h"
#include <iostream>

using namespace std;

#define ms2seconds(ms) (ms * 0.001) 

bool Engine::initialize() {
	bool succesfullInit = mRenderer.initialize();
	if (succesfullInit) {
		const auto camera = mRenderer.getCamera();
		const auto window = mRenderer.getWindow();

		keyboard = new Keyboard(setupKeyActions(camera, &deltaTime));
		keyboard->setupKeyInputs(window);

		mousePosition = new MousePosition(setupMouseDragActions(camera));
		mousePosition->setupKeyInputs(window);

		mouseScroll = new MouseScroll(setupMouseScrollActions(camera));
		mouseScroll->setupKeyInputs(window);

	}
	return succesfullInit;
}

void Engine::shutDown()
{
	mRunning = false;
	mRenderer.shutDown();
}

void Engine::run()
{
	mRunning = true;
	static GLFWwindow* window = mRenderer.getWindow();

	while (!glfwWindowShouldClose(window)) {
		processInput();
		update();
		generateOutput();
	}
}

void Engine::processInput()
{
	// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
	glfwPollEvents();
	//glfwWaitEvents();
}

void Engine::update()
{
	double currentFrameTime = glfwGetTime();
	deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;
	//cout << "deltaTime: " << deltaTime << endl;

	if (currentFrameTime - lastSec > constants::SECOND_DURATION) {
		//cout << "Frames per second: " << frameCount << endl;
		lastSec = currentFrameTime;
		frameCount = 0;
	}
	//static double lastTicks = 0;

	//double currentTicks = glfwGetTime();

	//double deltaTime = currentTicks - lastTicks;

	//lastTicks = currentTicks;
}

void Engine::generateOutput()
{
	mRenderer.clear();
	mRenderer.render();
	mRenderer.present();
}
