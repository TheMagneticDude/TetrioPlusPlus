#pragma once

#include <string>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <mmsystem.h>
#include <windows.h>
#pragma comment(lib, "winmm.lib")
#endif

#if __linux__ && !__ANDROID__
#include <stdlib.h>
#endif

inline void PlayAudioFile(std::string_view path) {
#ifdef _WIN32
    PlaySound(CA2T(path.data()), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
#endif
#if __linux__ && !__ANDROID__
    std::string command = "mplayer ";
    command += path;
    system(command.data());
#endif
}

inline void PlayBackgroundMusic() {
    // Tetris song from internet archive: https://ia902905.us.archive.org/11/items/TetrisThemeMusic/Tetris.mp3
#ifdef _WIN32
    mciSendString(TEXT("open \"TETRIODEP/TetrisBackground.mp3\" type mpegvideo alias Background"), NULL, 0, NULL);
    mciSendString(TEXT("play Background repeat"), NULL, 0, 0);
#endif
#if __linux__ && !__ANDROID__
    std::string command = "mplayer TETRIODEP/TetrisBackground.mp3";
    system(command.data());
#endif
}
