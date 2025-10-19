#ifndef I_PLAYLIST_H
#define I_PLAYLIST_H

#include <string>
#include <list>
#include "Song.h"

class IPlaylist
{
public:
    virtual std::string getName() = 0;
    virtual std::list<Song *> getSongs() = 0;
    virtual bool addSong(Song *song) = 0;
    virtual Song *removeSong(int index) = 0;
    virtual int playCurrentSong() = 0;
    virtual Song *getCurrentSong() = 0;
    virtual bool playNextSong() = 0;
    virtual bool playPreviousSong() = 0;
    virtual bool moveSong(int fromIndex, int toIndex) = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
};

#endif
