#ifndef BOUND_H
#define BOUND_H


#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::vector;

// world space positions of bound cubes
vector<glm::vec3> boundPositions{
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

vector<float> SkyboxVertices{
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};
#endif // !BOUND_H
