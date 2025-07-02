#pragma once
#include "Enemy.h"

class Game;

class SkyEnemy : public Enemy {
private:
    float fireRate;
    float fireTimer;

public:
    SkyEnemy() : Enemy(), fireRate(1.0f), fireTimer(0.0f) {}
    SkyEnemy(Game* gameRef);

    void Update(float dt) override;
    void Draw() override;
    void Reset(float x, float y);
    void Fire();
};