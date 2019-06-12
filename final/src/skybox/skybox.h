#pragma once
#ifndef SKYBOX_H
#define SKYBOX_H
#include "../shader/Shader.h"
#include "../object/constants/Vertices.h"
#include "../stb_image.h"
#include <iostream>

class Skybox
{
public:
	Skybox(Shader *_shader) : skyboxShader(_shader) {
		skyboxVertices = SkyboxVertices;
		setBuffer();
		loadMap();
		skyboxShader->use();
		skyboxShader->setInt("skybox", 0);
	}

	void setBuffer() {
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(float), skyboxVertices.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	}

	void loadMap() {
		vector<std::string> faces
		{
			"assets/sky-right.jpg",
			"assets/sky-left.jpg",
			"assets/sky-top.jpg",
			"assets/sky-bottom.jpg",
			"assets/sky-front.jpg",
			"assets/sky-back.jpg"
		};
		cubemapTexture = loadCubemap(faces);
	}

	unsigned int loadCubemap(vector<std::string> faces)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return textureID;
	}
	// view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
	// glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	void render(glm::mat4 view, glm::mat4 projection) {
		// draw skybox as last
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		skyboxShader->use();
		
		skyboxShader->setMat4("view", view);
		skyboxShader->setMat4("projection", projection);
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default
	}

	~Skybox() {
		// ½â³ý°ó¶¨
		glDeleteVertexArrays(1, &skyboxVAO);
		glDeleteBuffers(1, &skyboxVBO);
	}

private:
	unsigned int skyboxVAO, skyboxVBO;
	unsigned int cubemapTexture;
	Shader *skyboxShader;
	vector<float> skyboxVertices;
};


#endif
