#ifndef MOCK_PLAYLIST_H
#define MOCK_PLAYLIST_H

#include "IPlaylist.h"
#include <gmock/gmock.h>

class MockPlaylist : public IPlaylist
{
public:
    MOCK_METHOD(std::string, getName, ());
    MOCK_METHOD(std::list<Song *>, getSongs, ());
    MOCK_METHOD(bool, addSong, (Song * song));
    MOCK_METHOD(Song *, removeSong, (int index));
    MOCK_METHOD(Song *, getCurrentSong, ());
    MOCK_METHOD(int, playCurrentSong, ());
    MOCK_METHOD(bool, playNextSong, ());
    MOCK_METHOD(bool, playPreviousSong, ());
    MOCK_METHOD(void, pause, ());
    MOCK_METHOD(void, stop, ());
    MOCK_METHOD(bool, moveSong, (int fromIndex, int toIndex));
};

#endif
