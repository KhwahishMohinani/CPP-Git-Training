#ifndef I_PLAYLIST_MANAGER_H
#define I_PLAYLIST_MANAGER_H

#include <string>
#include <map>

class IPlaylist;

class IPlaylistManager
{
private:
public:
    virtual bool addPlaylist(IPlaylist *playlist) = 0;
    virtual IPlaylist *removeExistingPlaylist(std::string playlistName) = 0;
    virtual IPlaylist *getPlaylist(std::string playlistName) = 0;
    virtual const std::map<std::string, IPlaylist *> &getAllPlaylists() const = 0;
    virtual ~IPlaylistManager() {};
};

#endif
