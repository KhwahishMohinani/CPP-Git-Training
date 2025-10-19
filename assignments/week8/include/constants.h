#ifndef CONSTANTS_H
#define CONSTANTS_H

const char MAIN_MENU[] = "-----Music Playlist System-----\n1. Create new playlist\n2. Delete existing playlist\n3. Access existing playlist\n4. Show all playlists\n5. Exit\nEnter your choice: ";
const char PLAYLIST_MENU[] = "-----Playlist-----\n1. Show all songs\n2. Add a song\n3. Remove a song\n4. Play a Song\n5. Move Song\n6. Back to main menu\nEnter your choice: ";
const char ENTER_PLAYLIST_NAME[] = "Enter the playlist name: ";
const char PLAYLIST_CREATION_SUCCESS[] = "Playlist created successfully\n";
const char PLAYLIST_CREATION_FAILURE[] = "Cannot create playlist. A playlist with this name already exists\n";
const char PLAYLIST_DELETION_SUCCESS[] = "Playlist deleted successfully\n";
const char PLAYLIST_NOT_FOUND[] = "Playlist not found\n";
const char EXIT_MSG[] = "Exiting...\n";
const char NO_PLAYLIST_FOUND[] = "No playlists found.\n";
const char ALL_PLAYLISTS[] = "----- All Playlists -----\n";
const char HYPHEN[] = "- ";
const char PLAYLISTS_FILE_PATH[] = "data/playlists.json";
const char SONGS_FILE_PATH[] = "data/songs.json";
const char NO_FILE_LOADED[] = "No playlists loaded (file missing or empty)\n";
const char ENTER_SONG_NAME[] = "Enter song name to add: ";
const char ADD_SONG_SUCCESS[] = "Song added successfully.\n";
const char SAVE_PLAYLIST_FAILED[] = "Failed to save playlists.\n";
const char ERROR_READING_JSON[] = "Error reading JSON: ";
const char INVALID_CHOICE[] = "Invalid choice";
const char BACK_TO_MAIN_MENU[] = "Returning to the main menu...\n";
const char ERROR[] = "Error: ";
const char SONG_EXIST_IN_PLAYLIST[] = " is already in the playlist.\n";
const char ADD_SONG_FAILURE[] = " is already in the playlist\n";
const char AVAILABLE_SONGS[] = "\nAvailable Songs:\n";
const char ENTER_SONG_NUMBER_TO_ADD[] = "\nEnter the number of the song you want to add: ";
const char SONGS_IN_PLAYLIST[] = "Songs in playlist: ";
const char ARTIST_NAME[] = "\tArtist name: ";
const char SONG_NAME[] = " Song name: ";
const char ENTER_SONG_NUMBER_TO_REMOVE[] = "\nEnter the number of the song you want to remove: ";
const char REMOVE_SONG_SUCCESS[] = "Song removed successfully!\n";
const char EXIT_PLAYER[] = "Exiting player...\n";
const char PLAYER_MENU[] = "\n-----Player Controls-----\n1. Play / Resume\n2. Pause\n3. Stop\n4. Next Song\n5. Previous Song\n6. Exit Player\nEnter your choice: ";
const char AUDIO_FILE_NOT_AVAILABLE[] = "Audio file not available for this song\n";
const char NO_SONGS_AVAILABLE[] = "No songs present in the playlist\n";
const char NOW_PLAYING[] = "Now Playing: ";
const char BY[] = " by ";
const char NOT_ENOUGH_SONGS_TO_MOVE[] = "Not enough songs to move.\n";
const char MOVED_SONG[] = "-----Move Song-----\nSongs in playlist:\n";
const char SONG_NUMBER_TO_MOVE[] = "Enter the number of the song you want to move: ";
const char ENTER_NEW_POSITION[] = "Enter the new position (1 to ";
const char BRACKET[] = "): ";
const char MOVE_SONG_SUCCESS[] = "Song moved successfully!\n";
const char INVALID_INPUT_TO_MOVE_SONG[] = "Invalid input. Could not move song.\n";
const char INVALID_INPUT[] = "Invalid Input. Please enter a valid number: ";
const char EMPTY_PLAYLIST[] = "This playlist is empty. Please add songs first.\n";
const char NO_SONGS_IN_PLAYLIST[] = "No songs in this playlist.\n";

const char SONGS_LABEL[] = "songs";
const char NAME_LABEL[] = "name";
const char ARTIST_LABEL[] = "artist";
const char FILE_PATH_LABEL[] = "filepath";

const int NO_SONGS_IN_PLAYLIST_CODE = 1;
const int PLAY_SONG_SUCCESS_CODE = 0;
const int AUDIO_FILE_NOT_AVAILABLE_CODE = 2;

const char TEST_SONG_FILE_PATH[] = "song.mp3";
const char TEST_PLAYLIST_JSON_FILE_PATH[] = "test_playlists.json";
const char TEST_SONGS_JSON_FILE_PATH[] = "test_songs.json";
const char TEST_PLAYLIST_NAME[] = "MyPlaylist1";
const char TEST_PLAYLIST2_NAME[] = "MyPlaylist2";
const char TEST_SONG_NAME[] = "Song1";
const char TEST_ARTIST_NAME[] = "Artist1";
const char TEST_SONG_PATH[] = "song1.mp3";
const char TEST_SONG2_NAME[] = "Song2";
const char TEST_ARTIST2_NAME[] = "Artist2";
const char TEST_SONG2_PATH[] = "song2.mp3";

#endif
