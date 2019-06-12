#include "Object.h"

Object::Object(vector<float> _vertices, vector<unsigned int> _textures): textures(_textures) {
    vertices_num = _vertices.size();

    // ����
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// �� VAO, VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_num * sizeof(float), _vertices.data(), GL_STREAM_DRAW);
	// λ������
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// ��������
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// ��������
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Object::~Object() {
	// �����
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

// ��Ⱦ
void Object::Render(vector<glm::vec3> positions, Shader *shader, bool renderShadow) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);  // ����

    if (renderShadow) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);  // ��Ӱ
    }

	// ��Ⱦ���������
	glBindVertexArray(VAO);
    
	for (int i = 0; i < positions.size(); i++) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, positions[i]);
        shader->setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, vertices_num);
	}
	glBindVertexArray(0);
}