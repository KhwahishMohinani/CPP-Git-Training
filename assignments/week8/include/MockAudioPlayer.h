#ifndef MOCK_AUDIO_PLAYER_H
#define MOCK_AUDIO_PLAYER_H

#include "IAudioPlayer.h"
#include <gmock/gmock.h>

class MockAudioPlayer : public IAudioPlayer
{
public:
    MOCK_METHOD(bool, load, (const std::string &filepath));
    MOCK_METHOD(void, play, ());
    MOCK_METHOD(void, pause, ());
    MOCK_METHOD(void, stop, ());
};

#endif
