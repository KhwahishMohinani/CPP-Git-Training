#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "menu.h"
#include "constants.h"
#include "IPlaylistManager.h"
#include "IPlaylist.h"
#include "Playlist.h"
#include "IAudioPlayer.h"
#include "IFileHandler.h"
#include "InputHandler.h"
#include "Song.h"

InputHandler inputHandler;

int getValidInt(const std::string &prompt)
{
    std::string input;
    int value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> input;
        if (inputHandler.isValidInt(input, value) && value >= 0)
        {
            return value;
        }
        std::cout << INVALID_INPUT;
    }
}

void createPlaylistMenu(IPlaylistManager *playlistManager, std::vector<IPlaylist *> &allPlaylists, IAudioPlayer *audioPlayer)
{
    std::string playlistName;
    std::cout << ENTER_PLAYLIST_NAME;
    std::cin >> playlistName;

    IPlaylist *playlist = new Playlist(playlistName, audioPlayer);
    if (playlistManager->addPlaylist(playlist))
    {
        allPlaylists.push_back(playlist);
        std::cout << PLAYLIST_CREATION_SUCCESS;
    }
    else
    {
        delete playlist;
        std::cout << PLAYLIST_CREATION_FAILURE;
    }
}

void deleteExistingPlaylistMenu(IPlaylistManager *playlistManager, std::vector<IPlaylist *> &allPlaylists)
{
    std::string playlistName;
    std::cout << ENTER_PLAYLIST_NAME;
    std::cin >> playlistName;

    IPlaylist *playlist = playlistManager->removeExistingPlaylist(playlistName);

    if (playlist)
    {
        std::vector<IPlaylist *>::iterator iterator = std::find(allPlaylists.begin(), allPlaylists.end(), playlist);
        if (iterator != allPlaylists.end())
        {
            delete *iterator;
            allPlaylists.erase(iterator);
        }

        std::cout << PLAYLIST_DELETION_SUCCESS;
    }
    else
    {
        std::cout << PLAYLIST_NOT_FOUND;
    }
}

void showAllPlaylists(IPlaylistManager *playlistManager)
{
    const std::map<std::string, IPlaylist *> &allPlaylists = playlistManager->getAllPlaylists();

    if (allPlaylists.empty())
    {
        std::cout << NO_PLAYLIST_FOUND;
        return;
    }

    std::cout << ALL_PLAYLISTS;
    for (const std::pair<const std::string, IPlaylist *> &pair : allPlaylists)
    {
        std::cout << HYPHEN << pair.first << "\n";
    }
}

void accessExistingPlaylistMenu(IPlaylistManager *playlistManager, IFileHandler *fileHandler)
{
    std::vector<nlohmann::json> allSongs = fileHandler->loadAllAvailableSongs();
    std::string playlistName;
    std::cout << ENTER_PLAYLIST_NAME;
    std::cin >> playlistName;

    IPlaylist *playlist = playlistManager->getPlaylist(playlistName);

    if (playlist == nullptr)
    {
        std::cout << PLAYLIST_NOT_FOUND;
        return;
    }

    int choice;
    do
    {
        std::cout << PLAYLIST_MENU;
        choice = getValidInt("");

        switch (choice)
        {
        case 1:
            showAllSongsInPlaylist(playlist);
            break;
        case 2:
            addSongMenu(playlist, allSongs);
            break;
        case 3:
            removeSongMenu(playlist);
            break;
        case 4:
            playSongMenu(playlist);
            break;
        case 5:
            moveSongMenu(playlist);
            break;
        case 6:
            std::cout << BACK_TO_MAIN_MENU;
            break;
        default:
            std::cout << INVALID_CHOICE;
            break;
        }

    } while (choice != 6);
}
void showAllSongsInPlaylist(IPlaylist *playlist)
{
    if (playlist->getSongs().empty())
    {
        std::cout << NO_SONGS_IN_PLAYLIST;
        return;
    }
    std::cout << SONGS_IN_PLAYLIST << playlist->getName() << "\n";
    for (Song *song : playlist->getSongs())
    {
        std::cout << SONG_NAME << song->getName() << ARTIST_NAME << song->getArtistName() << "\n";
    }
}

void addSongMenu(IPlaylist *playlist, const std::vector<nlohmann::json> &allSongs)
{
    std::cout << AVAILABLE_SONGS;
    for (size_t i = 0; i < allSongs.size(); ++i)
    {
        const nlohmann::json &song = allSongs[i];
        std::cout << i + 1 << SONG_NAME << song[NAME_LABEL] << ARTIST_NAME << song[ARTIST_LABEL] << "\n";
    }

    int songChoice = getValidInt(ENTER_SONG_NUMBER_TO_ADD);

    if (songChoice < 1 || songChoice > allSongs.size())
    {
        std::cout << INVALID_CHOICE;
    }
    else
    {
        const nlohmann::json &songData = allSongs[songChoice - 1];
        Song *newSong = new Song(songData[NAME_LABEL], songData[ARTIST_LABEL], songData[FILE_PATH_LABEL]);

        if (playlist->addSong(newSong))
        {
            std::cout << newSong->getName() << ADD_SONG_SUCCESS << playlist->getName() << "\n";
        }
        else
        {
            std::cout << newSong->getName() << ADD_SONG_FAILURE;
        }
    }
}

void removeSongMenu(IPlaylist *playlist)
{
    if (playlist->getSongs().empty())
    {
        std::cout << EMPTY_PLAYLIST;
        return;
    }
    std::list<Song *> songs = playlist->getSongs();
    std::cout << SONGS_IN_PLAYLIST;
    int index = 1;
    for (Song *song : songs)
    {
        std::cout << index++ << " " << song->getName() << BY << song->getArtistName() << "\n";
    }

    int choice = getValidInt(ENTER_SONG_NUMBER_TO_REMOVE);

    Song *songToDelete = playlist->removeSong(choice - 1);
    if (songToDelete)
    {
        delete songToDelete;
        std::cout << REMOVE_SONG_SUCCESS;
    }
    else
    {
        std::cout << INVALID_CHOICE;
    }
}

void playSongMenu(IPlaylist *playlist)
{
    if (playlist->getSongs().empty())
    {
        std::cout << EMPTY_PLAYLIST;
        return;
    }
    int choice;

    playlist->playCurrentSong();

    do
    {
        std::cout << PLAYER_MENU;
        choice = getValidInt("");

        switch (choice)
        {
        case 1:
            playlist->playCurrentSong();
            break;
        case 2:
            playlist->pause();
            break;
        case 3:
            playlist->stop();
            break;
        case 4:
            playlist->playNextSong();
            break;
        case 5:
            playlist->playPreviousSong();
            break;
        case 6:
            playlist->stop();
            std::cout << EXIT_PLAYER;
            break;
        default:
            std::cout << INVALID_CHOICE;
        }
    } while (choice != 6);
}

void playCurrentSongMenu(IPlaylist *playlist)
{
    int errorCode = playlist->playCurrentSong();
    if (errorCode == PLAY_SONG_SUCCESS_CODE)
    {
        std::cout << NOW_PLAYING << playlist->getCurrentSong()->getName() << BY << playlist->getCurrentSong()->getArtistName() << "\n";
    }
    else if (errorCode == AUDIO_FILE_NOT_AVAILABLE_CODE)
    {
        std::cout << AUDIO_FILE_NOT_AVAILABLE;
    }
    else
    {
        std::cout << NO_SONGS_AVAILABLE;
    }
}

void moveSongMenu(IPlaylist *playlist)
{
    if (playlist->getSongs().empty())
    {
        std::cout << EMPTY_PLAYLIST;
        return;
    }
    const std::list<Song *> &songsList = playlist->getSongs();
    int size = songsList.size();
    if (size < 2)
    {
        std::cout << NOT_ENOUGH_SONGS_TO_MOVE;
        return;
    }

    std::cout << MOVED_SONG;
    int i = 1;
    for (Song *song : songsList)
    {
        std::cout << i << " " << song->getName() << BY << song->getArtistName() << "\n";
        ++i;
    }

    int fromPosition = getValidInt(SONG_NUMBER_TO_MOVE);
    int toPosition = getValidInt(ENTER_NEW_POSITION + std::to_string(size) + BRACKET);
    if (playlist->moveSong(fromPosition, toPosition))
        std::cout << MOVE_SONG_SUCCESS;
    else
        std::cout << INVALID_INPUT_TO_MOVE_SONG;
}
