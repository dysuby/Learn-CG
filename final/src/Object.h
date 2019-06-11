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
	Object(vector<float> _vertices, Shader *_shader);

	~Object();

	// 单个cube渲染
	void Render(int vertices_num);

	// 多个cube渲染
	void Render(vector<glm::vec3> positions);


private:
	unsigned int VAO, VBO;
	vector<float> vertices;
	Shader *shader;
};

#endif // !CUBE_H
