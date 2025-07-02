#include "Player.h"
#include "Game.h"

Player::Player(Game* gameRef) : GameObject(300.0f, 470.0f, 70.0f, 70.0f, true), 
speed(200.0f), verticalVelocity(0.0f), isJumping(false), isFacingRight(true),
isBlinking(false), blinkTimer(0.0f), game(gameRef) {
}

void Player::Update(float dt) {
    if (game->GetHealth() <= 0) return;

    if (IsKeyDown(KEY_LEFT) && rect.x > 0) {
        MoveLeft(dt);
    }

    if (IsKeyDown(KEY_RIGHT)) {
        MoveRight(dt);
    }

    if (IsKeyPressed(KEY_SPACE)) {
        Jump();
    }

    ApplyGravity(dt);

    /*
    if (IsKeyPressed(KEY_F)) {
        PlaySound(game->GetSoundManager().GetBulletSound());
        game->FireBullet(false);
    }

    if (IsKeyPressed(KEY_E)) {
        PlaySound(game->GetSoundManager().GetBulletSound());
        game->FireBullet(true);
    }
     */

    if (isBlinking) {
        blinkTimer -= dt;
        if (blinkTimer <= 0.0f) {
            isBlinking = false;
        }
    }
}

void Player::Draw() {
    Texture2D currentTexture = isFacingRight ?
        game->GetTextureManager().GetPlayerRightTexture() :
        game->GetTextureManager().GetPlayerLeftTexture();

    Color color = isBlinking ? RED : WHITE;

    DrawTexturePro(
        currentTexture,
        { 0, 0, (float)currentTexture.width, (float)currentTexture.height },
        { rect.x, rect.y, rect.width, rect.height },
        { 0, 0 }, 0, color
    );
}

void Player::MoveLeft(float dt) {
    isFacingRight = false;
    if (rect.x > 0) {
        rect.x -= speed * dt;
    }
}

void Player::MoveRight(float dt) {
    isFacingRight = true;
    if (rect.x < game->GetScreenWidth()) {
        if (rect.x < game->GetScreenWidth() / 3) {
            rect.x += speed * dt;
        }
        else {
            float newScrollX = game->GetScrollX() - speed * dt;
            game->SetScrollX(newScrollX);
        }
    }
    
    if (rect.x + rect.width > game->GetScreenWidth()) {
        rect.x = game->GetScreenWidth() - rect.width;
    }
}

void Player::Jump() {
    if (!isJumping) {
        isJumping = true;
        verticalVelocity = jumpStrength;
    }
}


void Player::ApplyGravity(float dt) {
    bool onPlatform = false;
    auto& platforms = game->GetPlatforms();

    for (auto& platform : platforms) {
        if (platform.isActive &&
            rect.y + rect.height >= platform.rect.y &&
            rect.y + rect.height <= platform.rect.y + 10 &&
            rect.x + rect.width > platform.rect.x &&
            rect.x < platform.rect.x + platform.rect.width && verticalVelocity >= 0) {

            rect.y = platform.rect.y - rect.height;

            isJumping = false;
            verticalVelocity = 0;

            onPlatform = true;
            break;
        }
    }

    if (!onPlatform) {
        verticalVelocity += gravity * dt;
        rect.y += verticalVelocity * dt;

        if (rect.y >= groundY) {
            rect.y = groundY;
            isJumping = false;
            verticalVelocity = 0;
        }
    }
}