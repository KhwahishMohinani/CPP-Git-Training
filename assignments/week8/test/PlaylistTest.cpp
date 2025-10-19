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

TEST_F(PlaylistTest, WhenAddSongCalledWithNewSong_ThenReturnsTrueAndAddsSong)
{
    EXPECT_TRUE(playlist->addSong(song1));
    EXPECT_EQ(playlist->getSongs().size(), 1);
}

TEST_F(PlaylistTest, WhenAddSongCalledWithDuplicateSong_ThenReturnsFalseAndDoesNotAdd)
{
    playlist->addSong(song1);
    EXPECT_FALSE(playlist->addSong(song1));
    EXPECT_EQ(playlist->getSongs().size(), 1);
}

TEST_F(PlaylistTest, WhenRemoveSongCalledWithValidIndex_ThenRemovesAndReturnsSong)
{
    playlist->addSong(song1);
    playlist->addSong(song2);

    Song *removed = playlist->removeSong(0);
    EXPECT_EQ(removed, song1);
    EXPECT_EQ(playlist->getSongs().size(), 1);
}

TEST_F(PlaylistTest, WhenRemoveSongCalledWithInvalidIndex_ThenReturnsNullAndDoesNotRemove)
{
    playlist->addSong(song1);
    Song *removed = playlist->removeSong(5);
    EXPECT_EQ(removed, nullptr);
    EXPECT_EQ(playlist->getSongs().size(), 1);
}

TEST_F(PlaylistTest, WhenGetCurrentSongCalledOnEmptyPlaylist_ThenReturnsNull)
{
    EXPECT_EQ(playlist->getCurrentSong(), nullptr);
}

TEST_F(PlaylistTest, WhenGetCurrentSongCalledOnNonEmptyPlaylist_ThenReturnsFirstSong)
{
    playlist->addSong(song1);
    EXPECT_EQ(playlist->getCurrentSong(), song1);
}

TEST_F(PlaylistTest, WhenPlayCurrentSongCalledWithSongs_ThenPlaysSongAndReturnsSuccessCode)
{
    playlist->addSong(song1);

    EXPECT_CALL(mockPlayer, load(TEST_SONG_PATH)).WillOnce(testing::Return(true));
    EXPECT_CALL(mockPlayer, play()).Times(1);

    int result = playlist->playCurrentSong();
    EXPECT_EQ(result, PLAY_SONG_SUCCESS_CODE);
}

TEST_F(PlaylistTest, WhenPlayCurrentSongCalledWithNoSongs_ThenReturnsNoSongsCode)
{
    int result = playlist->playCurrentSong();
    EXPECT_EQ(result, NO_SONGS_IN_PLAYLIST_CODE);
}

TEST_F(PlaylistTest, WhenPlayPreviousSongCalledOnEmptyPlaylist_ThenReturnsFalse)
{
    EXPECT_FALSE(playlist->playPreviousSong());
}

TEST_F(PlaylistTest, WhenPlayPreviousSongCalledAtFirstSong_ThenWrapsToLastAndReturnsTrue)
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

TEST_F(PlaylistTest, WhenPauseCalled_ThenCallsAudioPlayerPause)
{
    EXPECT_CALL(mockPlayer, pause()).Times(1);
    playlist->pause();
}

TEST_F(PlaylistTest, WhenPlayNextSongCalledOnEmptyPlaylist_ThenReturnsFalse)
{
    EXPECT_FALSE(playlist->playNextSong());
}

TEST_F(PlaylistTest, WhenPlayNextSongCalledAtLastSong_ThenWrapsToBeginAndReturnsTrue)
{
    playlist->addSong(song1);
    playlist->addSong(song2);

    EXPECT_CALL(mockPlayer, load(TEST_SONG_PATH)).WillOnce(testing::Return(true));
    EXPECT_CALL(mockPlayer, play()).Times(1);

    bool result = playlist->playNextSong();
    EXPECT_TRUE(result);

    EXPECT_EQ(playlist->getCurrentSong(), song1);
}

TEST_F(PlaylistTest, WhenStopCalled_ThenCallsAudioPlayerStop)
{
    EXPECT_CALL(mockPlayer, stop()).Times(1);
    playlist->stop();
}

TEST_F(PlaylistTest, WhenMoveSongCalledWithValidIndices_ThenMovesSongAndReturnsTrue)
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

TEST_F(PlaylistTest, WhenMoveSongCalledWithInvalidIndices_ThenReturnsFalse)
{
    playlist->addSong(song1);
    EXPECT_FALSE(playlist->moveSong(0, 5));
}
