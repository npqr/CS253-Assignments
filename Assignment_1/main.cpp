//// Includes                     //////////////////////////////////////

#include <include/global.h>     // Include the global header file
#include "include/dbf.h"        // Include the database functions header file
#include "include/auth.h"       // Include the authentication header file
#include "include/help.h"       // Include the helper functions header file
#include "include/user.h"       // Include the user class header file

//// Main Function                //////////////////////////////////////

int main() {
    Sleep(300);
    cout << "Welcome to Car Rental System!!. Working on " << get_platform_name() << " platform." << endl;
    Sleep(1000);
    clearScreen();

    string filename = "db/catDistributionSystem.sqlite3";

    // Check if the database file exists, create it if not
    if (!databaseExists(filename)) {
        cout << "Database file not found. Creating database..." << endl;
        createDatabase(filename);
        // cout << "DBBACKBODI DONE\n";
    }

    // Connect to the SQLite database
    sqlite3* db;
    int rc = sqlite3_open(filename.c_str(), &db);
    if (rc != SQLITE_OK) {
        cerr << "Error opening SQLite database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }

    // Ask the user whether to register or login
    string action;
    cout << "Welcome to CaR-e-MaSyS!\n";
    cout << "Do you want to register or login? (r/l): ";
    while((action != "r") || (action != "l")) {
        cin >> action;
        
        if (action == "r") {
            // Registration
            string Name, ID, password;
            cout << "Hi! Please Enter your Name: ";
            cin >> Name;

            bool unique_ID = false;
            while(unique_ID == false) {
            cout << "Enter a ID: ";
            cin >> ID;
           
            //check if ID already exists
            string query = "SELECT COUNT(*) FROM Users WHERE ID = ?";
            sqlite3_stmt* stmt;
           
            int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
            if (rc != SQLITE_OK) {
                cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
                break;
            }

            sqlite3_bind_text(stmt, 1, ID.c_str(), -1, SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);

            if (count > 0) {
                cerr << "ID '" << ID << "' already exists. Please choose a different ID." << endl;
            }
            else {
                unique_ID = true;
            }
        
            }

            cout << "Create a password: ";
            password = getPassword();

            User newUser(Name, ID, password);
            registerUser(db, newUser);
            break;
        } 
        else if (action == "l") {
            // Login
            bool auth = false;
            
            while(auth != true) {
                
                string ID, password;
                cout << "Enter your ID: ";
                cin >> ID;

                cout << "Enter your password: ";
                password = getPassword();

                clearScreen();
                auth = loginUser(db, ID, password);
            }
            break;
        } 
        else {
            clearScreen();
            cerr << ANSI_COLOR_RED << "Invalid action!\n" << ANSI_COLOR_RESET << "Please choose 'register' or 'login' (type 'r' or 'l'). : ";
        }
    }


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

            clearScreen();
            cout << ANSI_COLOR_RED << "Invalid input. Please try again." << ANSI_COLOR_RESET << endl;
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

                clearScreen();
                cout << ANSI_COLOR_RED << "Invalid choice. Please try again." << ANSI_COLOR_RESET << endl;
        }
    } while (choice != 4);


    // Close the database connection
    sqlite3_close(db);

}