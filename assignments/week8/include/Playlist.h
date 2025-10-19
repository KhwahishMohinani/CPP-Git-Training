#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "IPlaylist.h"
#include "IAudioPlayer.h"
#include <list>
#include <string>

class Playlist : public IPlaylist
{
private:
    std::string name;
    std::list<Song *> songs;
    std::list<Song *>::iterator currentSong;
    IAudioPlayer *audioPlayer;
    Song *currentPlayingSong = nullptr;

public:
    Playlist(std::string playlistName, IAudioPlayer *player);
    std::string getName();
    std::list<Song *> getSongs();
    bool addSong(Song *song);
    Song *removeSong(int index);
    Song *getCurrentSong();
    int playCurrentSong();
    bool playNextSong();
    bool playPreviousSong();
    bool moveSong(int fromIndex, int toIndex);
    void pause();
    void stop();
};

#endif
