#include "Object.h"

Object::Object(vector<float> _vertices, Shader *_shader) : vertices(_vertices), shader(_shader) {
	// 生成
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// 绑定 VAO, VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STREAM_DRAW);
	// 位置属性
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// 颜色属性
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// 纹理属性
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Object::~Object() {
	// 解除绑定
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

// 单个cube渲染
void Object::Render(int vertices_num) {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices_num);
	glBindVertexArray(0);
}

// 多个cube渲染
void Object::Render(vector<glm::vec3> positions) {
	// 渲染多个立方体
	glBindVertexArray(VAO);
	for (int i = 0; i < positions.size(); i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, positions[i]);
		shader->setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);
}
