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
		rotate = 180.0f;
    }

	void playerMove(const char direction) {
		if (playerDirection != direction) {
			player->dir = playerRotate(direction);
		}
		else {
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

	glm::vec3 getNextPos(const glm::vec3 curPos, const char direction) {
        glm::vec3 nextPos = curPos;
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
        return nextPos;
    }

	bool moveBox(const glm::vec3 boxPos, const char direction) {
        for (int i = 0; i < boxes->size(); ++i) {
            if (boxPos.x == (*boxes)[i].position.x && boxPos.z == (*boxes)[i].position.z) {
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
			return rotate;
        }
        else {
            switch (direction){
            case 'S':
				rotate = 0.0f;
				break;
			case 'D':
				rotate = 90.0f;
				break;
			case 'W':
				rotate = 180.0f;
				break;
			case 'A':
				rotate = 270.0f;
				break;
            default:
                break;
            }
            playerDirection = direction;
            return rotate;
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
	float rotate;
};


#endif