#include "IMusic.h"
#include "AudioPlayer.h"
#include "SFML_Music.h"
#include <iostream>

AudioPlayer::AudioPlayer(IMusic *musicPlayer)
    : music(musicPlayer ? musicPlayer : new SFMLMusic())
{
}

bool AudioPlayer::load(const std::string &filepath)
{
    bool success = false;
    if (music->openFromFile(filepath))
    {
        success = true;
        isPaused = false;
    }
    return success;
}

void AudioPlayer::play()
{
    if (isPaused)
    {
        music->play();
    }
    else
    {
        music->stop();
        music->play();
    }
    isPaused = false;
}

void AudioPlayer::pause()
{
    music->pause();
    isPaused = true;
}

void AudioPlayer::stop()
{
    music->stop();
    isPaused = false;
}

AudioPlayer::~AudioPlayer()
{
    if (music)
        music->stop();
    isPaused = false;
    delete music;
}
