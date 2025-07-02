#pragma once
#include <raylib.h>

class SoundManager {
private:
    Music bgMusic;
    Music bgMusic1;
    Sound dyingSound;
    Sound heliCrashSound;
    Sound bulletSound;
    Music countMusic;
    Sound coinSound;

public:
    SoundManager();

    void LoadSounds();
    void UnloadSounds();

    // Getters
    Music GetBGMusic() const;
    Music GetBGMusic1() const;
    Sound GetDyingSound() const;
    Sound GetHeliCrashSound() const;
    Sound GetBulletSound() const;
    Music GetCountSound() const;
    Sound GetCoinSound() const;

    void PlayBGMusic();
    void UpdateBGMusic();
};