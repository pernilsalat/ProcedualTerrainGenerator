#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <functional>
#include <vector>
#include <map>
#include <constants.h>
#include "src/Camera/Camera.h"
using namespace std;
using namespace constants::inputTypes;

class KeyInput
{
public:
	// Takes a list of which keys to keep state for
	KeyInput(map<int, function<void(map<int, bool>*)>> keysToMonitor, InputType type);
	KeyInput(map<int, function<void(double, double)>> keysToMonitor, InputType type);
	KeyInput(map<int, function<void(double)>> keysToMonitor, InputType type);
	~KeyInput();

	// If this KeyInput is enabled and the given key is monitored,
	// returns pressed state.  Else returns false.
	bool getIsKeyDown(int key);

	bool getIsEnable() { return _isEnabled; }
	void setIsEnabled(int value) { _isEnabled = value; }

private:
	bool _isEnabled;
	int _position;
	InputType type;
	// Map from monitored keyes to their pressed states
	map<int, bool> _keys;
	// Map from monitored keyes to their respective actions
	map<int, function<void(map<int, bool>*)>> _keyActions;
	map<int, function<void(double, double)>> _dragActions;
	map<int, function<void(double)>> _scrollActions;

	// Used internally to update key states.  Called by the GLFW callback.
	void setIsKeyDown(int key, bool isDown);
	void setNewPosition(double xoffset, double yoffset);
	void setNewScroll(double yoffset);

public:
	// Must be called before any KeyInput instances will work
	virtual void setupKeyInputs(GLFWwindow* window) = 0;

protected:
	// The GLFW callback for key events.  Sends events to all KeyInput instances
	static void callbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void callbackMouseButtons(GLFWwindow* window, int button, int action, int mods);
	static void callbackMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
	static void callbackMousePosition(GLFWwindow* window, double xpos, double ypos);

private:
	// Keep a list of all KeyInput instances and notify them all of key events
	static map<InputType, vector<KeyInput*>> _instances;
};

