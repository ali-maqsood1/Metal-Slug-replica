#include "Enemy.h"


Enemy::Enemy(Game* gameRef) : GameObject(), speed(0.0f), direction(0), isDying(false), isBlinking(false),
dyingTimer(0.0f), blinkTimer(0.0f), game(gameRef) {
}

void Enemy::Update(float dt) {
    if (isDying) {
        dyingTimer -= dt;
        if (dyingTimer <= 0.0f) {
            isActive = false;
            isDying = false;
            isBlinking = false;
        }
    }

    if (isBlinking) {
        blinkTimer -= dt;
        if (blinkTimer <= 0.0f) {
            isBlinking = false;
        }
    }
}

void Enemy::Draw() {
    // will be overrided
}