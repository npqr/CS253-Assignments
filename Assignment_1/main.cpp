//// Includes                     //////////////////////////////////////

#include "include/global.h"     // Include the global header file
#include "include/dbf.h"        // Include the database functions header file
#include "include/auth.h"       // Include the authentication header file
#include "include/help.h"       // Include the helper functions header file
#include "include/classes.h"    // Include the classes header file
#include "include/classes.cpp"  // Include the classes implementation file

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

    User currentUser;

    // Ask the user whether to register or login
    string action;
    cout << "Welcome to CaR-e-MaSyS!\n";
    cout << "Do you want to register or login? (r/l): ";

    string role;
    while((action != "r") || (action != "l")) {
        cin >> action;
        if (action == "r") {
            while((role != "c") || (role != "e") || (role != "m"))
            {
                cout << "Please select your role: \n 1. Customer (c) \n 2. Employee (e) \n 3. Manager (m) : ";
                cin >> role;

                if(role == "c") {
                    cout << "You have selected Customer role.\n";
                }
                else if(role == "e") {
                    cout << "You have selected Employee role.\n";
                }
                else if(role == "m") {
                    cout << "You have selected Manager role.\n";
                }
                else {
                    clearScreen();
                    cout << "Invalid role! Please select a valid role.\n";
                    continue;
                }
                
                char back;
                cout << "Press (b) to go select another role. Press any other key to continue... " << endl; 
                getchar();
                back = getchar();

                if(back == 'b') {
                    clearScreen(); 
                    continue;
                    }
                else break;
            }

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

            if(role == "c") {
                Customer newUser(Name, ID, password);
                registerUser(db, newUser);
            }
            else if(role == "e") {
                Employee newUser(Name, ID, password);
                registerUser(db, newUser);
            }
            else if(role == "m") {
                Manager newUser(Name, ID, password);
                registerUser(db, newUser);
            }
           
            break;
        } 
        else if (action == "l") {
            // Login
            bool auth = false;
            string ID, password;
            
            while(auth != true) {
                
                cout << "Enter your ID: ";
                cin >> ID;

                cout << "Enter your password: ";
                password = getPassword();

                clearScreen();
                auth = loginUser(db, ID, password);
            }

            currentUser.fetchDB(db, ID);
            string rolee = currentUser.memberType;
            if(rolee == "Customer")
                role = "c";
            else if(rolee == "Employee")
                role = "e";
            else if(rolee == "Manager") 
                role = "m";

            cout << "You have successfully logged in as a " << rolee << "!\n";

            break;
        } 
        else {
            clearScreen();
            cerr << ANSI_COLOR_RED << "Invalid action!\n" << ANSI_COLOR_RESET << "Please choose 'register' or 'login' (type 'r' or 'l'). : ";
        }
    }

    // Main menu

    if(role == "c" || role == "e") {
        int choice;
        do {
            // Display menu

            // what should a typical customer menu for car rental system look like?
            Sleep(1000);
            clearScreen();
            currentUser.getDetails();

            cout << "Welcome to the " << role << " Menu!" << endl;
            cout << "Please select an option: " << endl;

            cout << "1. Browse & Rent" << endl;
            cout << "3. View rented cars" << endl;
            cout << "2. Return a car" << endl;
            cout << "4. View dues" << endl;
            cout << "5. Exit" << endl;

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
                    // Browse & Rent
                    
                    cout << "All cars available : " << endl;
                    currentUser.showAllCars(db);

                    cout << "this is alllfdsfsdfdsfdsfdsfsdfdsf\n";
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    cout << "Exiting program." << endl;
                    break;
                default:

                    clearScreen();
                    cout << ANSI_COLOR_RED << "Invalid choice. Please try again." << ANSI_COLOR_RESET << endl;
            }
        } while (choice != 4);
    }
    else if(role == "m") {
        Manager currManager(currentUser.getName(), currentUser.getID(), currentUser.getPassword());

        int choice;
        do {
            // Display menu
            Sleep(1000);
            clearScreen();

            cout << "Welcome to the Manager Menu!" << endl;
            cout << "Please select an option: " << endl;

            cout << "1. View All Cars" << endl;
            cout << "2. Modify Cars (add/update/delete)" << endl;
            cout << "3. Modify Customers (add/update/delet)" << endl;
            cout << "4. Modify Employees (add/update/delete)" << endl;
            cout << "5. Exit" << endl;

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
            string action;
            switch (choice) {
                case 1:
                    // View All Cars
                    currManager.showAllCars(db); 
                    break;
                case 2:
                    // Modify Cars
                    cout << "Do you want to add, update or delete a car? (a/u/d): ";
                    cin >> action;

                    if (action == "a") {
                        // Add a car
                        Car car;

                        cout << "Enter the car model: ";
                        cin >> car.model;

                        cout << "Enter the registration number: ";
                        cin >> car.regNo;

                        cout << "Enter the condition: ";
                        cin >> car.condition;

                        char isRented;
                        cout << "Is it rented? (y/n): ";
                        cin >> isRented;

                        if(isRented == 'y') {
                            car.isRented = true;

                            cout << "Enter the renter's ID: ";
                            cin >> car.renterID;

                            cout << "Enter the renter type: ";
                            cin >> car.renterType;

                            cout << "Enter the due date: ";
                            cin >> car.dueDate;
                        }
                        else {
                            car.isRented = false;

                            car.renterID = "";
                            car.renterType = "";
                            car.dueDate = "";
                        }

                        cout << "Following are the details of the car you want to add: \n";
                        car.getDetails();

                        cout << "Are you sure you want to add this car? (y/n): ";
                        char confirm;
                        cin >> confirm;

                        if(confirm == 'y') {
                            currManager.addCar(db, car);
                        }
                        

                    } else if (action == "u") {
                        // Update a car
                        
                        Car car;

                        cout << "Enter the registration number of the car you want to update: ";
                        cin >> car.regNo;

                        cout << "Enter the new condition: ";
                        cin >> car.condition;

                        cout << "Do you want to update the renter's details? (y/n): ";
                        char updateRenter;
                        cin >> updateRenter;

                        if(updateRenter == 'y') {
                            cout << "Is it still rented? (y/n): ";
                            char isRented;
                            cin >> isRented;

                            if(isRented == 'y') {
                                car.isRented = true;

                            cout << "Enter the renter's ID: ";
                            cin >> car.renterID;

                            cout << "Enter the renter type: ";
                            cin >> car.renterType;

                            cout << "Enter the due date: ";
                            cin >> car.dueDate;
                            }
                            else {
                                car.isRented = false;

                                car.renterID = "";
                                car.renterType = "";
                                car.dueDate = "";
                            }
                        }

                        currManager.updateCar(db, car);
                    } else if (action == "d") {
                        // Delete a car
                        Car car;

                        cout << "Enter the registration number of the car you want to delete: ";
                        cin >> car.regNo;

                        cout << "Are you sure you want to delete this car? (y/n): ";
                        char confirm;
                        cin >> confirm;

                        if(confirm == 'y') {
                            car.fetchDB(db);
                            car.getDetails();
                            currManager.removeCar(db, car);
                        }
                        

                    } else {
                        clearScreen();
                        cout << ANSI_COLOR_RED << "Invalid action. Please try again." << ANSI_COLOR_RESET << endl;
                    }

                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    cout << "Exiting program." << endl;
                    break;
                default:

                    clearScreen();
                    cout << ANSI_COLOR_RED << "Invalid choice. Please try again." << ANSI_COLOR_RESET << endl;
            }
        } while (choice != 5);
    }

    // Close the database connection
    sqlite3_close(db);

}