#ifndef SONG_H
#define SONG_H

#include <string>

class Song
{
private:
    std::string name;
    std::string artistName;
    std::string filepath;

public:
    Song(std::string songName, std::string songArtistName, std::string songFilePath);
    std::string getName();
    std::string getArtistName();
    std::string getFilePath();
};

#endif
