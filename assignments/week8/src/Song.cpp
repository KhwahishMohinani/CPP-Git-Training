#include "Song.h"

Song::Song(std::string songName, std::string songArtistName, std::string songFilePath)
    : name(songName), artistName(songArtistName), filepath(songFilePath)
{
}

std::string Song::getName()
{
    return name;
}

std::string Song::getArtistName()
{
    return artistName;
}

std::string Song::getFilePath()
{
    return filepath;
}
