#include "Player.h"

Player *Player::m_player = nullptr;

Player::Player(const char *model_path, int SCR_WIDTH, int SCR_HEIGHT, unsigned int _depthMap): Model(model_path) {
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    model = glm::mat4(1.0f);
    model =  glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    view = glm::mat4(1.0f);
    depthMap = _depthMap;
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

void Player::setModel(glm::mat4 _model) {
    model = _model;
}

void Player::setProjection(glm::mat4 _projection) {
    projection = _projection;
}

void Player::rotate(float degree) {
    model = glm::rotate(model, glm::radians(degree), glm::vec3(0.0f, 0.1f, 0.0f));
}

void Player::render(Shader *shader, bool renderShadow) {
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setMat4("model", model);

    //shader->setBool("useVertColor", true);
    this->Draw(*shader, depthMap, renderShadow);
}