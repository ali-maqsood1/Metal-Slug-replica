#pragma once
#include <raylib.h>

class Game;

class Level {
private:
    Game* game;

public:
    Level(Game* gameRef) : game(gameRef) {}

    void ShowCountdown();
    void ShowLevelIntro(int levelNum);
    void ShowProceedScreen();
    void ShowWinScreen();
    void ShowGameOverScreen(int score);
    void ShowLoadingScreen(Music music);
    void ShowControlScreen(Music music);
    void ResetLevel();
};