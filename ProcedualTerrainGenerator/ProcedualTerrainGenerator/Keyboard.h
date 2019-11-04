#pragma once
#include "KeyInput.h"


class Keyboard : public KeyInput {
public:
	using KeyInput::KeyInput;
	Keyboard(map<int, function<void(map<int, bool>*)>> keysToMonitor)
		: KeyInput(keysToMonitor, constants::inputTypes::InputType::KEYBOARD) {};

	void setupKeyInputs(GLFWwindow* window) override {
		glfwSetKeyCallback(window, callbackKeyboard);
	 }
};