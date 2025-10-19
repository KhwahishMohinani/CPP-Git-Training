#include <gtest/gtest.h>
#include "Song.h"
#include "constants.h"

class SongTest : public ::testing::Test
{
protected:
    Song *song;

    void SetUp() override
    {
        song = new Song(TEST_SONG_NAME, TEST_ARTIST_NAME, TEST_SONG_PATH);
    }

    void TearDown() override
    {
        delete song;
    }
};

TEST_F(SongTest, WhenGetNameCalled_ThenReturnsCorrectValue)
{
    EXPECT_EQ(song->getName(), TEST_SONG_NAME);
}

TEST_F(SongTest, WhenGetArtistNameCalled_ThenReturnsCorrectValue)
{
    EXPECT_EQ(song->getArtistName(), TEST_ARTIST_NAME);
}

TEST_F(SongTest, WhenGetFilePathCalled_ThenReturnsCorrectValue)
{
    EXPECT_EQ(song->getFilePath(), TEST_SONG_PATH);
}
