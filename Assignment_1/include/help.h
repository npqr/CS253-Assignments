#ifndef HELP_H
#define HELP_H

//// Helper Functions             //////////////////////////////////////
#include "global.h"

std::string getPassword() {
    std::string password;
    char ch;

    #ifdef _WIN32
        // On Windows, use conio.h functions to hide input
        while ((ch = _getch()) != 13) { // 13 is the Enter key
            if (ch != '\b') {
                cout << ANSI_COLOR_FG_YELLOW << '*'; // Print asterisk for each character
                password.push_back(ch);
            } else {
                if (!password.empty()) {
                    cout << "\b \b"; // Move cursor back, erase character, move cursor back again
                    password.pop_back();
                }
            }
        }
        cout << ANSI_COLOR_RESET << endl;
    #else
        // On Unix-like systems, use termios.h to hide input
        termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        termios newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // Turn off canonical mode and echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        while ((ch = getchar()) != '\n') { // Read characters until Enter is pressed
            cout << '*'; // Print asterisk for each character
            password.push_back(ch);
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore terminal settings
    #endif

    cout << endl;
    return password;
}

void clearScreen() {
    system(CLEAR_SCREEN);                                   
                                
    cout << ANSI_COLOR_FG_RED << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n" << ANSI_COLOR_FG_GREEN;
    cout << "::    _________ _________  ____ ___  ____ ________  _______   ::\n";
    cout << "::   / ___/ __ `/ ___/ _ \\/ __ `__ \\/ __ `/ ___/ / / / ___/   ::\n";
    cout << "::  / /__/ /_/ / /  /  __/ / / / / / /_/ (__  / /_/ (__  )    ::\n";
    cout << "::  \\___/\\__,_/_/   \\___/_/ /_/ /_/\\__,_/____/\\__, /____/     ::\n";
    cout << "::                                           /____/           ::\n";
    cout << "::                                                            ::\n";
    cout << ANSI_COLOR_FG_RED << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n" << ANSI_COLOR_RESET;
    cout << endl;
    
}

void pak2c() {
    cout << "Press any key to continue... ";
    getchar();
    getchar();
}

#endif // HELP_H