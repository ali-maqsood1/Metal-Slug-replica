#pragma once
#include "GameObject.h"
#include <raylib.h>

class Game;

class Bullet : public GameObject {
private:
    float rad;
    bool isMovingUp;
    bool isMovingLeft;
    static const int bulletFrames = 7;
    int currentFrame;
    int frameCounter;
    const int frameSpeed = 2;
    int bulletFrameWidth;
    Game* game;

public:
    Bullet();
    Bullet(Game* gameRef);

    void Fire(float x, float y, bool movingUp, bool movingLeft);
    void Update(float dt) override;
    void Draw() override;
    void SetFrameWidth(int width) { 
        bulletFrameWidth = width; 
    }
    float GetRadius() const { 
        return rad; 
    }
};