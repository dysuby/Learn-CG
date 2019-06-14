#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shader/Shader.h"

#include "../utils/utils.h"

struct Particle {
	glm::vec3 Position;
	glm::vec3 Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec4 Color = glm::vec4(0.54f, 0.11f, 0.11f, 1.0f);
	GLfloat Life;
	GLfloat gravityEffect;
	GLfloat rotation;
	GLfloat scale = 0.1f;
	GLfloat elapsedTime = 0;
};


class ParticleGenerator {
public:
	// Constructor
	ParticleGenerator(int amount);
	// Update all particles
	//void Update(GLfloat dt, GLuint newParticles, glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f));
	void Update(float dt, int newParticles);
	// Render all particles
	void Draw(float& deltaTime, Shader shader, glm::vec3 position);
private:
	// State
	std::vector<Particle> particles;
	GLuint amount;
	// Render state
	GLuint VAO;
	// Initializes buffer and vertex attributes
	void init();
	// Returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
	GLuint firstUnusedParticle();
	// Respawns particle
	void respawnParticle(Particle &particle);
};







#endif