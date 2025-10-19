#ifndef I_MUSIC_H
#define I_MUSIC_H

#include <string>

class IMusic
{
public:
    virtual bool openFromFile(const std::string &filepath) = 0;
    virtual void play() = 0;
    virtual void stop() = 0;
    virtual void pause() = 0;
    virtual ~IMusic() = default;
};

#endif
