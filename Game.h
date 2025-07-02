#pragma once
#include <raylib.h>
#include <vector>
#include "TextureManager.h"
#include "Header.h"
#include "SoundManager.h"
#include "Player.h"
#include "Bullet.h"
#include "GroundEnemy.h"
#include "SkyEnemy.h"
#include "SkyEnemyBullet.h"
#include "GameState.h"
#include "Level.h"

using namespace std;

class Game {
private:
    const int screenWidth = 800;
    const int screenHeight = 600;
    float scrollX = 0.0f;
    int health = 5;
    int score = 0;
    int coinCount = 0;

    TextureManager textureManager;
    SoundManager soundManager;
    Player player;
    vector<FloatingScore> floatingScores;
    vector<Bullet> bullets;
    vector<GroundEnemy> groundEnemies;
    vector<SkyEnemy> skyEnemies;
    vector<SkyEnemyBullet> skyEnemyBullets;
    vector<Platform> platforms;
    vector<Coin> coins;
    vector<HeartPickup> heartPickups;
    GameState gameState;
    Level level;

    // Enemy spawn timers
    float enemySpawnTimer = 0.0f;
    float enemySpawnInterval = 0.0f;
    float skyEnemySpawnTimer = 0.0f;
    float skyEnemySpawnInterval = 0.0f;

    // Bullet animation variables
    int bulletFrameWidth;
    int currentBulletFrame = 0;
    int bulletFrameCounter = 0;
    const int bulletFrameSpeed = 2;

public:
    Game();

    void Initialize();
    void Run();
    void Update(float dt);
    void Draw();
    void Shutdown();

    // Game mechanics
    void InitEnemies();
    void InitPlatforms();
    void LoadBulletTexture();
    void UpdateEnemies(float dt);
    void UpdateSkyEnemies(float dt);
    void CheckBulletEnemyCollision();
    void CheckPlayerEnemyCollision();
    void FireBullet(bool movingUp);
    void DrawScrollingBackground(Texture2D bg, float scrollX);
    void DrawHealth();
    void DrawScore();

    void InitLevel(int levelNum);

    // Getters and setters
    int GetScreenWidth() const;
    int GetScreenHeight() const;
    float GetScrollX() const;
    void SetScrollX(float scroll);
    TextureManager& GetTextureManager();
    SoundManager& GetSoundManager();
    Player& GetPlayer();
    vector<Bullet>& GetBullets();
    vector<GroundEnemy>& GetGroundEnemies();
    vector<SkyEnemy>& GetSkyEnemies();
    vector<SkyEnemyBullet>& GetSkyEnemyBullets();
    vector<Platform>& GetPlatforms();
    GameState& GetGameState();
    Level& GetLevel();
    int GetHealth() const;
    void SetHealth(int h);
    int GetScore() const;
    void SetScore(int s);
    void IncreaseScore();
    void DecreaseHealth();
    int GetCurrentBulletFrame() const;
    void UpdateBulletFrame();
    int GetBulletFrameWidth() const;
};