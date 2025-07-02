#pragma once
#include <raylib.h>
#include "GameObject.h"

class Game;


class Enemy : public GameObject {
protected:
    float speed;
    int direction;
    bool isDying;
    bool isBlinking;
    float dyingTimer;
    float blinkTimer;
    const float dyingDuration = 0.1f;
    const float blinkDuration = 0.1f;
    Game* game;

public:
    Enemy() : GameObject(), speed(0.0f), direction(0), isDying(false), isBlinking(false), dyingTimer(0.0f), blinkTimer(0.0f), game(nullptr) {}
    Enemy(Game* gameRef);

    virtual void Update(float dt) override;
    virtual void Draw() override;
    void SetDying(bool dying) { 
        isDying = dying; 
        dyingTimer = dyingDuration; 
        isBlinking = true; 
        blinkTimer = blinkDuration; 
    }
    bool IsDying() const { 
        return isDying; 
    }
};