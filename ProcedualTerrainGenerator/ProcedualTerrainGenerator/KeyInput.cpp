#include "KeyInput.h"
#include <algorithm>
#include <iostream>

map<InputType, vector<KeyInput*>> KeyInput::_instances;

KeyInput::KeyInput(map<int, function<void(map<int, bool>*)>> keysToMonitor, InputType type)
	: _isEnabled(true), _keyActions(keysToMonitor), type(type)
{
	for (auto iter : keysToMonitor) {
		_keys[iter.first] = false;
	}
	_position = _instances[type].size();
	// Add this instance to the list of instances
	_instances[type].push_back(this);
}

KeyInput::KeyInput(map<int, function<void(double, double)>> keysToMonitor, InputType type)
	: _isEnabled(true), _dragActions(keysToMonitor), type(type)
{
	for (auto iter : keysToMonitor) {
		_keys[iter.first] = false;
	}
	_position = _instances[type].size();
	// Add this instance to the list of instances
	_instances[type].push_back(this);
}

KeyInput::KeyInput(map<int, function<void(double)>> keysToMonitor, InputType type)
	: _isEnabled(true), _scrollActions(keysToMonitor), type(type)
{
	for (auto iter : keysToMonitor) {
		_keys[iter.first] = false;
	}
	_position = _instances[type].size();
	// Add this instance to the list of instances
	_instances[type].push_back(this);
}

KeyInput::~KeyInput()
{
	_instances[type].erase(_instances[type].begin() + _position);
}

bool KeyInput::getIsKeyDown(int key)
{
	bool result = false;

	if (_isEnabled && _keys.contains(key)) {
		result = _keys[key];
	}
	return result;
}

//void KeyInput::setupKeyInputs(GLFWwindow* window)
//{
//	glfwSetKeyCallback(window, KeyInput::callback);
//}

void KeyInput::setIsKeyDown(int key, bool isDown)
{
	if (_keys.contains(key)) {
		_keys[key] = isDown;
		if (isDown) {
			_keyActions[key](&_keys);
		}
	}
}

void KeyInput::setNewPosition(double xoffset, double yoffset)
{
	_dragActions[constants::DRAG](xoffset, yoffset);
}

void KeyInput::setNewScroll(double yoffset)
{
	_scrollActions[constants::SCROLL](yoffset);
}

void KeyInput::callbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Send key event to all KeyInput instances
	for (KeyInput* keyInput : _instances[InputType::KEYBOARD]) {
		keyInput->setIsKeyDown(key, action != GLFW_RELEASE);
	}
}

void KeyInput::callbackMouseButtons(GLFWwindow* window, int button, int action, int mods)
{
	// Send key event to all KeyInput instances
	for (KeyInput* keyInput : _instances[InputType::MOUSE_BUTTONS]) {
		keyInput->setIsKeyDown(button, action != GLFW_RELEASE);
	}
}

void KeyInput::callbackMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	// Send key event to all KeyInput instances
	for (KeyInput* keyInput : _instances[InputType::MOUSE_BUTTONS]) {
		keyInput->setNewScroll(yoffset);
	}
}

void KeyInput::callbackMousePosition(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Send key event to all KeyInput instances
		for (KeyInput* keyInput : _instances[InputType::MOUSE_DRAG]) {
			keyInput->setNewPosition(xpos, ypos);
		}
	}
}
