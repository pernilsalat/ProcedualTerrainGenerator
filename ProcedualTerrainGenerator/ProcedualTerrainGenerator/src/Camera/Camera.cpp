#include <iostream>
#include "Camera.h"
#include <glm\gtx\string_cast.hpp>

using namespace std;

Camera::Camera(vec3 position, vec3 up, GLfloat speed, GLfloat yaw, GLfloat pitch) :
	front(vec3(0, 0, -1)), movementSpeed(speed), mouseSensitivity(defaultValues::SENSITIVITY), fov(defaultValues::FOV),
	position(position),	worldUp(up), yaw(yaw), pitch(pitch)
{
	//updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
	front(vec3(0, 0, -1)), movementSpeed(defaultValues::SPEED), mouseSensitivity(defaultValues::SENSITIVITY),
	fov(defaultValues::FOV), position(vec3(posX, posY, posZ)), worldUp(vec3(upX, upY, upZ)), yaw(yaw), pitch(pitch)
{
	//updateCameraVectors();
}

mat4 Camera::getViewMatrix()
{
	return lookAt(position, position + front, worldUp);
}

mat4 Camera::getMirroredViewMatrix(float mirrorHeight)
{
	vec3 mirrorPos = vec3(position.x, -position.y + 2.0 * mirrorHeight, position.z);
	vec3 mirrorFront = vec3(front.x, -front.y, front.z);

	return lookAt(position, position + front, worldUp);
}

void Camera::setFront(vec3 newFront)
{
	front = normalize(newFront);
}

void Camera::move(vec3 distance)
{
	position += distance;
}

void Camera::processKeyboard(CameraMovement action, GLfloat deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime;
	switch (action)
	{
	case CameraMovement::FORWARD:
		position += front * velocity;
		break;
	case CameraMovement::BACKWARD:
		position -= front * velocity;
		break;
	case CameraMovement::LEFT:
		position -= right * velocity;
		break;
	case CameraMovement::RIGHT:
		position += right * velocity;
		break;
	case CameraMovement::UPWARD:
		position += worldUp * velocity;
		break;
	case CameraMovement::DOWNWARD:
		position -= worldUp * velocity;
		break;
	case CameraMovement::ROTATE_UP:
		pitch += ROTATION_INCREMENT;
		break;
	case CameraMovement::ROTATE_DOWN:
		pitch -= ROTATION_INCREMENT;
		break;
	case CameraMovement::ROTATE_LEFT:
		yaw -= ROTATION_INCREMENT;
		break;
	case CameraMovement::ROTATE_RIGHT:
		yaw += ROTATION_INCREMENT;
		break;
	default:
		cout << "action camera not valid" << endl;
		break;
	}
}

void Camera::processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
	yaw += xoffset * mouseSensitivity;
	pitch += yoffset * mouseSensitivity;

	if (constrainPitch) {
		if (pitch > MAX_PITCH)
			pitch = MAX_PITCH;
		else if (pitch < MIN_PITCH)
			pitch = MIN_PITCH;
	}
	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateCameraVectors();
}

void Camera::processMouseScroll(GLfloat yoffset)
{
	fov -= yoffset;

	if (fov < MIN_FOV)
		fov = MIN_FOV;
	else if (fov > MAX_FOV)
		fov = MAX_FOV;
}

void Camera::debug()
{
	cout << "front: " << to_string(front) << endl;
	cout << "up: " << to_string(up) << endl;
	cout << "right: " << to_string(right) << endl;
	cout << "position: " << to_string(position) << endl;
	cout << "yaw:" << yaw << endl;
	cout << "pitch:" << pitch << endl;
}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	vec3 front;
	front.x = cos(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(radians(pitch));
	this->front = normalize(front);
	//cout << "front: " << to_string(front) << endl;
	cout << "front this: " << to_string(this->front) << endl;

	// Also re-calculate the Right and Up vector
	right = normalize(cross(this->front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = normalize(cross(right, this->front));
}
