#include <iostream>
#include "menu.h"
#include "constants.h"
#include "IPlaylistManager.h"
#include "PlaylistManager.h"
#include "FileHandler.h"
#include "AudioPlayer.h"

int main()
{
    IFileHandler *fileHandler = new FileHandler(PLAYLISTS_FILE_PATH, SONGS_FILE_PATH);
    IAudioPlayer *audioPlayer = new AudioPlayer();
    IPlaylistManager *playlistManager = new PlaylistManager(fileHandler, audioPlayer);

    if (!fileHandler->fileExists())
    {
        std::cout << NO_FILE_LOADED;
    }

    std::vector<IPlaylist *> allPlaylists;
    int choice;
    do
    {
        std::cout << MAIN_MENU;
        choice = getValidInt("");

        switch (choice)
        {
        case 1:
            createPlaylistMenu(playlistManager, allPlaylists, audioPlayer);
            break;
        case 2:
            deleteExistingPlaylistMenu(playlistManager, allPlaylists);
            break;
        case 3:
            accessExistingPlaylistMenu(playlistManager, fileHandler);
            break;
        case 4:
            showAllPlaylists(playlistManager);
            break;
        case 5:
            std::cout << EXIT_MSG;
            break;
        default:
            std::cout << INVALID_CHOICE;
            break;
        }
    } while (choice != 5);

    delete playlistManager;
    for (IPlaylist *playlist : allPlaylists)
    {
        delete playlist;
    }
    allPlaylists.clear();

    delete fileHandler;
    delete audioPlayer;

    return 0;
}
