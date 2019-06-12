#pragma once

#include "../models/Model.h"

class Player: public Model {
public:

    static Player *getInstance(const char *model_path);
    static void DestroyInstance();


private:
    Player(const char *model_path);
     
    static Player *m_player;
};

