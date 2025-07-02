#pragma once
#include "GameObject.h"


class Game;



class SkyEnemyBullet : public GameObject {
private:
    float speed;
    Game* game;

public:
    SkyEnemyBullet() : GameObject(), speed(250.0f), game(nullptr) {}
    SkyEnemyBullet(Game* gameRef);

    void Fire(float x, float y);
    void Update(float dt) override;
    void Draw() override;
};