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
	//Object(vector<float> _vertices, vector<unsigned int> _textures);
	Object(vector<float> _vertices, vector<unsigned int> _textures, glm::vec3 _position, unsigned int _VAO = 0, unsigned int _VBO = 0);
	Object();
	/*~Object();*/

	// ‰÷»æ
	//void Render(vector<glm::vec3> positions, Shader *shader, bool renderShadow = true);
	void Render(Shader *shader, bool renderShadow = true);

	glm::vec3 position;

private:
	unsigned int VAO, VBO;
    vector<unsigned int> textures;
	size_t vertices_num;
};

vector<Object> createObjects(vector<float> _vertices, vector<unsigned int> _textures, vector<glm::vec3> _positions);

void renderObjects(vector<Object> _objects, Shader *_shader, bool renderShadow = true);

void setBuffer(vector<float> _vertices, unsigned int _VAO, unsigned int _VBO);

#endif // !OBJECT_H
