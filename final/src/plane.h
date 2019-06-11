#ifndef PLANE_H
#define PLANE_H

#include <vector>

using std::vector;

vector<float> planeVertices {
	// Positions         // Normals			// Texture
	 6.0f, -0.5f,  6.0f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	-6.0f, -0.5f, -6.0f, 0.0f, 1.0f, 0.0f,  0.0f,  1.0f,
	-6.0f, -0.5f,  6.0f, 0.0f, 1.0f, 0.0f,  0.0f,  0.0f,

	 6.0f, -0.5f,  6.0f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 6.0f, -0.5f, -6.0f, 0.0f, 1.0f, 0.0f,  1.0f,  1.0f,
	-6.0f, -0.5f, -6.0f, 0.0f, 1.0f, 0.0f,  0.0f,  1.0f
};

#endif // !PLANE_H
