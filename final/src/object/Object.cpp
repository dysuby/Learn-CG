#include "Object.h"

//Object::Object(vector<float> _vertices, vector<unsigned int> _textures): textures(_textures) {
//    vertices_num = _vertices.size();
//
//    // 生成
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	// 绑定 VAO, VBO
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, vertices_num * sizeof(float), _vertices.data(), GL_STREAM_DRAW);
//	// 位置属性
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	// 法线属性
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	// 纹理属性
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//}

//Object::~Object() {
//	// 解除绑定
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//}

//// 渲染
//void Object::Render(vector<glm::vec3> positions, Shader *shader, bool renderShadow) {
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, textures[0]);  // 纹理
//
//    if (renderShadow) {
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, textures[1]);  // 阴影
//    }
//
//	// 渲染多个立方体
//	glBindVertexArray(VAO);
//    
//	for (int i = 0; i < positions.size(); i++) {
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, positions[i]);
//        shader->setMat4("model", model);
//
//		glDrawArrays(GL_TRIANGLES, 0, vertices_num);
//	}
//	glBindVertexArray(0);
//}

Object::Object(vector<float> _vertices, vector<unsigned int> _textures, glm::vec3 _position, unsigned int _VAO, unsigned int _VBO): position(_position), textures(_textures){
	vertices_num = _vertices.size();
	if (_VAO == 0 && _VBO == 0) {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		setBuffer(_vertices, VAO, VBO);
	}
	else {
		VAO = _VAO;
		VBO = _VBO;
	}
}

Object::Object(){}

void Object::Render(Shader *_shader, bool renderShadow) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);  // 纹理

	if (renderShadow) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);  // 阴影
	}

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	_shader->setMat4("model", model);

	// 渲染立方体
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices_num);
	glBindVertexArray(0);
}

vector<Object> createObjects(vector<float> _vertices, vector<unsigned int> _textures, vector<glm::vec3> positions) {
	vector<Object> objects;
	// generate VAO, VBO
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	setBuffer(_vertices, VAO, VBO);
	cout << VAO << endl;
	for (int i = 0; i < positions.size(); i++) {
		objects.push_back(Object(_vertices, _textures, positions[i], VAO, VBO));
	}
	return objects;
}

void renderObjects(vector<Object> _objects, Shader *_shader, bool renderShadow) {
	for (int i = 0; i < _objects.size(); i++) {
		_objects[i].Render(_shader, renderShadow);
	}
}

void setBuffer(vector<float> _vertices, unsigned int _VAO, unsigned int _VBO) {
	// 绑定 VAO, VBO
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STREAM_DRAW);
	// 位置属性
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// 法线属性
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// 纹理属性
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}