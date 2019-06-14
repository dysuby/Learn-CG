#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../object/Object.h"
#include "../object/constants/Positions.h"
#include "../player/Player.h"

using namespace std;

class Manager
{
public:
    Manager() {}

    void init(vector<Object>* walls, vector<Object>* boxes, Player* player = NULL) {
        this->walls = walls;
        this->boxes = boxes;
        this->player = player;
		over = false;
    }

    void playerMove(Direction direction) {
        if (over) {
            return;
        }
        player->dir = direction;
        glm::vec3 nextPos = getNextPos(player->position, direction);
        int obj = ObjectInPos(nextPos);
        switch (obj) {
            case 0:
                player->position = nextPos;
                break;
            case 2: {
                // printObjectsPos(boxes);
                glm::vec3 boxNextPos = getNextPos(nextPos, direction);
                int nextObj = ObjectInPos(boxNextPos);
                if (!nextObj) {
                    moveBox(nextPos, direction);
                    player->position = nextPos;
                    updateGameState();
                }
                // printObjectsPos(boxes);
                break;
	    }
            case 1:
                break;
            default:
                break;
        }
    }

    int ObjectInPos(glm::vec3 pos) {
        for (int i = 0; i < walls->size(); ++i) {
            if (pos.x == (*walls)[i].position.x && pos.z == (*walls)[i].position.z)
                return 1;
        }
        for (int i = 0; i < boxes->size(); ++i) {
            if (pos.x == (*boxes)[i].position.x && pos.z == (*boxes)[i].position.z)
                return 2;
        }
        return 0;
    }

    glm::vec3 getNextPos(const glm::vec3 curPos, Direction direction) {
        glm::vec3 nextPos = curPos;
        switch (direction) {
        case Left:
            nextPos.x -= 1.0f;
            break;
        case Right:
            nextPos.x += 1.0f;
            break;
        case Forward:
            nextPos.z -= 1.0f;
            break;
        case Back:
            nextPos.z += 1.0f;
            break;
        default:
            break;
        }
        return nextPos;
    }

    bool moveBox(const glm::vec3 boxPos, Direction direction) {
        for (int i = 0; i < boxes->size(); ++i) {
            if (boxPos.x == (*boxes)[i].position.x && boxPos.z == (*boxes)[i].position.z) {
                (*boxes)[i].position = getNextPos((*boxes)[i].position, direction);
                return true;
            }
        }
        return false;
    }
	
    void printObjectsPos(vector<Object>* objs) {
        cout << "all boxes pos: " << endl;
        for (int i = 0; i < objs->size(); ++i)
            cout << (*objs)[i].position.x << ' ' << (*objs)[i].position.z << endl;
        cout << endl;
    }

    void updateGameState() {
        for (int i = 0; i < boxes->size(); ++i) {
            int j = 0;
            for ( ; j < endPositions.size(); ++j) {
                if ((*boxes)[i].position.x == endPositions[j].x && (*boxes)[i].position.z == endPositions[j].z) {
                    break;
                }
            }
            if (j == endPositions.size()) {
                over = false;
                return;
            }
        }
        over = true;
    }

    void resetObjsPos() {
        for (int i = 0; i < boxes->size(); ++i) {
            (*boxes)[i].position = boxPositions[i];
        }
        (*player).position = playerPosition;
		over = false;
    }

    bool isGameOver() {
        return over;
    }

private:
    vector<Object> * walls;
    vector<Object> * boxes;
    Player * player;
    Direction playerDirection;
    bool over;
};


#endif
