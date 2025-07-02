#include "SoundManager.h"

SoundManager::SoundManager() {}

void SoundManager::LoadSounds()
{
    bgMusic = LoadMusicStream("assets/bgAudio1.mp3");
    bgMusic1 = LoadMusicStream("assets/bgAudio.ogg");
    dyingSound = LoadSound("assets/dyingMain.mp3");
    heliCrashSound = LoadSound("assets/helicrash.mp3");
    bulletSound = LoadSound("assets/bullets.mp3");
    countMusic = LoadMusicStream("assets/countdown-beep.ogg");
    coinSound = LoadSound("assets/coinSound.mp3");
}

void SoundManager::UnloadSounds()
{
    UnloadMusicStream(bgMusic);
    UnloadMusicStream(bgMusic1);
    UnloadSound(dyingSound);
    UnloadSound(heliCrashSound);
    UnloadSound(bulletSound);
    UnloadMusicStream(countMusic);
    UnloadSound(coinSound);
}

// Getters
Music SoundManager::GetBGMusic() const { return bgMusic; }
Music SoundManager::GetBGMusic1() const { return bgMusic1; }
Sound SoundManager::GetDyingSound() const { return dyingSound; }
Sound SoundManager::GetHeliCrashSound() const { return heliCrashSound; }
Sound SoundManager::GetBulletSound() const { return bulletSound; }
Music SoundManager::GetCountSound() const { return countMusic; }
Sound SoundManager::GetCoinSound() const { return coinSound; }

void SoundManager::PlayBGMusic()
{
    PlayMusicStream(bgMusic);
}
void SoundManager::UpdateBGMusic()
{
    UpdateMusicStream(bgMusic);
}