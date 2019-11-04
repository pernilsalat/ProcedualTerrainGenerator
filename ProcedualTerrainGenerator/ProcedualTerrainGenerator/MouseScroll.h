#pragma once
#include "KeyInput.h"


class MouseScroll : public KeyInput {
public:
	using KeyInput::KeyInput;

	MouseScroll(map<int, function<void(double)>> keysToMonitor)
		: KeyInput(keysToMonitor, constants::inputTypes::InputType::MOUSE_SCROLL) {};

	void setupKeyInputs(GLFWwindow* window) override {
		glfwSetScrollCallback(window, KeyInput::callbackMouseScroll);
	}
};