#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>
#include "Playlist.h"
#include "IPlaylist.h"
#include "IFileHandler.h"
#include "nlohmann_json.hpp"

class FileHandler : public IFileHandler
{
private:
    std::string playlistsFilename;
    std::string songsFilename;

public:
    FileHandler(const std::string &playlistsFile, const std::string songsFile);
    bool fileExists();
    bool savePlaylists(const std::map<std::string, IPlaylist *> &playlistsMap);
    std::map<std::string, IPlaylist *> loadPlaylists(IAudioPlayer *audioPlayer);
    std::vector<nlohmann::json> loadAllAvailableSongs();
};

#endif
