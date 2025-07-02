#include "TextureManager.h"

void TextureManager :: LoadTextures() {
    bg = LoadTexture("assets/perfectBG1.png");
    playerLeftTexture = LoadTexture("assets/left face.png");
    playerRightTexture = LoadTexture("assets/main_char.png");
    enemyTexture1 = LoadTexture("assets/enemy1.png");
    enemyTexture2 = LoadTexture("assets/enemy2.png");
    skyEnemyTexture = LoadTexture("assets/skyEnemy.png");
    missileTexture = LoadTexture("assets/missile.png");
    bulletTexture = LoadTexture("assets/bullets.png");
    bulletLeftTexture = LoadTexture("assets/bulletsLeft.png");
    healthTexture = LoadTexture("assets/health.png");
    end1Texture = LoadTexture("assets/end1.png");
    end2Texture = LoadTexture("assets/end2.png");
    goldCoinTexture = LoadTexture("assets/goldCoins.png");
    silverCoinTexture = LoadTexture("assets/silverCoins.png");
    heartTexture = LoadTexture("assets/heartBlink.png");
    pauseTexture = LoadTexture("assets/pauseScreen.png");

}


void TextureManager :: UnloadTextures() {
        UnloadTexture(bg);
        UnloadTexture(playerLeftTexture);
        UnloadTexture(playerRightTexture);
        UnloadTexture(enemyTexture1);
        UnloadTexture(enemyTexture2);
        UnloadTexture(skyEnemyTexture);
        UnloadTexture(missileTexture);
        UnloadTexture(bulletTexture);
        UnloadTexture(bulletLeftTexture);
        UnloadTexture(healthTexture);
        UnloadTexture(end1Texture);
        UnloadTexture(end2Texture);
        UnloadTexture(goldCoinTexture);
        UnloadTexture(silverCoinTexture);
        UnloadTexture(goldCoinTexture);
        UnloadTexture(silverCoinTexture);
        UnloadTexture(heartTexture);
        UnloadTexture(pauseTexture);
}

Texture2D TextureManager :: LoadSpecificTexture(const char* filename) {
    return LoadTexture(filename);
}

Texture2D TextureManager::GetBackgroundTexture() const { return bg; }
Texture2D TextureManager::GetPlayerLeftTexture() const { return playerLeftTexture; }
Texture2D TextureManager::GetPlayerRightTexture() const { return playerRightTexture; }
Texture2D TextureManager::GetEnemyTexture1() const { return enemyTexture1; }
Texture2D TextureManager::GetEnemyTexture2() const { return enemyTexture2; }
Texture2D TextureManager::GetSkyEnemyTexture() const { return skyEnemyTexture; }
Texture2D TextureManager::GetMissileTexture() const { return missileTexture; }
Texture2D TextureManager::GetBulletTexture() const { return bulletTexture; }
Texture2D TextureManager::GetBulletLeftTexture() const { return bulletLeftTexture; }
Texture2D TextureManager::GetHealthTexture() const { return healthTexture; }
Texture2D TextureManager::GetEnd1Texture() const { return end1Texture; }
Texture2D TextureManager::GetEnd2Texture() const { return end2Texture; }
Texture2D TextureManager::GetGoldCoinTexture() const { return goldCoinTexture; }
Texture2D TextureManager::GetSilverCoinTexture() const { return silverCoinTexture; }
Texture2D TextureManager::GetHeartTexture() const { return heartTexture; }
Texture2D TextureManager::GetPauseTexture() const { return pauseTexture; }