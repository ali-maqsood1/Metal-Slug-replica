#pragma once
#include <raylib.h>
using namespace std;

class TextureManager {
private:
    Texture2D bg;
    Texture2D bg2;
    Texture2D playerLeftTexture;
    Texture2D playerRightTexture;
    Texture2D enemyTexture1;
    Texture2D enemyTexture2;
    Texture2D skyEnemyTexture;
    Texture2D missileTexture;
    Texture2D bulletTexture;
    Texture2D bulletLeftTexture;
    Texture2D healthTexture;
    Texture2D end1Texture;
    Texture2D end2Texture;
    Texture2D winTexture1;
    Texture2D winTexture2;
    Texture2D goldCoinTexture;
    Texture2D silverCoinTexture;
    Texture2D heartTexture;
    Texture2D pauseTexture;

public:
    TextureManager() {}

    void LoadTextures();

    void UnloadTextures();

    // Getters
    Texture2D GetBackgroundTexture() const;
    Texture2D GetPlayerLeftTexture() const;
    Texture2D GetPlayerRightTexture() const;
    Texture2D GetEnemyTexture1() const;
    Texture2D GetEnemyTexture2() const;
    Texture2D GetSkyEnemyTexture() const;
    Texture2D GetMissileTexture() const;
    Texture2D GetBulletTexture() const;
    Texture2D GetBulletLeftTexture() const;
    Texture2D GetHealthTexture() const;
    Texture2D GetEnd1Texture() const;
    Texture2D GetEnd2Texture() const;
    Texture2D GetGoldCoinTexture() const;
    Texture2D GetSilverCoinTexture() const;
    Texture2D GetHeartTexture() const;
    Texture2D GetPauseTexture() const;

    
    // Load specific screens
    Texture2D LoadSpecificTexture(const char* filename);
};