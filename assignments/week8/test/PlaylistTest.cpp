#include "Playlist.h"
#include "IAudioPlayer.h"
#include "MockAudioPlayer.h"
#include "constants.h"
#include <gtest/gtest.h>

class PlaylistTest : public ::testing::Test
{
protected:
    MockAudioPlayer mockPlayer;
    Playlist *playlist;
    Song *song1;
    Song *song2;

    void SetUp() override
    {
        playlist = new Playlist(TEST_PLAYLIST_NAME, &mockPlayer);
        song1 = new Song(TEST_SONG_NAME, TEST_ARTIST_NAME, TEST_SONG_PATH);
        song2 = new Song(TEST_SONG2_NAME, TEST_ARTIST2_NAME, TEST_SONG2_PATH);
    }

    void TearDown() override
    {
        delete playlist;
        delete song1;
        delete song2;
    }
};

TEST_F(PlaylistTest, AddSongSuccess)
{
    EXPECT_TRUE(playlist->addSong(song1));
    EXPECT_EQ(playlist->getSongs().size(), 1);
}

TEST_F(PlaylistTest, AddSongDuplicateFails)
{
    playlist->addSong(song1);
    EXPECT_FALSE(playlist->addSong(song1));
    EXPECT_EQ(playlist->getSongs().size(), 1);
}

TEST_F(PlaylistTest, RemoveSongValidIndex)
{
    playlist->addSong(song1);
    playlist->addSong(song2);

    Song *removed = playlist->removeSong(0);
    EXPECT_EQ(removed, song1);
    EXPECT_EQ(playlist->getSongs().size(), 1);
}

TEST_F(PlaylistTest, RemoveSongInvalidIndex)
{
    playlist->addSong(song1);
    Song *removed = playlist->removeSong(5);
    EXPECT_EQ(removed, nullptr);
    EXPECT_EQ(playlist->getSongs().size(), 1);
}

TEST_F(PlaylistTest, GetCurrentSongEmptyPlaylist)
{
    EXPECT_EQ(playlist->getCurrentSong(), nullptr);
}

TEST_F(PlaylistTest, GetCurrentSongNonEmptyPlaylist)
{
    playlist->addSong(song1);
    EXPECT_EQ(playlist->getCurrentSong(), song1);
}

TEST_F(PlaylistTest, PlayCurrentSongSuccess)
{
    playlist->addSong(song1);

    EXPECT_CALL(mockPlayer, load(TEST_SONG_PATH)).WillOnce(testing::Return(true));
    EXPECT_CALL(mockPlayer, play()).Times(1);

    int result = playlist->playCurrentSong();
    EXPECT_EQ(result, PLAY_SONG_SUCCESS_CODE);
}

TEST_F(PlaylistTest, PlayCurrentSongNoSongs)
{
    int result = playlist->playCurrentSong();
    EXPECT_EQ(result, NO_SONGS_IN_PLAYLIST_CODE);
}

TEST_F(PlaylistTest, PlayPreviousSongEmptyPlaylistReturnsFalse)
{
    EXPECT_FALSE(playlist->playPreviousSong());
}

TEST_F(PlaylistTest, PlayPreviousSongCurrentAtBegin_WrapsToLast)
{
    playlist->addSong(song1);
    playlist->addSong(song2);

    EXPECT_CALL(mockPlayer, load(TEST_SONG_PATH)).WillOnce(testing::Return(true));
    EXPECT_CALL(mockPlayer, play()).Times(1);
    playlist->playCurrentSong();

    EXPECT_CALL(mockPlayer, load(TEST_SONG2_PATH)).WillOnce(testing::Return(true));
    EXPECT_CALL(mockPlayer, play()).Times(1);

    bool result = playlist->playPreviousSong();
    EXPECT_TRUE(result);
    EXPECT_EQ(playlist->getCurrentSong(), song2);
}

TEST_F(PlaylistTest, PauseCallsAudioPlayerPause)
{
    EXPECT_CALL(mockPlayer, pause()).Times(1);
    playlist->pause();
}

TEST_F(PlaylistTest, PlayNextSongEmptyPlaylistReturnsFalse)
{
    EXPECT_FALSE(playlist->playNextSong());
}

TEST_F(PlaylistTest, PlayNextSongCurrentAtEnd_WrapsToBegin)
{
    playlist->addSong(song1);
    playlist->addSong(song2);

    EXPECT_CALL(mockPlayer, load(TEST_SONG_PATH)).WillOnce(testing::Return(true));
    EXPECT_CALL(mockPlayer, play()).Times(1);

    bool result = playlist->playNextSong();
    EXPECT_TRUE(result);

    EXPECT_EQ(playlist->getCurrentSong(), song1);
}

TEST_F(PlaylistTest, StopCallsAudioPlayerStop)
{
    EXPECT_CALL(mockPlayer, stop()).Times(1);
    playlist->stop();
}

TEST_F(PlaylistTest, MoveSongValid)
{
    playlist->addSong(song1);
    playlist->addSong(song2);

    EXPECT_TRUE(playlist->moveSong(1, 2));

    std::list<Song *> songs = playlist->getSongs();
    std::list<Song *>::iterator iterator = songs.begin();
    EXPECT_EQ(*iterator, song2);
    ++iterator;
    EXPECT_EQ(*iterator, song1);
}

TEST_F(PlaylistTest, MoveSongInvalid)
{
    playlist->addSong(song1);
    EXPECT_FALSE(playlist->moveSong(0, 5));
}
