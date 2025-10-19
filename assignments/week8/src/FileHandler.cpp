#include "FileHandler.h"
#include "nlohmann_json.hpp"
#include "constants.h"
#include "AudioPlayer.h"
#include <fstream>
#include <iostream>

FileHandler::FileHandler(const std::string &playlistsFile, const std::string songsFile)
    : playlistsFilename(playlistsFile), songsFilename(songsFile)
{
}

bool FileHandler::savePlaylists(const std::map<std::string, IPlaylist *> &playlistsMap)
{
    nlohmann::json jsonRoot = nlohmann::json::array();

    for (const std::pair<std::string, IPlaylist *> &pair : playlistsMap)
    {
        IPlaylist *playlist = pair.second;
        nlohmann::json jsonPlaylist;
        jsonPlaylist[NAME_LABEL] = playlist->getName();
        jsonPlaylist[SONGS_LABEL] = nlohmann::json::array();

        for (Song *song : playlist->getSongs())
        {
            nlohmann::json jsonSong = {
                {NAME_LABEL, song->getName()},
                {ARTIST_LABEL, song->getArtistName()},
                {FILE_PATH_LABEL, song->getFilePath()}};
            jsonPlaylist[SONGS_LABEL].push_back(jsonSong);
        }

        jsonRoot.push_back(jsonPlaylist);
    }

    std::ofstream file(playlistsFilename);
    if (!file.is_open())
        return false;

    file << jsonRoot.dump(4);
    return true;
}

bool FileHandler::fileExists()
{
    bool success = false;
    std::fstream file(playlistsFilename);
    if (file.is_open())
    {
        success = true;
        file.close();
    }
    return success;
}

std::map<std::string, IPlaylist *> FileHandler::loadPlaylists(IAudioPlayer *audioPlayer)
{
    std::map<std::string, IPlaylist *> playlistsMap;
    std::ifstream file(playlistsFilename);

    if (!file.is_open() || file.peek() == std::ifstream::traits_type::eof())
        return playlistsMap;

    nlohmann::json jsonRoot;
    file >> jsonRoot;

    for (nlohmann::json &jsonPlaylist : jsonRoot)
    {
        std::string name = jsonPlaylist[NAME_LABEL];
        IPlaylist *playlist = new Playlist(name, audioPlayer);

        for (nlohmann::json &jsonSong : jsonPlaylist[SONGS_LABEL])
        {
            Song *song = new Song(
                jsonSong[NAME_LABEL],
                jsonSong[ARTIST_LABEL],
                jsonSong[FILE_PATH_LABEL]);
            playlist->addSong(song);
        }

        playlistsMap[name] = playlist;
    }

    return playlistsMap;
}

std::vector<nlohmann::json> FileHandler::loadAllAvailableSongs()
{
    std::vector<nlohmann::json> allSongs;
    std::ifstream file(songsFilename);
    if (file.is_open() && file.peek() != std::ifstream::traits_type::eof())
    {
        nlohmann::json jsonRoot;
        file >> jsonRoot;
        file.close();

        if (jsonRoot.contains(SONGS_LABEL))
        {
            allSongs = jsonRoot[SONGS_LABEL].get<std::vector<nlohmann::json>>();
        }
    }
    return allSongs;
}
