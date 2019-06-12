#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Camera {
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f) : Front(glm::vec3(0.0f, 0.0f, -1.0f)) {
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)){
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix() {
		return glm::lookAt(Position, Position + Front, Up);
	}
	void moveForward(GLfloat const distance) {
		Position += Front * distance;
	}
	void moveBack(GLfloat const distance) {
		Position -= Front * distance;
	}
	void moveRight(GLfloat const distance) {
		Position += Right * distance;
	}
	void moveLeft(GLfloat const distance) {
		Position -= Right * distance;
	}
	void moveUp(GLfloat const distance) {
		Position += Up * distance;
	}
	void moveDown(GLfloat const distance) {
		Position -= Up * distance;
	}
	void rotate(GLfloat const yaw, GLfloat const pitch) {
		Yaw += yaw;
		Pitch += pitch;
		float radian_yaw = glm::radians(Yaw), radian_pitch = glm::radians(Pitch);
		updateCameraVectors();
	}
	void updateCameraVectors(){
		glm::vec3 front = glm::vec3(cos(Yaw) * cos(Pitch), sin(Pitch), sin(Yaw) * cos(Pitch));
		Front = glm::normalize(front);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}

	// 摄像机属性
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// 欧拉角度
	float Yaw;
	float Pitch;
};

#endif // !_CAMERA_H_