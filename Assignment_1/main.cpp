//// Includes                     //////////////////////////////////////

#include "include/global.h"     // Include the global header file
#include "include/dbf.h"        // Include the database functions header file
#include "include/auth.h"       // Include the authentication header file
#include "include/help.h"       // Include the helper functions header file
#include "include/classes.h"    // Include the classes header file
#include "include/classes.cpp"  // Include the classes implementation file

#define cout std::cout
#define cin std::cin

//// Main Function                //////////////////////////////////////

int main() {

    Sleep(300);
    cout << "Welcome to Car Rental System!!. Working on " << get_platform_name() << " platform." << endl;

    Sleep(1000);
    clearScreen();
    
    God God;
    God.importData();

    User currentUser;

    std::string action;
    cout << "Welcome to CaR-e-MaSyS!\n";
    cout << "Do you want to register or login? (r/l): ";

    std::string role;
    while((action != "r") || (action != "l")) {
        cin >> action;
        if (action == "r") {
            while((role != "c") || (role != "e"))
            {
                cout << "Please select your role: \n 1. Customer (c) \n 2. Employee (e) : ";
                cin >> role;

                clearScreen();
                if(role == "c") {
                    cout << "You have selected Customer role.\n";
                }
                else if(role == "e") {
                    cout << "You have selected Employee role.\n";
                }
                else {
                    cout << "Invalid role! Please select a valid role.\n";
                    continue;
                }
                
                char back;
                cout << "Press (b) to go select another role. Press any other key to continue... "; 
                getchar();
                back = getchar();

                if(back == 'b') {
                    clearScreen(); 
                    continue;
                }
                else break;
            }

            // Registration
            std::string Name, ID, password;
            cout << "Hi! Please Enter your Name: ";
            cin >> Name;

            bool unique_ID = false;
            while(unique_ID == false) {
                cout << "Enter a ID: ";
                cin >> ID;
                
                //check if ID already exists

                if (God.findUser(ID) == true){
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
                God.addUser(newUser);
            }
            else if(role == "e") {
                Employee newUser(Name, ID, password);
                God.addUser(newUser);
            }
           
            break;
        } 
        else if (action == "l") {
            // Login
            bool auth = false;
            std::string ID, password;
            
            while(auth != true) {
                
                cout << "Enter your ID: ";
                cin >> ID;

                cout << "Enter your password: ";
                password = getPassword();

                clearScreen();
                auth = God.login(ID, password);
            }

            currentUser = God.getUser(ID);
            std::string rolee = currentUser.memberType;
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

    God.exportData();
    God.importData();
    
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
                    // currentUser.showAllCars(db);

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
            Sleep(600);
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
            std::string action, view;
            switch (choice) {
                case 1:
                    // View All Cars
                    God.showAllCars();

                    cout << "Press any key to continue... ";
                    getchar();
                    getchar();

                    break;

                case 2:
                    // Modify Cars
                    cout << "Do you want to add, update or delete a car? (a/u/d): ";
                    cin >> action;

                    cout << "Do you want to view all the cars first? (y/n): ";
                    cin >> view;

                    if(view == "y") {
                        God.showAllCars();
                        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                    }

                    if (action == "a") {
                        // Add a car
                        Car car;
                        std::string model, regNo, renterID, renterType, dueDate;
                        float condition;
                        bool isRented;
                        
                        cout << "Enter the car model: ";
                        cin >> model;

                        cout << "Enter the registration number: ";
                        cin >> regNo;

                        cout << "Enter the condition: ";
                        cin >> condition;

                        std::string isR;
                        cout << "Is it rented? (y/n): ";
                        cin >> isR;

                        isRented = (isR == "y") ? true : false;

                        if(isRented) {

                            cout << "Enter the renter's ID: ";
                            cin >> renterID;

                            cout << "Enter the renter type: ";
                            cin >> renterType;

                            cout << "Enter the due date: ";
                            cin >> dueDate;
                        }
                        else {
                            isRented = false;
                            renterID = "";
                            dueDate = "";
                        }

                        car = Car(model, regNo, condition, isRented, renterID, dueDate);

                        cout << "Following are the details of the car you want to add: \n";
                        car.getDetails();

                        cout << "Are you sure you want to add this car? (y/n): ";
                        char confirm;
                        cin >> confirm;

                        if(confirm == 'y') {
                            God.addCar(car);
                        }
                        

                    } else if (action == "u") {
                        // Update a car
                        
                        Car car;
                        std::string regNo, renterID, renterType, dueDate;
                        float condition;
                        bool isRented;
                        std::string act;

                        cout << "Enter the registration number of the car you want to update: ";
                        cin >> regNo;

                        cout << "Do you want to update the condition? (y/n): ";
                        cin >> act;

                        if(act == "y") {
                            cout << "Enter the new condition: ";
                            cin >> condition;
                        }

                        cout << "Do you want to update the renter's details? (y/n): ";
                        cin >> act;

                        if(act == "y") {
                            cout << "Is it still rented? (y/n): ";
                            std::string isR;
                            cin >> isR;

                            if(isR == "y") {
                                isRented = true;

                            cout << "Enter the renter's ID: ";
                            cin >> renterID;

                            cout << "Enter the renter type: ";
                            cin >> renterType;

                            cout << "Enter the due date: ";
                            cin >> dueDate;

                            }
                            else {
                                isRented = false;
                                renterID = "";
                                renterType = "";
                                dueDate = "";
                            }
                        }

                        car = Car(God.getCar(regNo).getModel(), regNo, condition, isRented, renterID, dueDate);
                        God.updateCar(car);

                    } else if (action == "d") {
                        // Delete a car
                        Car car;
                        std::string regNo;

                        cout << "Enter the registration number of the car you want to delete: ";
                        cin >> regNo;

                        cout << "Are you sure you want to delete this car? (y/n): ";
                        char confirm;
                        cin >> confirm;

                        if(confirm == 'y') {
                            God.removeCar(God.getCar(regNo));
                            cout << "Car deleted successfully." << endl;
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

    God.exportData();

    return 0;
}