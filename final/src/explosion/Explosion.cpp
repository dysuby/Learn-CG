#include "explosion.h"

Explosion::Explosion(Shader shader)
    : shader(shader) {
    init();
    reset();
}


void Explosion::reset() {
    for (int j = 0; j < 1000; j++) {
        this->particles.push_back(ExplosionParticle());

        particles[j].Position = glm::vec3(getRand(), getRand(), getRand());
        particles[j].Color = glm::vec4(1.0f, 0.2f, 0.0f, 1.0f);
        particles[j].Life = 1.0f;
        particles[j].Velocity = glm::vec3(getRand() * 100, getRand() * 100, getRand() * 100);
    }
}

void Explosion::Update(float dt, unsigned int newExplosions) {
    // Update all explosions
    for (auto &explosion: particles) {
        explosion.Life -= dt; // reduce life
        if (explosion.Life > 0.0f) {
            // explosion is alive, thus update
            explosion.Position += explosion.Velocity * dt;
            explosion.Color = glm::vec4(1.0f, 0.2f, 0.0f, 1.0f) * explosion.Life;
        }
    }
}

// Render all explosions
void Explosion::Draw(glm::vec3 position) {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    this->shader.use();

    for (ExplosionParticle &p : this->particles) {
        if (p.Life > 0.0f) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, position);
            model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

            this->shader.setMat4("model", model);
            this->shader.setVec4("color", p.Color);
            this->shader.setVec3("offset", p.Position);
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        }
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Explosion::init() {
    // Set up mesh and attribute properties
    unsigned int VBO;
    float explosion_quad[] = {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(explosion_quad), explosion_quad, GL_STATIC_DRAW);
    // Set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);

}

float Explosion::getRand() {
    return ((rand() % 100) - 50) / 50.0f;
}