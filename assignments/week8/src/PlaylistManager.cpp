#include "PlaylistManager.h"
#include "Playlist.h"
#include "constants.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

PlaylistManager::PlaylistManager(IFileHandler *fileHandler, IAudioPlayer *audioPlayer) : fileHandler(fileHandler)
{
    playlists = fileHandler->loadPlaylists(audioPlayer);
}

bool PlaylistManager::addPlaylist(IPlaylist *playlist)
{
    bool success = false;
    std::string name = playlist->getName();
    if (playlists[name] == nullptr)
    {
        playlists[name] = playlist;
        success = true;
    }
    return success;
}

IPlaylist *PlaylistManager::removeExistingPlaylist(std::string playlistName)
{
    IPlaylist *playlist = nullptr;
    std::map<std::string, IPlaylist *>::iterator iterator = playlists.find(playlistName);
    if (iterator != playlists.end())
    {
        playlist = iterator->second;
        playlists.erase(iterator);
    }
    return playlist;
}

IPlaylist *PlaylistManager::getPlaylist(std::string playlistName)
{
    IPlaylist *playlist = nullptr;
    std::map<std::string, IPlaylist *>::iterator iterator = playlists.find(playlistName);
    if (iterator != playlists.end())
    {
        playlist = iterator->second;
    }
    return playlist;
}

const std::map<std::string, IPlaylist *> &PlaylistManager::getAllPlaylists() const
{
    return playlists;
}

PlaylistManager::~PlaylistManager()
{
    fileHandler->savePlaylists(playlists);
    playlists.clear();
}
