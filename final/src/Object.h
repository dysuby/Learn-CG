#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

using namespace std;

class Object {
public:
	Object(vector<float> _vertices, Shader *_shader, unsigned int _Texture);

	~Object();

	// ‰÷»æ
	void Render(vector<glm::vec3> positions, int vertices_num);


private:
	unsigned int VAO, VBO;
	unsigned int Texture;
	Shader *shader;
};

#endif // !CUBE_H
