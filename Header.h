#pragma once
#include <raylib.h>

struct Coin {
    Rectangle rect;
    float originalX;
    bool isActive;
    bool isGold;
    int frame;
    float frameTimer;

    Coin(float x, float y, bool gold)
        : rect{ x, y, 40, 40 }, originalX(x), isActive(true), isGold(gold), frame(0), frameTimer(0.0f) {}
};

struct FloatingScore {
    Vector2 pos;
    int value;
    float timer;
    bool visible;
    Color color;

    FloatingScore(Vector2 p, int v)
        : pos(p), value(v), timer(1.0f), visible(true), color(WHITE) {}
};

struct Platform {
    Rectangle rect;
    float originalX;
    bool isActive;

    Platform() : rect{0,0,0,0}, originalX(0), isActive(false) {}
    Platform(float x, float y, float width, float height, float origX, bool active = true)
        : rect{x, y, width, height}, originalX(origX), isActive(active) {}

};

struct HeartPickup {
    Rectangle rect;
    float originalX;
    int frame = 0;
    float frameTimer = 0.0f;
    static const int totalFrames = 6;
    static constexpr float frameDuration = 0.15f;
    Texture2D texture;
    bool isActive = true;

    HeartPickup(Texture2D tex, float x, float y)
        : rect{ x, y, 180.0f, 153.0f }, originalX(x), frame(0), frameTimer(0.0f), texture(tex), isActive(true) {}

    void Update(float dt, float scrollX) {
        if (!isActive) return;
        frameTimer += dt;
        if (frameTimer >= frameDuration) {
            frame = (frame + 1) % totalFrames;
            frameTimer = 0.0f;
        }
        rect.x = originalX + scrollX;
    }

    void Draw() const {
        if (!isActive) return;
        int frameWidth = texture.width / totalFrames;
        Rectangle src = { (float)(frame * frameWidth), 0, (float)frameWidth, (float)texture.height };
        float scale = 0.2f; 
        Rectangle dest = { rect.x, rect.y, rect.width * scale, rect.height * scale };
        DrawTexturePro(texture, src, dest, {0,0}, 0, WHITE);
    }
};

enum GameStateType {
    LEVEL_INTRO,
    COUNTDOWN,
    PLAYING,
    PAUSED,
    PROCEED,
    GAME_WIN,
    GAME_OVER
};