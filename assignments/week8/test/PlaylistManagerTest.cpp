#include "PlaylistManager.h"
#include "MockPlaylist.h"
#include "MockFileHandler.h"
#include "MockAudioPlayer.h"
#include "constants.h"

class PlaylistManagerTest : public ::testing::Test
{
protected:
    MockFileHandler mockFileHandler;
    MockAudioPlayer mockAudioPlayer;
    PlaylistManager *manager;
    MockPlaylist *playlist1;
    MockPlaylist *playlist2;

    void SetUp() override
    {
        EXPECT_CALL(mockFileHandler, loadPlaylists(&mockAudioPlayer))
            .WillOnce(testing::Return(std::map<std::string, IPlaylist *>{}));

        manager = new PlaylistManager(&mockFileHandler, &mockAudioPlayer);

        playlist1 = new MockPlaylist();
        playlist2 = new MockPlaylist();

        ON_CALL(*playlist1, getName()).WillByDefault(testing::Return(TEST_PLAYLIST_NAME));
        ON_CALL(*playlist2, getName()).WillByDefault(testing::Return(TEST_PLAYLIST2_NAME));
    }

    void TearDown() override
    {
        delete manager;
        delete playlist1;
        delete playlist2;
    }
};

TEST_F(PlaylistManagerTest, AddPlaylistSuccess)
{
    EXPECT_TRUE(manager->addPlaylist(playlist1));
    EXPECT_EQ(manager->getAllPlaylists().size(), 1);
}

TEST_F(PlaylistManagerTest, AddPlaylistDuplicateFails)
{
    manager->addPlaylist(playlist1);
    EXPECT_FALSE(manager->addPlaylist(playlist1));
}

TEST_F(PlaylistManagerTest, RemoveExistingPlaylistSuccess)
{
    manager->addPlaylist(playlist1);
    IPlaylist *removed = manager->removeExistingPlaylist(TEST_PLAYLIST_NAME);
    EXPECT_EQ(removed, playlist1);
}

TEST_F(PlaylistManagerTest, GetPlaylistExists)
{
    manager->addPlaylist(playlist1);
    IPlaylist *p = manager->getPlaylist(TEST_PLAYLIST_NAME);
    EXPECT_EQ(p, playlist1);
}
