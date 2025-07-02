#pragma once
#include "Enemy.h"
#include <raylib.h>

class Game;

class GroundEnemy : public Enemy {
public:
    GroundEnemy() : Enemy() {}
    GroundEnemy(Game* gameRef);

    void Update(float dt) override;
    void Draw() override;
    void Reset(float x, float y, int dir);
};