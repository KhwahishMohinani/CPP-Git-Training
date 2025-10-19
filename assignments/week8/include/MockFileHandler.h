#ifndef MOCK_FILE_HANDLER_H
#define MOCK_FILE_HANDLER_H

#include "IFileHandler.h"
#include <gmock/gmock.h>
#include <map>
#include <vector>
#include <string>
#include "nlohmann_json.hpp"

class MockFileHandler : public IFileHandler
{
public:
    MOCK_METHOD((std::map<std::string, IPlaylist *>), loadPlaylists, (IAudioPlayer * audioPlayer), (override));
    MOCK_METHOD(bool, savePlaylists, ((const std::map<std::string, IPlaylist *> &playlistsMap)), (override));
    MOCK_METHOD(bool, fileExists, (), (override));
    MOCK_METHOD(std::vector<nlohmann::json>, loadAllAvailableSongs, (), (override));
};

#endif
