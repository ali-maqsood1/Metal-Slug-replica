#include "SkyEnemyBullet.h"
#include "Game.h"

SkyEnemyBullet::SkyEnemyBullet(Game* gameRef) : GameObject(), speed(175.0f), game(gameRef) {
    rect = { 0, 0, 40, 40 };
}

void SkyEnemyBullet::Fire(float x, float y) {
    rect.x = x;
    rect.y = y;
    isActive = true;
}

void SkyEnemyBullet::Update(float dt) {
    if (!isActive) return;

    rect.y += speed * dt;
    if (rect.y > game->GetScreenHeight()) {
        isActive = false;
    }
}

void SkyEnemyBullet::Draw() {
    if (!isActive) return;

    Rectangle sourceRec = { 0, 0, (float)game->GetTextureManager().GetMissileTexture().width, (float)game->GetTextureManager().GetMissileTexture().height };
    Rectangle destRec = { rect.x, rect.y, rect.width, rect.height };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(game->GetTextureManager().GetMissileTexture(), sourceRec, destRec, origin, 0.0f, WHITE);
}