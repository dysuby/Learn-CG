#include "particle.h"

ParticleGenerator::ParticleGenerator(int _amount) : amount(_amount) {
	this->init();
}

void ParticleGenerator::Update(float dt, int newParticles) {
	// Add new particles 
	for (int i = 0; i < newParticles; ++i) {
		int unusedParticle = this->firstUnusedParticle();
		this->respawnParticle(this->particles[unusedParticle]);
	}
	// Update all particles
	for (int i = 0; i < this->amount; ++i) {
		Particle &p = this->particles[i];
		p.Life -= dt; // reduce life
		if (p.Life > 0.0f) {	
			// particle is alive, thus update
			p.Position -= p.Velocity * dt;
			p.Color.a -= dt * 0.8;
		}
	}
}

// Render all particles
void ParticleGenerator::Draw(float& deltaTime, Shader shader, glm::vec3 position) {
	// Use additive blending to give it a 'glow' effect
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (Particle particle : this->particles) {
		if (particle.Life > 0.0f) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, position);
			model = glm::scale(model, glm::vec3(particle.scale, particle.scale, particle.scale));
			shader.setMat4("model", model);
			shader.setVec4("color", particle.Color);
			shader.setVec3("offset", particle.Position);
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}
	}
	// Don't forget to reset to default blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::init() {
	// Set up mesh and attribute properties
	unsigned int VBO;
	float particle_quad[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);
	// Fill mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_DYNAMIC_DRAW);
	// Set mesh attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);

	// Create this->amount default particle instances
	for (GLuint i = 0; i < this->amount; ++i) {
		this->particles.push_back(Particle());
	}
}

// Stores the index of the last particle used (for quick access to next dead particle)
GLuint lastUsedParticle = 0;
GLuint ParticleGenerator::firstUnusedParticle() {
	// First search from last used particle, this will usually return almost instantly
	for (GLuint i = lastUsedParticle; i < this->amount; ++i) {
		if (this->particles[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// Otherwise, do a linear search
	for (GLuint i = 0; i < lastUsedParticle; ++i) {
		if (this->particles[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
	lastUsedParticle = 0;
	return 0;
}

GLfloat getRand() {
	return ((rand() % 100) - 50) / 50.0f;
}

void ParticleGenerator::respawnParticle(Particle &particle) {

	GLfloat rColor = 0.8 + ((rand() % 100) / 100.0f);

	particle.Position = glm::vec3(0.0f) + glm::vec3(getRand() * 10, getRand() * 3, getRand() * 10);
	GLfloat disFromOrigin = pow(particle.Position.x, 2) + pow(particle.Position.z, 2);
	particle.Color = glm::vec4(rColor - 0.01 * disFromOrigin, getRand() / 5, 0.0f, 1.0f);
	particle.Life = 3.0f - 0.1 * disFromOrigin;
	particle.Velocity = glm::vec3(0.0f, -5.0f + abs(0.1 * disFromOrigin), 0.0f);
}