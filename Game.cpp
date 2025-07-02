
#include <algorithm>
#include "Game.h"

Game::Game() : gameState(this), level(this), player(this) {}

void Game::Initialize() {
    InitWindow(screenWidth, screenHeight, "Metal Slug!");
    InitAudioDevice();
    textureManager.LoadTextures();
    soundManager.LoadSounds();
    soundManager.PlayBGMusic();

    bullets.clear();
    for (int i = 0; i < 10; ++i) {
        bullets.push_back(Bullet(this));
    }
    for (auto& b : bullets)
        b.SetFrameWidth(textureManager.GetBulletTexture().width / 7);

    groundEnemies.resize(5, GroundEnemy(this));
    skyEnemies.resize(3, SkyEnemy(this));
    skyEnemyBullets.resize(15, SkyEnemyBullet(this));

    platforms.clear();
    platforms.push_back(Platform(50, 493, 165, 10, 440));
    platforms.push_back(Platform(750, 372, 175, 10, 175));
    platforms.push_back(Platform(0, 435, 110, 10, 0));
    platforms.push_back(Platform(1200, 493, 110, 10, 1179));
    for (auto& p : platforms) p.isActive = true;
}

void Game::InitLevel(int levelNum) {
    platforms.clear();
    platforms.push_back(Platform(50, 493, 165, 10, 440));
    platforms.push_back(Platform(750, 372, 175, 10, 175));
    platforms.push_back(Platform(0, 435, 110, 10, 0));
    platforms.push_back(Platform(1200, 493, 110, 10, 1179));
    for (auto& p : platforms) p.isActive = true;


    Texture2D heartTex = textureManager.GetHeartTexture();
    heartPickups.clear();
    if (health > 0) { 
        int numHearts = GetRandomValue(1, 3); 
        for (int i = 0; i < numHearts; ++i) {
            float x = GetRandomValue(0, screenWidth - 40); 
            float y = GetRandomValue(screenHeight / 2, 500 - 40); 
            heartPickups.emplace_back(heartTex, x, y);
        }
    }

    if (levelNum == 2) {
        enemySpawnInterval = 2.0f;
        skyEnemySpawnInterval = 3.5f;
    }
    else {
        enemySpawnInterval = 3.0f;
        skyEnemySpawnInterval = 5.0f;
    }
    coins.clear();
    int numCoins = GetRandomValue(5, 10);
    for (int i = 0; i < numCoins; ++i) {
        float x = GetRandomValue(100, 1200);
        float y = GetRandomValue(350, 500);
        bool gold = (GetRandomValue(0, 1) == 1);
        coins.emplace_back(x, y, gold);
    }
}

void Game::Run() {
    level.ShowLoadingScreen(soundManager.GetBGMusic1());
    level.ShowControlScreen(soundManager.GetBGMusic1());

    while (!WindowShouldClose()) {
        soundManager.UpdateBGMusic();
        float dt = GetFrameTime();

        if (gameState.GetState() == GameStateType::PLAYING && IsKeyPressed(KEY_P)) {
            gameState.SetState(GameStateType::PAUSED);
        }

        switch (gameState.GetState()) {
        case GameStateType::LEVEL_INTRO:
            InitLevel(gameState.GetCurrentLevel());
            level.ShowLevelIntro(gameState.GetCurrentLevel());
            gameState.SetState(GameStateType::COUNTDOWN);
            break;
        case GameStateType::COUNTDOWN:
            level.ShowCountdown();
            gameState.SetState(GameStateType::PLAYING);
            break;
        case GameStateType::PLAYING:
            Update(dt);
            Draw();
            if (GetScore() >= gameState.GetLevelTarget()) {
                gameState.SetLevelCompleted(true);
                gameState.SetState(GameStateType::PROCEED);
            }
            if (GetHealth() <= 0) {
                gameState.SetState(GameStateType::GAME_OVER);
            }
            break;
        case GameStateType::PAUSED: {
            BeginDrawing();
            ClearBackground(BLACK); 
            Texture2D pauseTex = textureManager.GetPauseTexture();
            Rectangle src = { 0, 0, (float)pauseTex.width, (float)pauseTex.height };
            Rectangle dest = { 0, 0, (float)screenWidth, (float)screenHeight }; 
            Vector2 origin = { 0, 0 };
            DrawTexturePro(pauseTex, src, dest, origin, 0.0f, WHITE);

            EndDrawing();

            if (IsKeyPressed(KEY_C)) {
                gameState.SetState(GameStateType::PLAYING);
            }
            if (IsKeyPressed(KEY_Q)) {
                Shutdown();
                return;
            }
            break;
        }
        case GameStateType::PROCEED:
            level.ShowProceedScreen();
            if (IsKeyPressed(KEY_N)) {
                gameState.NextLevel();
                if (gameState.IsLastLevel()) {
                    gameState.SetState(GameStateType::GAME_WIN);
                }
                else {
                    gameState.SetLevelCompleted(false);
                    level.ResetLevel();
                    gameState.SetState(GameStateType::LEVEL_INTRO);
                }
            }
            break;
        case GameStateType::GAME_WIN:
            level.ShowWinScreen();
            break;
        case GameStateType::GAME_OVER:
            level.ShowGameOverScreen(GetScore());
            break;
        }
    }
    Shutdown();
}

void Game::Update(float dt) {
    UpdateBulletFrame();
    for (auto& b : bullets) b.Update(dt);
    UpdateEnemies(dt);
    UpdateSkyEnemies(dt);
    float bgWidth = textureManager.GetBackgroundTexture().width;
    float wrappedScroll = scrollX;
    while (wrappedScroll <= -bgWidth) wrappedScroll += bgWidth;
    while (wrappedScroll > 0) wrappedScroll -= bgWidth;

    for (auto& platform : platforms) {
        platform.rect.x = platform.originalX + wrappedScroll;
    }

    player.Update(dt);

    if (IsKeyPressed(KEY_F)) {
        PlaySound(soundManager.GetBulletSound());
        FireBullet(false);
    }
    if (IsKeyPressed(KEY_E)) {
        PlaySound(soundManager.GetBulletSound());
        FireBullet(true);
    }

    for (auto& e : groundEnemies) e.Update(dt);
    for (auto& e : skyEnemies) e.Update(dt);
    for (auto& b : skyEnemyBullets) b.Update(dt);

    // Enemy Spawning
    enemySpawnTimer += dt;
    if (enemySpawnTimer >= enemySpawnInterval) {
        for (auto& enemy : groundEnemies) {
            if (!enemy.IsActive() && !enemy.IsDying()) {
                int dir = GetRandomValue(0, 1);
                float x = (dir == 0) ? -50.0f : (float)screenWidth;
                float y = 490.0f;
                enemy.Reset(x, y, dir);
                enemy.SetActive(true);
                break;
            }
        }
        enemySpawnInterval = GetRandomValue(1, 3);
        enemySpawnTimer = 0.0f;
    }

    skyEnemySpawnTimer += dt;
    if (skyEnemySpawnTimer >= skyEnemySpawnInterval) {
        for (auto& enemy : skyEnemies) {
            if (!enemy.IsActive() && !enemy.IsDying()) {
                float x = (float)screenWidth;
                float y = 100.0f;
                enemy.Reset(x, y);
                enemy.SetActive(true);
                break;
            }
        }
        skyEnemySpawnInterval = GetRandomValue(3, 5);
        skyEnemySpawnTimer = 0.0f;
    }

    // bullet to bullet collision
    for (auto& playerBullet : bullets) {
        if (!playerBullet.IsActive()) continue;
        for (auto& skyBullet : skyEnemyBullets) {
            if (!skyBullet.IsActive()) continue;
            if (CheckCollisionRecs(playerBullet.GetRect(), skyBullet.GetRect())) {
                playerBullet.SetActive(false);
                skyBullet.SetActive(false);
            }
        }
    }

    CheckBulletEnemyCollision();
    CheckPlayerEnemyCollision();

    // Floating Score ++
    for (auto& fs : floatingScores) {
        if (fs.visible) {
            fs.timer -= dt;
            fs.pos.y -= 30 * dt;
            if (((int)(fs.timer * 10) % 2) == 0)
                fs.color = YELLOW;
            else
                fs.color = WHITE;
            if (fs.timer <= 0) fs.visible = false;
        }
    }
    floatingScores.erase(
        std::remove_if(floatingScores.begin(), floatingScores.end(),
                    [](const FloatingScore& fs){ return !fs.visible; }),
        floatingScores.end()
    );

    for (auto& coin : coins) {
        if (!coin.isActive) continue;
        coin.frameTimer += dt;
        if (coin.frameTimer >= 0.07f) {
            coin.frame = (coin.frame + 1) % 13;
            coin.frameTimer = 0.0f;
        }
    }

    while (wrappedScroll <= -bgWidth) wrappedScroll += bgWidth;
    while (wrappedScroll > 0) wrappedScroll -= bgWidth;
    for (auto& coin : coins) {
        coin.rect.x = coin.originalX + wrappedScroll;
    }

    // setting hearts
    for (auto& heart : heartPickups) {
        heart.rect.x = heart.originalX + wrappedScroll;
    }

    // random position for hearts
    if (scrollX <= -bgWidth) {
        scrollX += bgWidth;
        for (auto& heart : heartPickups) {
            heart.isActive = true;
            heart.originalX = GetRandomValue(200, 1200);
            heart.rect.x = heart.originalX + scrollX;
            heart.rect.y = GetRandomValue(350, 500);
        }
    }

    for (auto& coin : coins) {
        if (!coin.isActive) continue;
        if (CheckCollisionRecs(player.GetRect(), coin.rect)) {
            coin.isActive = false;
            coinCount += coin.isGold ? 5 : 3;
            PlaySound(soundManager.GetCoinSound());
        }
    }

    

    for (auto& heart : heartPickups) {
        heart.Update(dt, scrollX);
        if (heart.isActive && CheckCollisionRecs(player.GetRect(), heart.rect)) {
            heart.isActive = false;
            if (health < 5) health++; 
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawScrollingBackground(textureManager.GetBackgroundTexture(), scrollX);
    for (auto& b : bullets)
    {
        if (b.IsActive()) {
            b.Draw();
        }
    }

    for (auto& heart : heartPickups) {
        heart.Draw();
    }
    for (auto& e : groundEnemies) e.Draw();
    for (auto& e : skyEnemies) e.Draw();
    for (auto& b : skyEnemyBullets) b.Draw();
    for (const auto& coin : coins) {
        if (!coin.isActive) continue;
        Texture2D tex = coin.isGold ? textureManager.GetGoldCoinTexture() : textureManager.GetSilverCoinTexture();
        int frameWidth = tex.width / 13;
        Rectangle src = { (float)(coin.frame * frameWidth), 0, (float)frameWidth, (float)tex.height };
        Rectangle dst = { coin.rect.x, coin.rect.y, coin.rect.width, coin.rect.height };
        DrawTexturePro(tex, src, dst, {0,0}, 0, WHITE);
    }
    player.Draw();
    DrawHealth();
    DrawScore();
    DrawText(TextFormat("Coins: %d", coinCount), screenWidth - 140, 40, 20, YELLOW);
    for (const auto& fs : floatingScores) {
        if (fs.visible) {
            DrawText(TextFormat("+%d", fs.value), (int)fs.pos.x, (int)fs.pos.y, 24, fs.color);
        }
    }
    EndDrawing();
}

void Game::Shutdown() {
    textureManager.UnloadTextures();
    soundManager.UnloadSounds();
    CloseAudioDevice();
    CloseWindow();
}

void Game::DrawScrollingBackground(Texture2D bg, float scrollX) {
    float bgWidth = bg.width;
    float x = scrollX;
    while (x <= -bgWidth) x += bgWidth;
    while (x > 0) x -= bgWidth;
    DrawTextureEx(bg, { x, 0 }, 0.0f, 1.0f, WHITE);
    DrawTextureEx(bg, { x + bgWidth, 0 }, 0.0f, 1.0f, WHITE);
}

void Game::DrawHealth() {
    Texture2D healthTexture = textureManager.GetHealthTexture();
    float scale = 0.02f;
    int iconWidth = (int)(healthTexture.width * scale);
    int iconHeight = (int)(healthTexture.height * scale);
    for (int i = 0; i < health; i++) {
        DrawTextureEx(
            healthTexture,
            { 10.0f + i * (iconWidth + 5), 10.0f },
            0.0f,
            scale,
            WHITE
        );
    }
}

void Game::DrawScore() {
    DrawText(TextFormat("Score : %d", score), screenWidth - 140, 10, 20, WHITE);
}

void Game::FireBullet(bool movingUp) {
    for (auto& bullet : bullets) {
        if (!bullet.IsActive()) {
            float bulletX = player.GetRect().x + (player.IsFacingRight() ? player.GetRect().width : -bullet.GetRadius() * 2);
            float bulletY = player.GetRect().y + player.GetRect().height / 2;
            bullet.Fire(bulletX, bulletY, movingUp, !player.IsFacingRight());
            break;
        }
    }
}

void Game::UpdateBulletFrame() {
    bulletFrameCounter++;
    if (bulletFrameCounter >= bulletFrameSpeed) {
        bulletFrameCounter = 0;
        currentBulletFrame = (currentBulletFrame + 1) % 7;
    }
}

void Game::CheckBulletEnemyCollision() {
    for (auto& bullet : bullets) {
        if (!bullet.IsActive()) continue;
        for (auto& enemy : groundEnemies) {
            if (enemy.IsActive() && !enemy.IsDying()) {
                if (CheckCollisionRecs(bullet.GetRect(), enemy.GetRect())) {
                    bullet.SetActive(false);
                    enemy.SetDying(true);
                    IncreaseScore();
                    PlaySound(soundManager.GetDyingSound());
                    floatingScores.emplace_back(
                        Vector2{ enemy.GetRect().x + enemy.GetRect().width/2, enemy.GetRect().y - 20 },
                        1
                    );
                }
            }
        }
        for (auto& enemy : skyEnemies) {
            if (enemy.IsActive() && !enemy.IsDying()) {
                if (CheckCollisionRecs(bullet.GetRect(), enemy.GetRect())) {
                    bullet.SetActive(false);
                    enemy.SetDying(true);
                    IncreaseScore();
                    PlaySound(soundManager.GetHeliCrashSound());
                    floatingScores.emplace_back(
                        Vector2{ enemy.GetRect().x + enemy.GetRect().width/2, enemy.GetRect().y - 20 },
                        1
                    );
                }
            }
        }
    }
}

void Game::CheckPlayerEnemyCollision() {
    for (auto& enemy : groundEnemies) {
        if (enemy.IsActive() && CheckCollisionRecs(player.GetRect(), enemy.GetRect())) {
            DecreaseHealth();
            player.SetBlinking(true);
            enemy.SetActive(false);
        }
    }
    for (auto& bullet : skyEnemyBullets) {
        if (bullet.IsActive() && CheckCollisionRecs(player.GetRect(), bullet.GetRect())) {
            DecreaseHealth();
            player.SetBlinking(true);
            bullet.SetActive(false);
        }
    }
}

void Game::UpdateEnemies(float dt) {
    for (auto& e : groundEnemies) e.Update(dt);
}

void Game::UpdateSkyEnemies(float dt) {
    for (auto& e : skyEnemies) e.Update(dt);
    for (auto& b : skyEnemyBullets) b.Update(dt);
}

void Game::InitEnemies() {
    for (auto& enemy : groundEnemies) enemy.SetActive(false);
    for (auto& enemy : skyEnemies) enemy.SetActive(false);
    for (auto& bullet : skyEnemyBullets) bullet.SetActive(false);
}

void Game::InitPlatforms() {
    for (auto& platform : platforms) {
        platform.isActive = true;
    }
}

void Game::LoadBulletTexture() {
    bulletFrameWidth = textureManager.GetBulletTexture().width / 7;
    for (auto& b : bullets) b.SetFrameWidth(bulletFrameWidth);
}

int Game::GetScreenWidth() const { return screenWidth; }
int Game::GetScreenHeight() const { return screenHeight; }
float Game::GetScrollX() const { return scrollX; }
void Game::SetScrollX(float scroll) { scrollX = scroll; }
TextureManager& Game::GetTextureManager() { return textureManager; }
SoundManager& Game::GetSoundManager() { return soundManager; }
Player& Game::GetPlayer() { return player; }
vector<Bullet>& Game::GetBullets() { return bullets; }
vector<GroundEnemy>& Game::GetGroundEnemies() { return groundEnemies; }
vector<SkyEnemy>& Game::GetSkyEnemies() { return skyEnemies; }
vector<SkyEnemyBullet>& Game::GetSkyEnemyBullets() { return skyEnemyBullets; }
vector<Platform>& Game::GetPlatforms() { return platforms; }
GameState& Game::GetGameState() { return gameState; }
Level& Game::GetLevel() { return level; }
int Game::GetHealth() const { return health; }
void Game::SetHealth(int h) { health = h; }
int Game::GetScore() const { return score; }
void Game::SetScore(int s) { score = s; }
void Game::IncreaseScore() { score++; }
void Game::DecreaseHealth() { health--; }
int Game::GetCurrentBulletFrame() const { return currentBulletFrame; }
int Game::GetBulletFrameWidth() const { return bulletFrameWidth; }