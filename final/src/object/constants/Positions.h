#ifndef POSITIONS_H
#define POSITIONS_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::vector;

// world space positions of bound cubes
vector<glm::vec3> wallPositions{
	glm::vec3(-3.5f,  0.0f, -3.5f),
	glm::vec3(-2.5f,  0.0f, -3.5f),
	glm::vec3(-1.5f,  0.0f, -3.5f),
	glm::vec3(-0.5f,  0.0f, -3.5f),
	glm::vec3(0.5f,  0.0f, -3.5f),
	glm::vec3(1.5f,  0.0f, -3.5f),
	glm::vec3(2.5f,  0.0f, -3.5f),
	glm::vec3(3.5f,  0.0f, -3.5f),

	glm::vec3(-3.5f,  0.0f, -2.5f),
	glm::vec3(3.5f,  0.0f, -2.5f),

	glm::vec3(-3.5f,  0.0f, -1.5f),
	glm::vec3(1.5f,  0.0f, -1.5f),
	glm::vec3(3.5f,  0.0f, -1.5f),

	glm::vec3(-3.5f,  0.0f, -0.5f),
	glm::vec3(-1.5f,  0.0f, -0.5f),
	glm::vec3(0.5f,  0.0f, -0.5f),
	glm::vec3(3.5f,  0.0f, -0.5f),

	glm::vec3(-3.5f,  0.0f,  0.5f),
	glm::vec3(-2.5f,  0.0f,  0.5f),
	glm::vec3(-1.5f,  0.0f,  0.5f),
	glm::vec3(0.5f,  0.0f,  0.5f),
	glm::vec3(2.5f,  0.0f,  0.5f),
	glm::vec3(3.5f,  0.0f,  0.5f),

	glm::vec3(-2.5f,  0.0f,  1.5f),
	glm::vec3(2.5f,  0.0f,  1.5f),

	glm::vec3(-2.5f,  0.0f,  2.5f),
	glm::vec3(0.5f,  0.0f,  2.5f),
	glm::vec3(1.5f,  0.0f,  2.5f),
	glm::vec3(2.5f,  0.0f,  2.5f),

	glm::vec3(-2.5f,  0.0f,  3.5f),
	glm::vec3(-1.5f,  0.0f,  3.5f),
	glm::vec3(-0.5f,  0.0f,  3.5f),
	glm::vec3(0.5f,  0.0f,  3.5f)
};

vector<glm::vec3> boxPositions{
	glm::vec3(1.5f, 0.0f, -2.5f),
	glm::vec3(-1.5f, 0.0f, -1.5f),
	glm::vec3(-0.5f, 0.0f, -0.5f)
};

vector<glm::vec3> endPositions{
	glm::vec3(-2.5f,  0.005f, -2.5f),
	glm::vec3(-2.5f,  0.005f, -1.5f),
	glm::vec3(-2.5f,  0.005f, -0.5f)
};

glm::vec3 playerPosition = glm::vec3(-0.5f, -0.5f, 0.5f);
// world space positions of plane cubes
vector<glm::vec3> groundPositions;

// world space positions of dirt blocks
vector<glm::vec3> dirtPositions;
void createMap() {
	for (int z = 0; z < 10; z++) {
		for (int x = 0; x < 10; x++) {
			groundPositions.push_back(glm::vec3(float(x - 4.5), 0.0f, float(z - 4.5)));
		}
	}

	for (int y = 0; y < 5; y++) {
		for (int z = y; z < 10 - y; z++) {
			for (int x = y; x < 10 - y; x++) {
				dirtPositions.push_back(glm::vec3(float(x - 4.5), - y - 1.005, float(z - 4.5)));
			}
		}
	}
}

#endif