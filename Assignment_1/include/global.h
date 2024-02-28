#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

#define cout std::cout
#define cin std::cin
#define endl std::endl
#define ifstream std::ifstream
#define ofstream std::ofstream
#define cerr std::cerr

#define fi first
#define se second

//// Environment Detection      //////////////////////////////////////

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    #define PLATFORM_NAME "Windows" // Windows
    #define CLEAR_SCREEN "cls"
    #include <conio.h>
    #include <windows.h>
#elif defined(__linux__)
    #define PLATFORM_NAME "Linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
    #define CLEAR_SCREEN "clear"
    #include <termios.h>
    #include <unistd.h>
#elif defined(__APPLE__) && defined(__MACH__) // Support still needed to be added
    #define PLATFORM_NAME "Mac OS" // Apple OSX
#else
    #define PLATFORM_NAME NULL
#endif

const char *get_platform_name() {
    return PLATFORM_NAME;
}

//// Ansi Color Codes           //////////////////////////////////////

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#endif // GLOBAL_H