#pragma once
#include "Header.h"

class Game;

class GameState {
private:
    GameStateType currentState;
    int currentLevel;
    const int levelTargets[10] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    bool levelCompleted;
    Game* game;

public:
    GameState(Game* gameRef) : currentState(GameStateType::LEVEL_INTRO), currentLevel(1), levelCompleted(false), game(gameRef) {}

    GameStateType GetState() const { return currentState; }
    void SetState(GameStateType state) { currentState = state; }
    int GetCurrentLevel() const { return currentLevel; }
    void SetCurrentLevel(int level) { currentLevel = level; }
    bool IsLevelCompleted() const { return levelCompleted; }
    void SetLevelCompleted(bool completed) { levelCompleted = completed; }
    int GetLevelTarget() const { return levelTargets[currentLevel - 1]; }
    void NextLevel() { currentLevel++; }
    bool IsLastLevel() const { return currentLevel > 10; }
};
