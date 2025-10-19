#ifndef SFML_MUSIC_H
#define SFML_MUSIC_H

#include <SFML/Audio.hpp>
#include "IMusic.h"

class SFMLMusic : public IMusic
{
private:
    sf::Music music;

public:
    bool openFromFile(const std::string &filepath) override
    {
        return music.openFromFile(filepath);
    }
    void play() override { music.play(); }
    void stop() override { music.stop(); }
    void pause() override { music.pause(); }
};

#endif
