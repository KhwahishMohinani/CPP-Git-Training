#ifndef PLAYLIST_MANAGER_H
#define PLAYLIST_MANAGER_H

#include "IPlaylistManager.h"
#include "IFileHandler.h"
#include <map>

class IAudioPlayer;

class PlaylistManager : public IPlaylistManager
{
private:
    std::map<std::string, IPlaylist *> playlists;
    IFileHandler *fileHandler;

public:
    PlaylistManager(IFileHandler *fileHandler, IAudioPlayer *audioPlayer);
    bool addPlaylist(IPlaylist *playlist);
    IPlaylist *removeExistingPlaylist(std::string playlistName);
    IPlaylist *getPlaylist(std::string playlistName);
    const std::map<std::string, IPlaylist *> &getAllPlaylists() const;
    ~PlaylistManager();
};

#endif
