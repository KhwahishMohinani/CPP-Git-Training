#include <gtest/gtest.h>
#include <fstream>
#include "FileHandler.h"
#include "Playlist.h"
#include "Song.h"
#include "IAudioPlayer.h"
#include "MockAudioPlayer.h"
#include "constants.h"

class FileHandlerTest : public ::testing::Test
{
protected:
    std::string playlistsFile = TEST_PLAYLIST_JSON_FILE_PATH;
    std::string songsFile = TEST_SONGS_JSON_FILE_PATH;
    FileHandler *fileHandler;
    MockAudioPlayer mockPlayer;

    void SetUp() override
    {
        fileHandler = new FileHandler(playlistsFile, songsFile);
    }

    void TearDown() override
    {
        delete fileHandler;
        if (std::filesystem::exists(playlistsFile))
        {
            std::filesystem::remove(playlistsFile);
        }
        if (std::filesystem::exists(songsFile))
        {
            std::filesystem::remove(songsFile);
        }
    }
};

TEST_F(FileHandlerTest, WhenFileDoesNotExist_ThenFileExistsReturnsFalse)
{
    EXPECT_FALSE(fileHandler->fileExists());
}

TEST_F(FileHandlerTest, WhenFileExists_ThenFileExistsReturnsTrue)
{
    std::ofstream file(playlistsFile);
    file << "{}";
    file.close();

    EXPECT_TRUE(fileHandler->fileExists());
}

TEST_F(FileHandlerTest, WhenSavePlaylistsCalled_ThenWritesFileAndIncludesPlaylistAndSongData)
{
    Playlist playlist(TEST_PLAYLIST_NAME, &mockPlayer);
    Song song(TEST_SONG_NAME, TEST_ARTIST_NAME, TEST_SONG_PATH);
    playlist.addSong(&song);

    std::map<std::string, IPlaylist *> playlists = {{TEST_PLAYLIST_NAME, &playlist}};

    EXPECT_TRUE(fileHandler->savePlaylists(playlists));
    EXPECT_TRUE(std::filesystem::exists(playlistsFile));

    std::ifstream file(playlistsFile);
    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
    EXPECT_NE(content.find(TEST_PLAYLIST_NAME), std::string::npos);
    EXPECT_NE(content.find(TEST_SONG_NAME), std::string::npos);
}

TEST_F(FileHandlerTest, WhenLoadPlaylistsCalledOnEmptyFile_ThenReturnsEmptyMap)
{
    std::ofstream file(playlistsFile);
    file.close();

    auto playlists = fileHandler->loadPlaylists(&mockPlayer);
    EXPECT_TRUE(playlists.empty());
}

TEST_F(FileHandlerTest, WhenLoadPlaylistsCalledAfterSave_ThenReturnsSavedPlaylistsWithSongs)
{
    Playlist playlist(TEST_PLAYLIST_NAME, &mockPlayer);
    Song song(TEST_SONG_NAME, TEST_ARTIST_NAME, TEST_SONG_PATH);
    playlist.addSong(&song);

    std::map<std::string, IPlaylist *> playlists = {{TEST_PLAYLIST_NAME, &playlist}};
    fileHandler->savePlaylists(playlists);

    std::map<std::string, IPlaylist *> loaded = fileHandler->loadPlaylists(&mockPlayer);
    EXPECT_EQ(loaded.size(), 1);
    IPlaylist *loadedPlaylist = loaded[TEST_PLAYLIST_NAME];
    EXPECT_EQ(loadedPlaylist->getName(), TEST_PLAYLIST_NAME);
    std::list<Song *> songs = loadedPlaylist->getSongs();
    ASSERT_EQ(songs.size(), 1);
    EXPECT_EQ(songs.front()->getName(), TEST_SONG_NAME);
}

TEST_F(FileHandlerTest, WhenLoadAllAvailableSongsCalledOnEmptyFile_ThenReturnsEmptyVector)
{
    std::ofstream file(songsFile);
    file.close();

    std::vector<nlohmann::json> allSongs = fileHandler->loadAllAvailableSongs();
    EXPECT_TRUE(allSongs.empty());
}

TEST_F(FileHandlerTest, WhenLoadAllAvailableSongsCalled_ThenReturnsAllSavedSongs)
{
    nlohmann::json jsonSongs = {
        {SONGS_LABEL, {{{NAME_LABEL, TEST_SONG_NAME}, {ARTIST_LABEL, TEST_ARTIST_NAME}, {FILE_PATH_LABEL, TEST_SONG_PATH}}, {{NAME_LABEL, TEST_SONG2_NAME}, {ARTIST_LABEL, TEST_ARTIST2_NAME}, {FILE_PATH_LABEL, TEST_SONG2_PATH}}}}};

    std::ofstream file(songsFile);
    file << jsonSongs.dump(4);
    file.close();

    std::vector<nlohmann::json> allSongs = fileHandler->loadAllAvailableSongs();
    EXPECT_EQ(allSongs.size(), 2);
    EXPECT_EQ(allSongs[0][NAME_LABEL], TEST_SONG_NAME);
    EXPECT_EQ(allSongs[1][ARTIST_LABEL], TEST_ARTIST2_NAME);
}
