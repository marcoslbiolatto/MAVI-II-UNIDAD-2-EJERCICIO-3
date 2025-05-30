#ifndef GAME_H
#define GAME_H

#include "Box2DHelper.h"
#include <vector>

class Game {
public:
    Game();
    void Update();
    b2Body* GetBall();
    std::vector<b2Body*> GetObstacles();

private:
    b2World* world;
    b2Body* ball;
    std::vector<b2Body*> obstacles;
};

#endif
