#ifndef MENU_H
#define MENU_H

#include "nlohmann_json.hpp"

class IPlaylistManager;
class IFileHandler;
class IPlaylist;
class IAudioPlayer;

void createPlaylistMenu(IPlaylistManager *playlistManager, std::vector<IPlaylist *> &allPlaylists, IAudioPlayer *audioPlayer);
void deleteExistingPlaylistMenu(IPlaylistManager *playlistManager, std::vector<IPlaylist *> &allPlaylists);
void accessExistingPlaylistMenu(IPlaylistManager *playlistManager, IFileHandler *filehandler);
void showAllPlaylists(IPlaylistManager *playlistManager);
void playSongMenu(IPlaylist *playlist);
void removeSongMenu(IPlaylist *playlist);
void addSongMenu(IPlaylist *playlist, const std::vector<nlohmann::json> &allSongs);
void showAllSongsInPlaylist(IPlaylist *playlist);
void moveSongMenu(IPlaylist *playlist);
void playCurrentSongMenu(IPlaylist *playlist);
int getValidInt(const std::string &prompt);

#endif
