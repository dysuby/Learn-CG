#include "Player.h"

Player *Player::m_player = nullptr;

Player::Player(const char *model_path): Model(model_path) { }

Player *Player::getInstance(const char *model_path) {
    if (m_player == nullptr)
        m_player = new Player(model_path);
    
    return m_player;
}

void Player::DestroyInstance() {
    if (m_player)
        delete m_player;
}
