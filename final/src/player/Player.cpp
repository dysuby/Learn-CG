#include "Player.h"
Player *Player::m_player = nullptr;

float dir2angle[]{ 90.f, -90.0f, 180.0f, 0.0f };

Player::Player(const char *model_path, int SCR_WIDTH, int SCR_HEIGHT, unsigned int _depthMap): Model(model_path) {
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    view = glm::mat4(1.0f);
    depthMap = _depthMap;
    position = glm::vec3(-0.5f, -0.5f, 0.5f);
    dir = Forward;
}

Player *Player::getInstance(const char *model_path, int SCR_WIDTH, int SCR_HEIGHT, unsigned int depthMap) {
    if (m_player == nullptr)
        m_player = new Player(model_path, SCR_WIDTH, SCR_HEIGHT, depthMap);
    
    return m_player;
}

void Player::DestroyInstance() {
    if (m_player)
        delete m_player;
}

void Player::setView(glm::mat4 _view) {
    view = _view;
}

void Player::setProjection(glm::mat4 _projection) {
    projection = _projection;
}

void Player::render(Shader *shader, glm::vec3 lightPos, bool renderShadow) {
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setVec3("lightPos", lightPos);

    model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(dir2angle[dir]), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    shader->setMat4("model", model);
    
    this->Draw(*shader, depthMap, renderShadow);
}