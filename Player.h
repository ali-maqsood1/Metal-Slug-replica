#pragma once
#include "GameObject.h"

class Game;

class Player : public GameObject {
private:
    float speed;
    float verticalVelocity;
    bool isJumping;
    bool isFacingRight;
    bool isBlinking;
    float blinkTimer;
    const float blinkDuration = 0.1f;
    const float gravity = 800.0f;
    const float jumpStrength = -500.0f;
    const float groundY = 470.0f;
    Game* game;

public:
    Player() : GameObject(), speed(200.0f), verticalVelocity(0.0f), isJumping(false), isFacingRight(true),
        isBlinking(false), blinkTimer(0.0f), game(nullptr) {
    }
    Player(Game* gameRef);

    void Update(float dt) override;
    void Draw() override;
    void MoveLeft(float dt);
    void MoveRight(float dt);
    void Jump();
    void ApplyGravity(float dt);
    void SetBlinking(bool blink) { isBlinking = blink; blinkTimer = blinkDuration; }
    bool IsBlinking() const { return isBlinking; }
    bool IsFacingRight() const { return isFacingRight; }
    Rectangle GetHitbox() const { return rect; }
};

