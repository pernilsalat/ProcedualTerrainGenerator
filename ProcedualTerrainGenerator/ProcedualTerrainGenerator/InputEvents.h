#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <map>
#include <functional>
#include "src/Camera/Camera.h"
#include <iostream>
#include <constants.h>
using namespace std;

map<int, function<void(map<int, bool>*)>> setupKeyActions(Camera* camera, double *deltaTime) {
	//cout << *deltaTime << endl;
	return {
		{ GLFW_KEY_W, [=](map<int, bool>* keysState) -> void { camera->processKeyboard(CameraMovement::FORWARD, *deltaTime); } },
		{ GLFW_KEY_A, [=](map<int, bool>* keysState) -> void { camera->processKeyboard(CameraMovement::LEFT, *deltaTime); } },
		{ GLFW_KEY_S, [=](map<int, bool>* keysState) -> void { camera->processKeyboard(CameraMovement::BACKWARD, *deltaTime); } },
		{ GLFW_KEY_D, [=](map<int, bool>* keysState) -> void { camera->processKeyboard(CameraMovement::RIGHT, *deltaTime); } },
	};
	//return asd;
};

map<int, function<void(double, double)>> setupMouseDragActions(Camera* camera) {
	return {
		{ constants::DRAG, [=](double xpos, double ypos) -> void { camera->processMouseMovement(xpos, ypos); } },
	};
};

map<int, function<void(double)>> setupMouseScrollActions(Camera* camera) {
	return {
		{ constants::SCROLL, [=](double yoffset) -> void { camera->processMouseScroll(yoffset); } },
	};
};