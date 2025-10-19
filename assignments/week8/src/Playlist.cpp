#include "IAudioPlayer.h"
#include "Playlist.h"
#include "constants.h"

Playlist::Playlist(std::string playlistName, IAudioPlayer *player)
    : name(playlistName), audioPlayer(player)
{
    currentSong = songs.end();
}

std::string Playlist::getName()
{
    return name;
}

std::list<Song *> Playlist::getSongs()
{
    return songs;
}

bool Playlist::addSong(Song *song)
{
    for (Song *existingSong : songs)
    {
        if (existingSong->getName() == song->getName())
        {
            return false;
        }
    }

    songs.push_back(song);
    return true;
}

Song *Playlist::removeSong(int index)
{
    Song *removedSong = nullptr;
    if (index >= 0 && index < songs.size())
    {
        std::list<Song *>::iterator iterator = songs.begin();
        std::advance(iterator, index);
        removedSong = *iterator;
        songs.erase(iterator);
    }
    return removedSong;
}

Song *Playlist::getCurrentSong()
{
    Song *song = nullptr;
    if (!songs.empty())
    {
        if (currentSong == songs.end())
        {
            currentSong = songs.begin();
        }
        song = *currentSong;
    }
    return song;
}

int Playlist::playCurrentSong()
{
    Song *song = getCurrentSong();
    if (!song)
        return NO_SONGS_IN_PLAYLIST_CODE;

    if (currentPlayingSong != song)
    {
        if (!audioPlayer->load(song->getFilePath()))
            return AUDIO_FILE_NOT_AVAILABLE_CODE;

        currentPlayingSong = song;
    }

    audioPlayer->play();
    return PLAY_SONG_SUCCESS_CODE;
}

bool Playlist::playNextSong()
{
    bool success = false;

    if (!songs.empty())
    {
        if (currentSong == songs.end())
            currentSong = songs.begin();
        else
        {
            ++currentSong;
            if (currentSong == songs.end())
                currentSong = songs.begin();
        }

        success = (playCurrentSong() == PLAY_SONG_SUCCESS_CODE);
    }

    return success;
}

bool Playlist::playPreviousSong()
{
    bool success = false;

    if (!songs.empty())
    {
        if (currentSong == songs.end() || currentSong == songs.begin())
            currentSong = std::prev(songs.end());
        else
            --currentSong;

        success = (playCurrentSong() == PLAY_SONG_SUCCESS_CODE);
    }

    return success;
}

void Playlist::pause()
{
    audioPlayer->pause();
}

void Playlist::stop()
{
    audioPlayer->stop();
}

bool Playlist::moveSong(int fromIndex, int toIndex)
{
    bool success = true;
    int size = songs.size();

    if (fromIndex < 1 || fromIndex > size || toIndex < 1 || toIndex > size)
        success = false;
    else if (fromIndex != toIndex)
    {
        std::list<Song *>::iterator iteratorFromPosition = songs.begin();
        std::advance(iteratorFromPosition, fromIndex - 1);
        Song *songToMove = *iteratorFromPosition;
        songs.erase(iteratorFromPosition);

        std::list<Song *>::iterator iteratorToPosition = songs.begin();
        std::advance(iteratorToPosition, toIndex - 1);
        songs.insert(iteratorToPosition, songToMove);

        if (currentSong == iteratorFromPosition)
            currentSong = iteratorToPosition;
    }

    return success;
}
