#include "GroundEnemy.h"
#include "Game.h"

GroundEnemy::GroundEnemy(Game* gameRef) : Enemy(gameRef) {
    rect = { 0, 490, 80, 80 }; 
    speed = 140.0f;
}

void GroundEnemy::Update(float dt) {
    Enemy::Update(dt);

    if (!isActive || isDying) return;

    if (direction == 0) {
        rect.x += speed * dt;
        if (rect.x > game->GetScreenWidth()) {
            isActive = false;
        }
    }
    else {
        rect.x -= speed * dt;
        if (rect.x < -rect.width) {
            isActive = false;
        }
    }
}

void GroundEnemy::Draw() {
    if (!isActive && !isDying) return;

    Texture2D currentTexture = (direction == 0) ?
        game->GetTextureManager().GetEnemyTexture1() :
        game->GetTextureManager().GetEnemyTexture2();

    Rectangle sourceRec = { 0, 0, (float)currentTexture.width, (float)currentTexture.height };
    Rectangle destRec = { rect.x, rect.y, rect.width, rect.height };
    Vector2 origin = { 0, 0 };

    if (direction == 0) {
        destRec.y = rect.y - 25;
    }
    else {
        destRec.y = rect.y - 13;
    }

    Color color = (isDying || isBlinking) ? RED : WHITE;
    DrawTexturePro(currentTexture, sourceRec, destRec, origin, 0.0f, color);
}

void GroundEnemy::Reset(float x, float y, int dir) {
    rect.x = x;
    rect.y = y;
    direction = dir;
    isActive = true;
    isDying = false;
    isBlinking = false;
}