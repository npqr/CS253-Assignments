#ifndef HELP_H
#define HELP_H

//// Helper Functions             //////////////////////////////////////

string getPassword() {
    string password;
    char ch;

    #ifdef _WIN32
        // On Windows, use conio.h functions to hide input
        while ((ch = _getch()) != 13) { // 13 is the Enter key
            if (ch != '\b') {
                cout << '*'; // Print asterisk for each character
                password.push_back(ch);
            } else {
                if (!password.empty()) {
                    cout << "\b \b"; // Move cursor back, erase character, move cursor back again
                    password.pop_back();
                }
            }
        }
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
    cout << "----------------------------------------------\n";
    cout << "\t Car Rental Management System\n";
    cout << "----------------------------------------------\n";
}

#endif // HELP_H