#ifndef MOCK_MUSIC_H
#define MOCK_MUSIC_H

#include "IMusic.h"
#include <gmock/gmock.h>

class MockMusic : public IMusic
{
public:
    MOCK_METHOD(bool, openFromFile, (const std::string &filepath));
    MOCK_METHOD(void, play, ());
    MOCK_METHOD(void, stop, ());
    MOCK_METHOD(void, pause, ());
};

#endif
