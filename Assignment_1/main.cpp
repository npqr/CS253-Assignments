#include<iostream>
#include<stdlib.h>
using namespace std;

#if defined(_WIN32)
    #define PLATFORM_NAME "Windows" // Windows
#elif defined(_WIN64)
    #define PLATFORM_NAME "Windows" // Windows
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_NAME "Windows" // Windows (Cygwin POSIX under Microsoft Window)
#elif defined(__linux__)
    #define PLATFORM_NAME "Linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX
    #define PLATFORM_NAME "Mac OS" // Apple OSX
#else
    #define PLATFORM_NAME NULL
#endif

const char *get_platform_name() {
    return PLATFORM_NAME;
}
    
int main() {

    cout << "Welcome to Car Rental System!!. Working on " << get_platform_name() << " platform." << endl;
    int choice;
    do {
        // Display menu
        cout << "Car Rental Menu:" << endl;
        cout << "1. List available cars" << endl;
        cout << "2. Rent a car" << endl;
        cout << "3. Return a car" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please try again." << endl;
            continue;
        }

        // Process user's choice
        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;

                system("cls");
        }
    } while (choice != 4);
}