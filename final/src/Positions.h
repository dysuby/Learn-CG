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

// world space positions of plane cubes
vector<glm::vec3> groundPositions{
	glm::vec3(-4.5f,  0.0f, -4.5f), 
	glm::vec3(-3.5f,  0.0f, -4.5f), 
	glm::vec3(-2.5f,  0.0f, -4.5f), 
	glm::vec3(-1.5f,  0.0f, -4.5f), 
	glm::vec3(-0.5f,  0.0f, -4.5f),
	glm::vec3(0.5f,  0.0f, -4.5f), 
	glm::vec3(1.5f,  0.0f, -4.5f), 
	glm::vec3(2.5f,  0.0f, -4.5f), 
	glm::vec3(3.5f,  0.0f, -4.5f), 
	glm::vec3(4.5f,  0.0f, -4.5f),

	glm::vec3(-4.5f,  0.0f, -3.5f), 
	glm::vec3(-3.5f,  0.0f, -3.5f),
	glm::vec3(-2.5f,  0.0f, -3.5f), 
	glm::vec3(-1.5f,  0.0f, -3.5f), 
	glm::vec3(-0.5f,  0.0f, -3.5f), 
	glm::vec3(0.5f,  0.0f, -3.5f), 
	glm::vec3(1.5f,  0.0f, -3.5f), 
	glm::vec3(2.5f,  0.0f, -3.5f), 
	glm::vec3(3.5f,  0.0f, -3.5f), 
	glm::vec3(4.5f,  0.0f, -3.5f),

	glm::vec3(-4.5f,  0.0f, -2.5f), 
	glm::vec3(-3.5f,  0.0f, -2.5f), 
	glm::vec3(-2.5f,  0.0f, -2.5f), 
	glm::vec3(-1.5f,  0.0f, -2.5f), 
	glm::vec3(-0.5f,  0.0f, -2.5f),
	glm::vec3(0.5f,  0.0f, -2.5f), 
	glm::vec3(1.5f,  0.0f, -2.5f), 
	glm::vec3(2.5f,  0.0f, -2.5f), 
	glm::vec3(3.5f,  0.0f, -2.5f), 
	glm::vec3(4.5f,  0.0f, -2.5f),

	glm::vec3(-4.5f,  0.0f, -1.5f), 
	glm::vec3(-3.5f,  0.0f, -1.5f), 
	glm::vec3(-2.5f,  0.0f, -1.5f), 
	glm::vec3(-1.5f,  0.0f, -1.5f), 
	glm::vec3(-0.5f,  0.0f, -1.5f),
	glm::vec3(0.5f,  0.0f, -1.5f), 
	glm::vec3(1.5f,  0.0f, -1.5f), 
	glm::vec3(2.5f,  0.0f, -1.5f),
	glm::vec3(3.5f,  0.0f, -1.5f), 
	glm::vec3(4.5f,  0.0f, -1.5f),

	glm::vec3(-4.5f,  0.0f, -0.5f), 
	glm::vec3(-3.5f,  0.0f, -0.5f),
	glm::vec3(-2.5f,  0.0f, -0.5f),
	glm::vec3(-1.5f,  0.0f, -0.5f),
	glm::vec3(-0.5f,  0.0f, -0.5f),
	glm::vec3(0.5f,  0.0f, -0.5f), 
	glm::vec3(1.5f,  0.0f, -0.5f), 
	glm::vec3(2.5f,  0.0f, -0.5f), 
	glm::vec3(3.5f,  0.0f, -0.5f),
	glm::vec3(4.5f,  0.0f, -0.5f),

	glm::vec3(-4.5f,  0.0f, 0.5f),
	glm::vec3(-3.5f,  0.0f, 0.5f), 
	glm::vec3(-2.5f,  0.0f, 0.5f),
	glm::vec3(-1.5f,  0.0f, 0.5f), 
	glm::vec3(-0.5f,  0.0f, 0.5f), 
	glm::vec3(0.5f,  0.0f, 0.5f), 
	glm::vec3(1.5f,  0.0f, 0.5f),
	glm::vec3(2.5f,  0.0f, 0.5f),
	glm::vec3(3.5f,  0.0f, 0.5f),
	glm::vec3(4.5f,  0.0f, 0.5f),

	glm::vec3(-4.5f,  0.0f, 1.5f),
	glm::vec3(-3.5f,  0.0f, 1.5f),
	glm::vec3(-2.5f,  0.0f, 1.5f), 
	glm::vec3(-1.5f,  0.0f, 1.5f),
	glm::vec3(-0.5f,  0.0f, 1.5f),
	glm::vec3(0.5f,  0.0f, 1.5f), 
	glm::vec3(1.5f,  0.0f, 1.5f),
	glm::vec3(2.5f,  0.0f, 1.5f),
	glm::vec3(3.5f,  0.0f, 1.5f), 
	glm::vec3(4.5f,  0.0f, 1.5f),

	glm::vec3(-4.5f,  0.0f, 2.5f),
	glm::vec3(-3.5f,  0.0f, 2.5f),
	glm::vec3(-2.5f,  0.0f, 2.5f),
	glm::vec3(-1.5f,  0.0f, 2.5f), 
	glm::vec3(-0.5f,  0.0f, 2.5f),
	glm::vec3(0.5f,  0.0f, 2.5f), 
	glm::vec3(1.5f,  0.0f, 2.5f),
	glm::vec3(2.5f,  0.0f, 2.5f), 
	glm::vec3(3.5f,  0.0f, 2.5f),
	glm::vec3(4.5f,  0.0f, 2.5f),

	glm::vec3(-4.5f,  0.0f, 3.5f),
	glm::vec3(-3.5f,  0.0f, 3.5f),
	glm::vec3(-2.5f,  0.0f, 3.5f),
	glm::vec3(-1.5f,  0.0f, 3.5f),
	glm::vec3(-0.5f,  0.0f, 3.5f),
	glm::vec3(0.5f,  0.0f, 3.5f),
	glm::vec3(1.5f,  0.0f, 3.5f), 
	glm::vec3(2.5f,  0.0f, 3.5f), 
	glm::vec3(3.5f,  0.0f, 3.5f),
	glm::vec3(4.5f,  0.0f, 3.5f),

	glm::vec3(-4.5f,  0.0f, 4.5f),
	glm::vec3(-3.5f,  0.0f, 4.5f), 
	glm::vec3(-2.5f,  0.0f, 4.5f),
	glm::vec3(-1.5f,  0.0f, 4.5f), 
	glm::vec3(-0.5f,  0.0f, 4.5f),
	glm::vec3(0.5f,  0.0f, 4.5f), 
	glm::vec3(1.5f,  0.0f, 4.5f), 
	glm::vec3(2.5f,  0.0f, 4.5f), 
	glm::vec3(3.5f,  0.0f, 4.5f), 
	glm::vec3(4.5f,  0.0f, 4.5f),
};
#endif