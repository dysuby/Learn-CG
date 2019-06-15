#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../camera/Camera.h"
#include "../shader/Shader.h"
#include <glm\gtc\matrix_transform.hpp>
#include "explosion.h"
#include "../utils/utils.h"

struct ExplosionParticle {
    glm::vec3 Position;
    glm::vec3 Velocity = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec4 Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    float Life;
    float gravityEffect;
    float rotation;
    float scale;
    float elapsedTime = 0;
};


class Explosion
{
public:
    // Constructor
    Explosion(Shader shader);

    void reset();

    // Update all explosions
    void Update(float dt, unsigned int newExplosions);
    
    // Render all explosions
    void Draw(glm::vec3 position);
    
    float getRand();
 
private:
    // State
    std::vector<ExplosionParticle> particles;

    // Render state
    Shader shader;
    unsigned int VAO;

    // Initializes buffer and vertex attributes
    void init();
};


