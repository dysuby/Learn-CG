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
        playerDirection = 'W';
    }

	void playerMove(const char direction) {
        cout << "before move, dir: " << direction << endl;
        glm::vec3 nextPos = getNextPos(player->position, direction);
        int obj = ObjectInPos(nextPos);
        cout << "objInPos: " << obj << endl;
        switch (obj) {
        case 0:
            player->position = nextPos;
            cout << "player current pos:" << player->position.x << ' ' << player->position.z << endl;
            break;
        case 2: {
            cout << "move box before: " << endl;
            // printObjectsPos(boxes);
            glm::vec3 boxNextPos = getNextPos(nextPos, direction);
            int nextObj = ObjectInPos(boxNextPos);
            cout << "boxNextPos: " << nextObj << endl;
            if (!nextObj) {
                moveBox(nextPos, direction);
                player->position = nextPos;
            }
            cout << "move box after: " << endl;
            // printObjectsPos(boxes);
            break;
        }
        case 1:
            break;
        default:
            break;
        }
    }

	int ObjectInPos(const glm::vec3 pos) {
        for (int i = 0; i < walls->size(); ++i) {
            if (pos == (*walls)[i].position)
                return 1;
        }
        for (int i = 0; i < boxes->size(); ++i) {
            if (pos == (*boxes)[i].position)
                return 2;
        }
        return 0;
    }

	glm::vec3 getNextPos(const glm::vec3 curPos, const char direction) {
        glm::vec3 nextPos = curPos;
        cout << curPos.x << ' ' << curPos.z << endl;

        switch (direction) {
        case 'A':
            nextPos.x -= 1.0f;
            break;
        case 'D':
            nextPos.x += 1.0f;
            break;
        case 'W':
            nextPos.z -= 1.0f;
            break;
        case 'S':
            nextPos.z += 1.0f;
            break;
        default:
            break;
        }
        cout << nextPos.x << ' ' << nextPos.z << endl;
        return nextPos;
    }

	bool moveBox(const glm::vec3 boxPos, const char direction) {
        for (int i = 0; i < boxes->size(); ++i) {
            if (boxPos == (*boxes)[i].position) {
                switch (direction) {
                case 'A':
                    (*boxes)[i].position.x -= 1.0f;
                    break;
                case 'D':
                    (*boxes)[i].position.x += 1.0f;
                    break;
                case 'W':
                    (*boxes)[i].position.z -= 1.0f;
                    break;
                case 'S':
                    (*boxes)[i].position.z += 1.0f;
                    break;
                default:
                    break;
                }
                return true;
            }
        }
        return false;
    }

	float playerRotate(const char direction) {
        if (playerDirection == direction) {
            return 0.0f;
        }
        else {
            float angle = 0.0f;
            switch (playerDirection)
            {
            case 'A':
                switch (direction) {
                case 'D':
                    angle = 180.0f;
                    break;
                case 'W':
                    angle = 90.0f;
                    break;
                case 'S':
                    angle = -90.0f;
                    break;
                default:
                    angle = 0.0f;
                    break;
                }
            case 'D':
                switch (direction) {
                case 'A':
                    angle = 180.0f;
                    break;
                case 'S':
                    angle = 90.0f;
                    break;
                case 'W':
                    angle = -90.0f;
                    break;
                default:
                    angle = 0.0f;
                    break;
                }
            case 'W':
                switch (direction) {
                case 'S':
                    angle = 180.0f;
                    break;
                case 'D':
                    angle = 90.0f;
                    break;
                case 'A':
                    angle = -90.0f;
                    break;
                default:
                    angle = 0.0f;
                    break;
                }
            case 'S':
                switch (direction) {
                case 'W':
                    angle = 180.0f;
                    break;
                case 'A':
                    angle = 90.0f;
                    break;
                case 'D':
                    angle = -90.0f;
                    break;
                default:
                    angle = 0.0f;
                    break;
                }
            default:
                angle = 0.0f;
                break;
            }
            playerDirection = direction;
            return angle;
        }
    }
	
    void printObjectsPos(vector<Object>* objs) {
        cout << "all boxes pos: " << endl;
        for (int i = 0; i < objs->size(); ++i)
            cout << (*objs)[i].position.x << ' ' << (*objs)[i].position.z << endl;
        cout << endl;
    }

	void resetObjsPos() {
        for (int i = 0; i < boxes->size(); ++i) {
            (*boxes)[i].position = boxPositions[i];
        }
        (*player).position = playerPosition;
    }

private:
	vector<Object> * walls;
	vector<Object> * boxes;
	Player * player;
	char playerDirection;
};


#endif