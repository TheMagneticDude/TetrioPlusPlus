#pragma once

#include <string>

#ifdef _WIN32
#include <windows.h>
// This needs to come after windows.h
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif

#if __linux__ && !__ANDROID__
#include <linux/prctl.h>
#include <signal.h>
#include <sys/prctl.h>
#include <unistd.h>
#endif

inline void PlayAudioFile(std::string_view path) {
#ifdef _WIN32
    PlaySoundA(path.data(), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
#endif
#if __linux__ && !__ANDROID__
    std::string command = "mplayer ";
    command += path;
    command += " &";
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
    pid_t childPid = fork();
    if (childPid == 0) {
        prctl(PR_SET_PDEATHSIG, SIGHUP);
        execlp("/usr/bin/mplayer", "mplayer", "TETRIODEP/TetrisBackground.mp3", NULL);
        exit(0);
    }
#endif
}
