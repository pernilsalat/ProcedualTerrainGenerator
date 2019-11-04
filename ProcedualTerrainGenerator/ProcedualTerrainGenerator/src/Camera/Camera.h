#pragma once
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <constants.h>

using namespace glm;
using namespace constants::camera;

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum class CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UPWARD,
	DOWNWARD,
	ROTATE_UP,
	ROTATE_DOWN,
	ROTATE_LEFT,
	ROTATE_RIGHT
};

class Camera
{
public:
	// camera attributes
	vec3 position;
	vec3 front;
	vec3 up;
	vec3 right;
	vec3 worldUp;
	// euler angles
	GLdouble yaw;
	GLdouble pitch;
	// camera options
	GLfloat movementSpeed;
	GLdouble mouseSensitivity;
	GLfloat fov;

	// constructor with vectors
	Camera(vec3 position = vec3(0, 0, 0), vec3 up = vec3(0, 1, 0), GLfloat speed = defaultValues::SPEED, GLfloat yaw = defaultValues::YAW, GLfloat pitch = defaultValues::PITCH);
	// constructor with escalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	// returns the view matrix calculated using Euler angles and lookAt matrix
	mat4 getViewMatrix();

	mat4 getMirroredViewMatrix(float mirrorHeight);

	void setFront(vec3 newFront);

	void move(vec3 distance);

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void processKeyboard(CameraMovement action, GLfloat deltaTime);

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void processMouseScroll(GLfloat yoffset);

	void debug();
private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors();
};

