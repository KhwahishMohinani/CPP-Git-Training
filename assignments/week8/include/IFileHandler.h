#ifndef I_FILE_HANDLER_H
#define I_FILE_HANDLER_H

#include <vector>
#include <map>
#include <string>
#include "IPlaylist.h"
#include "nlohmann_json.hpp"

class IAudioPlayer;

class IFileHandler
{
public:
    virtual bool fileExists() = 0;
    virtual bool savePlaylists(const std::map<std::string, IPlaylist *> &playlistsMap) = 0;
    virtual std::map<std::string, IPlaylist *> loadPlaylists(IAudioPlayer *audioPlayer) = 0;
    virtual std::vector<nlohmann::json> loadAllAvailableSongs() = 0;
    virtual ~IFileHandler() {};
};

#endif
