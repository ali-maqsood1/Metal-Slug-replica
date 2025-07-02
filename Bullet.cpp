#include "Game.h"
#include "Bullet.h"

Bullet::Bullet() : GameObject(), rad(5.0f), isMovingUp(false), isMovingLeft(false), currentFrame(0), frameCounter(0), game(nullptr) {}

Bullet::Bullet(Game* gameRef) : GameObject(), rad(5.0f), isMovingUp(false), isMovingLeft(false),
    currentFrame(0), frameCounter(0), game(gameRef) {
    rect.width = 40.0f;
    rect.height = 20.0f;
}

void Bullet::Fire(float x, float y, bool movingUp, bool movingLeft) {
    isActive = true;
    rect.x = x;
    rect.y = y;
    isMovingUp = movingUp;
    isMovingLeft = movingLeft;
    rect.width = 40.0f;
    rect.height = 20.0f;
}

void Bullet::Update(float dt) {
    if (!isActive) return;

    if (isMovingUp) {
        rect.y -= 300.0f * dt;
        if (isMovingLeft) {
            rect.x -= 40.0f * dt;
        }
        else {
            rect.x += 40.0f * dt;
        }

        if (rect.y < 0) {
            isActive = false;
        }
    }
    else if (isMovingLeft) {
        rect.x -= 300.0f * dt;
        if (rect.x < 0) {
            isActive = false;
        }
    }
    else {
        rect.x += 300.0f * dt;
        if (game && rect.x > game->GetScreenWidth()) {
            isActive = false;
        }
    }

    frameCounter++;
    if (frameCounter >= frameSpeed) {
        frameCounter = 0;
        currentFrame = (currentFrame + 1) % bulletFrames;
    }
}

void Bullet::Draw() {
    if (!isActive) return;

    Texture2D currentTexture = isMovingLeft ?
        game->GetTextureManager().GetBulletLeftTexture() :
        game->GetTextureManager().GetBulletTexture();

    int frameWidth = bulletFrameWidth;
    int frameHeight = currentTexture.height;
    Rectangle sourceRec = { (float)(currentFrame * frameWidth), 0, (float)frameWidth, (float)frameHeight };

    float bulletWidth = 40.0f;
    float bulletHeight = 20.0f;
    Rectangle destRec = { rect.x, rect.y, bulletWidth, bulletHeight };

    Vector2 origin = { 0, 0 };
    float rotation = 0.0f;
    if (isMovingUp) {
        rotation = isMovingLeft ? 90.0f : -90.0f;
    }
    DrawTexturePro(currentTexture, sourceRec, destRec, origin, rotation, WHITE);
}