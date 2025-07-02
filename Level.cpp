#include "Level.h"
#include "Game.h"

void Level::ShowCountdown() {
    Texture2D count3 = game->GetTextureManager().LoadSpecificTexture("assets/count3.png");
    Texture2D count2 = game->GetTextureManager().LoadSpecificTexture("assets/count2.png");
    Texture2D count1 = game->GetTextureManager().LoadSpecificTexture("assets/count1.png");
    Texture2D go = game->GetTextureManager().LoadSpecificTexture("assets/countGO.png");

    int centerX = game->GetScreenWidth() / 2;
    int centerY = game->GetScreenHeight() / 2;

    Texture2D countdownFrames[] = { count3, count2, count1, go };
    float displayTime = 1.0f;
    SetMusicPitch(game->GetSoundManager().GetCountSound(), 1.6f); 
    PlayMusicStream(game->GetSoundManager().GetCountSound());

    for (int i = 0; i < 4; i++) {
        float startTime = GetTime();
        while (GetTime() - startTime < displayTime) {
            UpdateMusicStream(game->GetSoundManager().GetCountSound());
            BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(countdownFrames[i], centerX - countdownFrames[i].width / 2, centerY - countdownFrames[i].height / 2, WHITE);
            EndDrawing();
        }
        
        WaitTime(0.58f);
    }

    UnloadTexture(count3);
    UnloadTexture(count2);
    UnloadTexture(count1);
    UnloadTexture(go);
}

void Level::ShowLevelIntro(int levelNum) {
    const char* fileName = TextFormat("assets/level%d.png", levelNum);
    Texture2D levelTexture = game->GetTextureManager().LoadSpecificTexture(fileName);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    int centerX = (game->GetScreenWidth() - levelTexture.width) / 2;
    int centerY = (game->GetScreenHeight() - levelTexture.height) / 2;
    DrawTexture(levelTexture, centerX, centerY, WHITE);
    EndDrawing();

    WaitTime(0.6);
    UnloadTexture(levelTexture);
}

void Level::ShowProceedScreen() {
    Texture2D proceed1 = game->GetTextureManager().LoadSpecificTexture("assets/proceed1.png");
    Texture2D proceed2 = game->GetTextureManager().LoadSpecificTexture("assets/proceed2.png");
    Texture2D proceed3 = game->GetTextureManager().LoadSpecificTexture("assets/proceed3.png");

    int centerX = game->GetScreenWidth() / 2;
    int centerY = game->GetScreenHeight() / 2;

    Texture2D proceedFrames[] = { proceed1, proceed2, proceed3 };
    int numFrames = 3;
    int currentFrame = 0;
    float frameTime = 0.0f;
    float frameDuration = 0.5f;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_N)) break;
        if (IsKeyPressed(KEY_Q)) { CloseWindow(); exit(0); }

        frameTime += GetFrameTime();
        if (frameTime >= frameDuration) {
            frameTime = 0.0f;
            currentFrame = (currentFrame + 1) % numFrames;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(proceedFrames[currentFrame], centerX - proceedFrames[currentFrame].width / 2,
            centerY - proceedFrames[currentFrame].height / 2, WHITE);
        DrawText(TextFormat("%d", game->GetScore()), centerX + 40, centerY - 132, 40, WHITE);
        EndDrawing();
    }

    UnloadTexture(proceed1);
    UnloadTexture(proceed2);
    UnloadTexture(proceed3);
}

void Level::ShowWinScreen() {
    Texture2D win1 = game->GetTextureManager().LoadSpecificTexture("assets/win1.png");
    Texture2D win2 = game->GetTextureManager().LoadSpecificTexture("assets/win2.png");

    int centerX = game->GetScreenWidth() / 2;
    int centerY = game->GetScreenHeight() / 2;

    Texture2D winFrames[] = { win1, win2 };
    int numFrames = 2;
    int currentFrame = 0;
    float frameTime = 0.0f;
    float frameDuration = 0.5f;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ENTER))
        {
            // Reset game state for replay
            game->GetLevel().ResetLevel();
            game->GetGameState().SetCurrentLevel(1);
            game->GetGameState().SetState(GameStateType::LEVEL_INTRO);
            // CloseWindow(); 
            break;
        }

        frameTime += GetFrameTime();
        if (frameTime >= frameDuration) {
            frameTime = 0.0f;
            currentFrame = (currentFrame + 1) % numFrames;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(winFrames[currentFrame], centerX - winFrames[currentFrame].width / 2,
            centerY - winFrames[currentFrame].height / 2, WHITE);
        EndDrawing();
    }

    UnloadTexture(win1);
    UnloadTexture(win2);
}

void Level::ShowGameOverScreen(int score) {
    Texture2D end1 = game->GetTextureManager().GetEnd1Texture();
    Texture2D end2 = game->GetTextureManager().GetEnd2Texture();

    Texture2D frames[] = { end1, end2 };
    int numFrames = 2;
    int currentFrame = 0;
    float frameTime = 0.0f;

    while (!WindowShouldClose()) {
        frameTime += GetFrameTime();
        if (frameTime >= 0.5f) {
            frameTime = 0.0f;
            currentFrame = (currentFrame + 1) % numFrames;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(frames[currentFrame], 0, 0, WHITE);
        DrawText(TextFormat("%d", score), 456, 256, 22, BLACK);
        EndDrawing();

        if (IsKeyPressed(KEY_R)) {
            ResetLevel();
            game->GetGameState().SetCurrentLevel(1);
            game->GetGameState().SetState(GameStateType::LEVEL_INTRO);
            break;
        }
        else if (IsKeyPressed(KEY_Q)) {
            CloseWindow();
            exit(0);
        }
    }
}

void Level::ShowLoadingScreen(Music music) {
    StopMusicStream(music);
    PlayMusicStream(music);
    Texture2D load25 = game->GetTextureManager().LoadSpecificTexture("assets/load25.png");
    Texture2D load50 = game->GetTextureManager().LoadSpecificTexture("assets/load50.png");
    Texture2D load75 = game->GetTextureManager().LoadSpecificTexture("assets/load75.png");
    Texture2D load100 = game->GetTextureManager().LoadSpecificTexture("assets/load100.png");
    Texture2D enter1 = game->GetTextureManager().LoadSpecificTexture("assets/enter1.png");
    Texture2D enter2 = game->GetTextureManager().LoadSpecificTexture("assets/enter2.png");

    int centerX = game->GetScreenWidth() / 2;
    int centerY = game->GetScreenHeight() / 2;

    Texture2D loadingFrames[] = { load25, load50, load75, load100 };
    for (int i = 0; i < 4; i++) {
        float startTime = GetTime();
        while (GetTime() - startTime < 0.5f) {
            UpdateMusicStream(music);
            BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(loadingFrames[i], centerX - loadingFrames[i].width / 2, centerY - loadingFrames[i].height / 2, WHITE);
            EndDrawing();
        }
    }

    while (!IsKeyPressed(KEY_ENTER) && !WindowShouldClose()) {
        UpdateMusicStream(music);
        BeginDrawing();
        ClearBackground(BLACK);
        if ((int)(GetTime() * 2) % 2 == 0) {
            DrawTexture(enter1, centerX - enter1.width / 2, centerY - enter1.height / 2, WHITE);
        }
        else {
            DrawTexture(enter2, centerX - enter2.width / 2, centerY - enter2.height / 2, WHITE);
        }
        EndDrawing();
    }

    UnloadTexture(load25);
    UnloadTexture(load50);
    UnloadTexture(load75);
    UnloadTexture(load100);
    UnloadTexture(enter1);
    UnloadTexture(enter2);
}

void Level::ShowControlScreen(Music music) {
    Texture2D control = game->GetTextureManager().LoadSpecificTexture("assets/control.png");
    int centerX = game->GetScreenWidth() / 2;
    int centerY = game->GetScreenHeight() / 2;

    while (!(IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT)) && !WindowShouldClose()) {
        UpdateMusicStream(music);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(control, centerX - control.width / 2, centerY - control.height / 2, WHITE);
        EndDrawing();
    }

    UnloadTexture(control);
}

void Level::ResetLevel() {
    game->SetHealth(5);
    game->SetScore(0);
    game->SetScrollX(0.0f);

    auto& player = game->GetPlayer();
    player.SetPosition(300.0f, 470.0f);

    for (auto& enemy : game->GetGroundEnemies()) enemy.SetActive(false);
    for (auto& enemy : game->GetSkyEnemies()) enemy.SetActive(false);
    for (auto& bullet : game->GetBullets()) bullet.SetActive(false);
    for (auto& bullet : game->GetSkyEnemyBullets()) bullet.SetActive(false);
}