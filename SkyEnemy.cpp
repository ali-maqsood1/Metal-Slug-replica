#include "SkyEnemy.h"
#include "Game.h"

SkyEnemy::SkyEnemy(Game* gameRef) : Enemy(gameRef), fireRate(1.0f), fireTimer(0.0f) {
    rect = { (float)GetRandomValue(game->GetScreenWidth() - 200, game->GetScreenWidth() - 50), 100, 80, 80 };
    speed = 140.0f;
}

void SkyEnemy::Update(float dt) {
    Enemy::Update(dt);

    if (!isActive || isDying) return;

    fireTimer += dt;
    if (fireTimer >= fireRate) {
        Fire();
        fireTimer = 0.0f;
    }

    rect.x -= speed * dt;
    if (rect.x < -rect.width) {
        isActive = false;
    }
}

void SkyEnemy::Draw() {
    if (!isActive && !isDying) return;

    Rectangle sourceRec = { 0, 0, (float)game->GetTextureManager().GetSkyEnemyTexture().width, (float)game->GetTextureManager().GetSkyEnemyTexture().height };
    Rectangle destRec = { rect.x, rect.y, rect.width, rect.height };
    Vector2 origin = { 0, 0 };
    Color color = (isDying || isBlinking) ? RED : WHITE;
    DrawTexturePro(game->GetTextureManager().GetSkyEnemyTexture(), sourceRec, destRec, origin, 0.0f, color);
}

void SkyEnemy::Reset(float x, float y) {
    rect.x = x;
    rect.y = y;
    isActive = true;
    isDying = false;
    isBlinking = false;
    fireTimer = 0.0f;
}

void SkyEnemy::Fire() {
    // Find an inactive bullet to fire
    auto& bullets = game->GetSkyEnemyBullets();
    for (auto& bullet : bullets) {
        if (!bullet.IsActive()) {
            bullet.Fire(rect.x + 10, rect.y + 20);
            break;
        }
    }
}