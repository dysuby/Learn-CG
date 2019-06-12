#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shader/Shader.h"

using namespace std;

class Object {
public:
	Object(vector<float> _vertices, vector<unsigned int> _textures);

	~Object();

	// ‰÷»æ
	void Render(vector<glm::vec3> positions, Shader *shader, bool renderShadow = true);


private:
	unsigned int VAO, VBO;
    vector<unsigned int> textures;
	size_t vertices_num;
};

#endif // !CUBE_H
