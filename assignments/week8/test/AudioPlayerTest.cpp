#include "AudioPlayer.h"
#include "MockMusic.h"
#include "constants.h"
#include <gtest/gtest.h>

class AudioPlayerTest : public ::testing::Test
{
protected:
    MockMusic *mockMusic;
    AudioPlayer *player;

    void SetUp() override
    {
        mockMusic = new MockMusic();
        player = new AudioPlayer(mockMusic);
    }

    void TearDown() override
    {
        delete player;
    }
};

TEST_F(AudioPlayerTest, WhenLoadCalledWithValidFilePath_ThenReturnsTrue)
{
    EXPECT_CALL(*mockMusic, openFromFile(TEST_SONG_FILE_PATH))
        .WillOnce(testing::Return(true));

    bool result = player->load(TEST_SONG_FILE_PATH);
    EXPECT_TRUE(result);
}

TEST_F(AudioPlayerTest, WhenLoadCalledWithInvalidFilePath_ThenReturnsFalse)
{
    EXPECT_CALL(*mockMusic, openFromFile(TEST_SONG_FILE_PATH))
        .WillOnce(testing::Return(false));

    bool result = player->load(TEST_SONG_FILE_PATH);
    EXPECT_FALSE(result);
}
