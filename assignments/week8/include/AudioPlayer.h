#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "IAudioPlayer.h"
#include <string>

class IMusic;

class AudioPlayer : public IAudioPlayer
{
private:
    IMusic *music;
    bool isPaused = false;

public:
    AudioPlayer(IMusic *musicPlayer = nullptr);
    bool load(const std::string &filepath);
    void play();
    void pause();
    void stop();
    ~AudioPlayer();
};

#endif
