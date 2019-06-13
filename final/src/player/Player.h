#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "models/Model.h"

class Player: public Model {
public:

    static Player *getInstance(const char *model_path, int SCR_WIDTH, int SCR_HEIGHT, unsigned int depthMap);
    static void DestroyInstance();

    void render(Shader *shader, bool renderShadow = true);

    void setView(glm::mat4 _view);
    void setModel(glm::mat4 _model);
    void setProjection(glm::mat4 _projection);

    void rotate(float degree);

private:
    Player(const char *model_path, int SCR_WIDTH, int SCR_HEIGHT, unsigned int depthMap);
     
    static Player *m_player;

    glm::mat4 projection, view, model;

    unsigned int depthMap;
};

