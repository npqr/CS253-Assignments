//// Includes                       //////////////////////////////////////

#include "include/classes.cpp"  // Include the classes implementation file
#include "include/classes.hpp"  // Include the classes header file
#include "include/dbf.hpp"      // Include the database functions header file
#include "include/global.hpp"   // Include the global header file
#include "include/help.hpp"     // Include the helper functions header file

//// Login Function                 //////////////////////////////////////

void Login(DBMgr* DBMgr, User* currentUser, bool& isRunning) {
    clearScreen();

    DBMgr->importData();

    cout << "Welcome to " << acfg << "CaR-e-MaSyS!\n"
         << acr;
    cout << "Do you wish to \n"
         << acfg << "register (r)" << acr << " or " << acfy << "login (l)" << acr << " or " << acfr << "quit (q)? : " << acr;

    std::string action, role;

    while ((action[0] != 'r') || (action[0] != 'l') || (action[0] != 'q') || (action[0] != 'R') || (action[0] != 'L') || (action[0] != 'Q')) {
        cin >> (action);
        if (action[0] == 'q' || action[0] == 'Q') {
            isRunning = false;
            return;
        } else if (action[0] == 'r' || action[0] == 'R') {
            while ((role[0] != 'c') || (role[0] != 'e') || (role[0] != 'C') || (role[0] != 'E')) {
                cout << "Please select your role: \n Customer (c) or Employee (e) : ";
                cin >> (role);

                clearScreen();
                if (role[0] == 'c' || role[0] == 'C') {
                    cout << "You have selected Customer role.\n";
                } else if (role[0] == 'e' || role[0] == 'E') {
                    cout << "You have selected Employee role.\n";
                } else {
                    cout << acfr << "Invalid role!" << acr << "Please select a valid role.\n";
                    continue;
                }

                char back;
                cout << "Press (b) to go select another role. Press any other key to continue... ";
                getchar();
                back = getchar();

                if (back == 'b') {
                    clearScreen();
                    continue;
                } else
                    break;
            }

            // Registration
            std::string Name, ID, password;
            cout << "Hi! Please Enter your Name: " << endl;
            cin >> (Name);

            bool unique_ID = false;
            while (unique_ID == false) {
                cout << "Enter an ID: ";
                cin >> (ID);

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << acfr << "Invalid input. Please try again." << acr << endl;
                    continue;
                }

                // check if ID already exists

                if (DBMgr->findUser(ID) == true) {
                    cerr << "ID '" << ID << "' already exists. Please choose a different ID." << endl;
                } else {
                    unique_ID = true;
                }
            }

            cout << "Create a password: ";
            password = getPassword();

            if (role[0] == 'c' || role[0] == 'C') {
                Customer nC(Name, ID, password);
                DBMgr->addCustomer(&nC);
            } else if (role[0] == 'e' || role[0] == 'E') {
                Employee nE(Name, ID, password);
                DBMgr->addEmployee(&nE);
            }

            currentUser = DBMgr->getUser(ID);

            cout << "You have successfully registered as " << ((role[0] == 'c' || role[0] == 'C') ? "a Customer" : "an Employee") << "!\n";

            DBMgr->exportData();
            DBMgr->importData();

            break;
        } else if (action[0] == 'l' || action[0] == 'L') {
            // Login
            bool auth = false;
            std::string ID, password;

            while (auth != true) {
                cout << "Enter your ID: " << endl;

                cin >> (ID);
                // ID = "peter101";

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << acfr << "Invalid input. Please try again." << acr << endl;
                    continue;
                }

                cout << "Enter your password: " << endl;
                password = getPassword();
                // password = "gg";

                clearScreen();
                auth = DBMgr->login(ID, password);

                if (auth != true) cout << acfr << "Invalid ID or password! Please try again.\n"
                                       << acr;
            }

            currentUser = DBMgr->getUser(ID);

            std::string rolee = currentUser->memberType;

            if (rolee == "Customer")
                role = "c";
            else if (rolee == "Employee")
                role = "e";
            else if (rolee == "Manager")
                role = "m";

            cout << "You have successfully logged in as " << ((rolee == "Employee") ? "an " : "a ") << rolee << "!\n";
            Sleep(200);
            break;
        } else {
            clearScreen();
            cerr << acfr << "Invalid action!\n"
                 << acr << "Please choose 'register' or 'login' (or 'quit') (type 'r' or 'l' or 'q'). : ";
        }
    }

    DBMgr->exportData();
    DBMgr->importData();

    // Main menu

    if (role[0] == 'c' || role[0] == 'e') {
        int choice;
        do {
            // Display menu
            Sleep(1000);
            clearScreen();

            currentUser->getDetails();

            cout << "Welcome to the Main Menu!" << endl;
            cout << "Please select an option: " << endl;

            cout << dottedyellow;

            cout << "\t 1. Browse & Rent" << endl;
            cout << "\t 2. View rented cars" << endl;
            cout << "\t 3. Return a car" << endl;
            cout << "\t 4. View & Clear dues" << endl;
            cout << "\t 5. Logout" << endl;

            cout << dottedyellow;

            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');

                clearScreen();
                cout << acfr << "Invalid input. Please try again." << acr << endl;
                continue;
            }

            // Process user's choice
            std::string rent, regNo;
            switch (choice) {
                case 1: {
                    // Browse & Rent
                    int flag = 2;

                    cout << "All cars available : " << endl;
                    DBMgr->showAllCarsSecure();

                    cout << dottedred;

                    pak2c();

                    cout << "Do you want to rent a car? (y/n): ";
                    cin >> (rent);

                    if (rent[0] == 'y' || rent[0] == 'Y') {
                        cout << "Enter the registration number of the car you want to rent: ";
                        cin >> (regNo);

                        std::transform(regNo.begin(), regNo.end(), regNo.begin(), ::toupper);

                        if (DBMgr->findCar(regNo)) {
                            Car* car = DBMgr->getCar(regNo);

                            if ((currentUser->getRecord() < 0)) {
                                cout << acfr << "You have a negative record. You cannot rent a car->" << endl;
                                pak2c();
                                break;
                            } else if (car->getisRented()) {
                                cout << acfr << "Car is already rented!" << endl;
                                pak2c();
                                break;
                            }

                            cout << "Enter the rent date in the format (dd mm yyyy): ";
                            int dd, mm, yyyy;
                            cin >> dd >> mm >> yyyy;

                            if (dd < 1 || dd > 31 || mm < 1 || mm > 12 || yyyy < 2020 || yyyy > 2026) {
                                cout << acfr << "Invalid date!" << acr << "Please recheck details." << endl;
                                pak2c();
                                break;
                            }

                            cout << "Enter the number of days you want to rent the car for: ";
                            int days;
                            cin >> days;

                            if (days < 0 || days > 15) {
                                cout << acfr << "Invalid number of days!" << acr << "Please recheck details." << endl;
                                cout << "Note : \tYou can rent a car for a maximum of 15 days." << endl;
                                pak2c();
                                break;
                            }

                            Date rentDate = Date(dd, mm, yyyy);

                            car->rentRequest(currentUser);

                            car->updateRentDate(rentDate);
                            car->updateExpectedDays(days);

                            // car->getDetails();

                            DBMgr->updateCar(car);

                            currentUser->rentCar(car);
                            currentUser->addRent(car);
                            DBMgr->updateUser(currentUser);

                            cout << dottedgreen;
                            DBMgr->getCar(regNo)->getDetails();
                            cout << dottedgreen;

                        } else {
                            cout << acfr "Car not found! " << acr << "Please recheck details." << endl;
                        }
                    }

                    DBMgr->exportData();
                    DBMgr->importData();

                    pak2c();
                    break;
                }
                case 2: {
                    cout << "Rented cars: " << endl;
                    currentUser->showMyCars(DBMgr);

                    DBMgr->exportData();
                    DBMgr->importData();

                    pak2c();
                    break;
                }
                case 3: {
                    if (currentUser->getRentedCars().size() == 0) {
                        cout << acfr << "You have not rented any cars!" << endl;
                        pak2c();
                        break;
                    }

                    cout << "Do you want to view the cars you have rented? (y/n): ";
                    cin >> (rent);

                    if (rent[0] == 'y' || rent[0] == 'Y') {
                        currentUser->showMyCars(DBMgr);
                        pak2c();
                    }

                    cout << "Enter the registration number of the car you want to return: ";
                    cin >> (regNo);

                    std::transform(regNo.begin(), regNo.end(), regNo.begin(), ::toupper);

                    if (DBMgr->findCar(regNo)) {
                        Car* car = DBMgr->getCar(regNo);

                        if (!car->getisRented()) {
                            cout << acfr << "Car is not rented!" << endl;
                            pak2c();
                            break;
                        }

                        if (currentUser->getRentedCars().size() == 0) {
                            cout << acfr << "You have not rented any cars!" << endl;
                            pak2c();
                            break;
                        }

                        cout << "Either choose to enter the return date (d) or the number of days (n) you rented the car for: ";
                        std::string choice;
                        cin >> choice;

                        Date actualReturnDate;
                        int days;
                        if (choice[0] == 'd' || choice[0] == 'D') {
                            int dd, mm, yyyy;
                            cout << "Enter the return date in the format (dd mm yyyy): ";
                            cin >> dd >> mm >> yyyy;

                            if (dd < 1 || dd > 31 || mm < 1 || mm > 12 || yyyy < 2020 || yyyy > 2026) {
                                cout << acfr << "Invalid date!" << acr << "Please recheck details." << endl;
                                pak2c();
                                break;
                            }

                            actualReturnDate = Date(dd, mm, yyyy);

                            days = actualReturnDate - car->getRentDate();

                            if (days < 0) {
                                cout << acfr << "Invalid date! : Return Date cannot be before Rent Date. " << acr << "Please recheck details." << endl;
                                pak2c();
                                break;
                            }

                        } else {
                            cout << "How many days did you (actually) rent the car for? ";
                            cin >> days;
                        }

                        if (days > 15) {
                            cout << acfr << "Invalid number of days!" << acr << "Please recheck details." << endl;
                            cout << "Note : \tYou can rent a car for a maximum of 15 days." << endl;
                            pak2c();
                            break;
                        }

                        if (days == 0) {
                            days = 1;
                            cout << "Note : \tYou'll be charged for 1 day even on the same day return." << endl;
                        }

                        float condition;
                        cout << "Enter the condition: (0 - 100) ";
                        while (!(cin >> condition) || condition < 0 || condition > 100) {
                            cout << acfr << "Invalid condition!" << acr << "Please enter a valid condition." << endl;
                            cin.clear();
                            cin.ignore(1000, '\n');
                        }

                        if (condition > car->getCondition()) {
                            cout << acfr << "Invalid condition!" << acr << "Condition cannot be better after returning!" << endl;
                            pak2c();
                            break;
                        }

                        float diffcondition = car->getCondition() - condition;

                        car->updateCondition(condition);

                        double fine = 0.0;
                        fine = (0.1 * (100.0 - currentUser->getRecord()) * (days - car->getExpectedDays()));
                        if (fine < 0) fine = 0.0;

                        double newRecord = currentUser->getRecord() - fine / 200.0;
                        currentUser->setRecord(newRecord);

                        Date rentDate = car->getRentDate();
                        cout << dottedgreen;

                        cout << "You had rented the car on: " << rentDate.getDateString();
                        rentDate.addDays(days);
                        cout << " and returned on " << rentDate.getDateString() << endl;

                        if (days > car->getExpectedDays()) {
                            cout << "You have returned the car " << acfr << days - car->getExpectedDays() << acr << " days late." << endl;
                        }
                        if (diffcondition > 30) {
                            cout << "The car is returned in " << acfr << "poor" << acr << "condition." << endl;
                            if (fine < 0.1)
                                fine = 2000.0;
                            else
                                fine *= (1 + 1 - diffcondition / 100.0);
                        } else if (diffcondition <= 5) {
                            cout << "The car is in " << acfg << "good" << acr << " condition." << endl;
                            int random = rand() % 10 + 1;
                            cout << "Thank you for taking care of the car-> You will receive an additional discount of " << random << "%!" << endl;
                            fine += (-1 * car->getDailyRent() * car->getExpectedDays() * random / 100.0);

                            cout << "This also means that your record will be improved by " << acfg << random / 4 << acr << " points!" << endl;
                            currentUser->setRecord(currentUser->getRecord() + random / 4);
                        } else {
                            cout << "The car is in " << acfy << "average" << acr << " condition." << endl;
                        }

                        if (fine < 0) fine = 0.0;

                        if (fine > 0.0) {
                            cout << "Your fine is: Rs. " << acfr << fine << acr << endl;
                        } else {
                            cout << "You have no fines." << endl;
                        }

                        currentUser->addFine(fine);

                        cout << "You have to pay: Rs. " << acfy << currentUser->getDue() << acr << endl;

                        cout << dottedgreen;

                        car->returnRequest(currentUser);
                        currentUser->returnCar(car);

                        DBMgr->updateCar(car);
                        DBMgr->updateUser(currentUser);

                    } else {
                        cout << acfr "Car not found! " << acr << "Please recheck details." << endl;
                    }

                    DBMgr->exportData();
                    DBMgr->importData();

                    pak2c();
                    break;
                }
                case 4: {
                    for (auto car : currentUser->getRentedCars()) {
                        if (car->getisRented()) {
                            cout << "Dues for car " << car->getRegNo() << ": Rs. " << acfr << car->getDailyRent() * car->getExpectedDays() << acr << endl;
                        }
                    }

                    if (currentUser->getDue() > 0) {
                        cout << "After applying fines (if any), your total dues: Rs. " << acfr << currentUser->getDue() << acr << endl;
                        pak2c();
                    } else {
                        cout << "You have no dues." << endl;
                        pak2c();
                        break;
                    }

                    cout << "Do you wish to clear your dues? (y/n): ";
                    cin >> (rent);

                    cout << "Note : \tFor non-returned cars, You can clear the dues by returning the car->\n";

                    if (rent[0] == 'y' || rent[0] == 'Y') {
                        if (currentUser->getRentedCars().size() == 0 && currentUser->getDue() > 0) {
                            currentUser->clearDues();
                            cout << acfg << "Dues cleared successfully." << acr << endl;
                        } else {
                            double ddue = 0;
                            for (auto car : currentUser->getRentedCars()) {
                                if (car->getisRented()) {
                                    ddue += car->getDailyRent() * car->getExpectedDays();
                                }
                            }

                            ddue = currentUser->getDue() - ddue;
                            if (ddue < 0) ddue = 0.0;

                            currentUser->clearPartialDues(ddue);
                            if (ddue > 0)
                                cout << acfg << "Partial Dues cleared successfully." << acr << endl;
                            else
                                cout << acfy << "No Partial Dues to clear. Return Cars, if any, to clear all dues." << acr << endl;
                        }
                    }

                    if (currentUser->getDue() < 0) currentUser->clearDues();

                    double newRec = currentUser->getRecord() + 4.0;
                    if (newRec > 75.0) newRec = 75.0;
                    if (currentUser->getDue() < 75.0) {
                        currentUser->setRecord(newRec);
                    }

                    currentUser->setRecord(newRec);

                    DBMgr->updateUser(currentUser);

                    DBMgr->exportData();
                    DBMgr->importData();

                    pak2c();
                    break;
                }
                case 5: {
                    cout << "Logging out...\n";
                    DBMgr->exportData();
                    Sleep(400);
                    return;
                }
                default: {
                    clearScreen();
                    cout << acfr << "Invalid choice. Please try again." << acr << endl;
                }
            }

            DBMgr->exportData();
            DBMgr->importData();

        } while (choice != 5);
    } else if (role[0] == 'm') {
        Manager currManager(currentUser->getName(), currentUser->getID(), currentUser->getPassword());

        int choice;
        do {
            // Display menu
            Sleep(600);
            clearScreen();

            cout << "Welcome to the Manager Menu!" << endl;
            cout << "Please select an option: " << endl;

            cout << dottedyellow;

            cout << "\t 1. View All Cars" << endl;
            cout << "\t 2. Search Cars/Customers/Employees" << endl;
            cout << "\t 3. Modify Cars (add/update/delete)" << endl;
            cout << "\t 4. View and Modify Customers (add/update/delete)" << endl;
            cout << "\t 5. View and Modify Employees (add/update/delete)" << endl;
            cout << "\t 6. Logout" << endl;

            cout << dottedyellow;

            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();

                cin.ignore(1000, '\n');

                clearScreen();
                cout << acfr << "Invalid input. Please try again." << acr << endl;
                continue;
            }

            // Process user's choice
            std::string action, view;
            switch (choice) {
                case 1: {
                    // View All Cars
                    DBMgr->showAllCars();
                    cout << dottedred;

                    pak2c();
                    break;
                }
                case 2: {
                    cout << "Do you want to search for Cars (c), Customers (u) or Employees (e)? (c/u/e): ";
                    cin >> (action);

                    if (action[0] == 'c' || action[0] == 'C') {
                        std::string regNo, model;
                        int flag = 2;

                        cout << "Do you want to search by Registration No. or Model? (r/m): ";
                        cin >> (action);

                        if (action[0] == 'r' || action[0] == 'R') {
                            flag = 0;
                            cout << "Enter the registration number of the car you want to search: " << endl;
                            cin >> (regNo);
                        } else if (action[0] == 'm' || action[0] == 'M') {
                            flag = 1;
                            cout << "Enter the model of the car you want to search: " << endl;

                            cin >> (model);
                        }

                        std::transform(regNo.begin(), regNo.end(), regNo.begin(), ::toupper);
                        std::transform(model.begin(), model.end(), model.begin(), ::toupper);

                        if (DBMgr->findCar(regNo) && flag == 0) {
                            Car* car = DBMgr->getCar(regNo);
                            car->getDetails();
                        } else if (DBMgr->findCarbyModel(model) && flag == 1) {
                            Car* car = DBMgr->getCarbyModel(model);
                            car->getDetails();
                        } else {
                            cout << acfr << "Car not found! " << acr << "Please recheck details." << endl;
                            cout << "But here are the closest matches:\n"
                                 << endl;
                            for (auto car : DBMgr->getCars()) {
                                std::string regNoC = car.se->getRegNo();
                                std::string modelC = car.se->getModel();

                                transform(regNoC.begin(), regNoC.end(), regNoC.begin(), ::toupper);
                                transform(modelC.begin(), modelC.end(), modelC.begin(), ::toupper);

                                if ((((regNoC.find(regNo) != std::string::npos) && (flag == 0)) || ((modelC.find(model) != std::string::npos) && (flag == 1)))) {
                                    cout << dottedred;
                                    car.se->getDetails();
                                }
                            }
                        }

                    } else if (action[0] == 'u' || action[0] == 'U') {
                        std::string ID, name;
                        int flag = 2;
                        cout << "Do you want to search by ID or Name? (i/n): ";
                        cin >> (action);

                        if (action[0] == 'i' || action[0] == 'I') {
                            flag = 0;
                            cout << "Enter the ID of the customer you want to search: " << endl;
                            cin >> (ID);

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << acfr << "Invalid input. Please try again." << acr << endl;
                                continue;
                            }

                        } else {
                            flag = 1;
                            cout << "Enter the Name of the customer you want to search: " << endl;
                            cin >> (name);
                        }

                        transform(ID.begin(), ID.end(), ID.begin(), ::toupper);
                        transform(name.begin(), name.end(), name.begin(), ::toupper);

                        if (DBMgr->findUser(ID) && flag == 0) {
                            User* user = DBMgr->getUser(ID);
                            cout << dottedred;
                            user->getDetails();
                        } else if (DBMgr->findUserbyName(name) && flag == 1) {
                            User* user = DBMgr->getUserbyName(name);
                            cout << dottedred;
                            user->getDetails();
                        } else {
                            cout << acfr << "User not found! " << acr << "Please recheck details." << endl;
                            cout << "But here are the closest matches: " << endl;

                            for (auto user : DBMgr->getCustomers()) {
                                std::string IDU = user.se->getID();
                                std::string nameU = user.se->getName();

                                transform(IDU.begin(), IDU.end(), IDU.begin(), ::toupper);
                                transform(nameU.begin(), nameU.end(), nameU.begin(), ::toupper);

                                if (((IDU.find(ID) != std::string::npos) && flag == 0) || ((nameU.find(name) != std::string::npos) && flag == 1)) {
                                    cout << dottedred;
                                    user.se->getDetails();
                                }
                            }

                            for (auto user : DBMgr->getEmployees()) {
                                std::string IDU = user.se->getID();
                                std::string nameU = user.se->getName();

                                transform(IDU.begin(), IDU.end(), IDU.begin(), ::toupper);
                                transform(nameU.begin(), nameU.end(), nameU.begin(), ::toupper);

                                if (((IDU.find(ID) != std::string::npos) && flag == 0) || ((nameU.find(name) != std::string::npos) && flag == 1)) {
                                    cout << dottedred;
                                    user.se->getDetails();
                                }
                            }
                        }
                    } else if (action[0] == 'e' || action[0] == 'E') {
                        std::string ID, name;
                        int flag = 2;
                        cout << "Do you want to search by ID or Name? (i/n): ";
                        cin >> (action);

                        if (action[0] == 'i' || action[0] == 'I') {
                            flag = 0;
                            cout << "Enter the ID of the employee you want to search: " << endl;
                            cin >> (ID);

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << acfr << "Invalid input. Please try again." << acr << endl;
                                continue;
                            }

                        } else {
                            flag = 1;
                            cout << "Enter the Name of the employee you want to search: " << endl;
                            cin >> (name);
                        }

                        transform(ID.begin(), ID.end(), ID.begin(), ::toupper);
                        transform(name.begin(), name.end(), name.begin(), ::toupper);

                        if (DBMgr->findUser(ID) && flag == 0) {
                            User* user = DBMgr->getUser(ID);
                            cout << dottedred;
                            user->getDetails();
                        } else if (DBMgr->findUserbyName(name) && flag == 1) {
                            User* user = DBMgr->getUserbyName(name);
                            cout << dottedred;
                            user->getDetails();
                        } else {
                            cout << acfr << "User not found! " << acr << "Please recheck details." << endl;
                            cout << "But here are the closest matches: " << endl;

                            for (auto user : DBMgr->getCustomers()) {
                                std::string IDU = user.se->getID();
                                std::string nameU = user.se->getName();

                                transform(IDU.begin(), IDU.end(), IDU.begin(), ::toupper);
                                transform(nameU.begin(), nameU.end(), nameU.begin(), ::toupper);

                                if (((IDU.find(ID) != std::string::npos) && flag == 0) || ((nameU.find(name) != std::string::npos) && flag == 1)) {
                                    cout << dottedred;
                                    user.se->getDetails();
                                }
                            }

                            for (auto user : DBMgr->getEmployees()) {
                                std::string IDU = user.se->getID();
                                std::string nameU = user.se->getName();

                                transform(IDU.begin(), IDU.end(), IDU.begin(), ::toupper);
                                transform(nameU.begin(), nameU.end(), nameU.begin(), ::toupper);

                                if (((IDU.find(ID) != std::string::npos) && flag == 0) || ((nameU.find(name) != std::string::npos) && flag == 1)) {
                                    cout << dottedred;
                                    user.se->getDetails();
                                }
                            }
                        }
                    } else {
                        clearScreen();
                        cout << acfr << "Invalid action. Please try again." << acr << endl;
                    }

                    pak2c();
                    break;
                }
                case 3: {
                    // Modify Cars
                    cout << "Do you want to add, update or delete a car? (a/u/d): ";
                    cin >> (action);

                    cout << "Do you want to view all the cars first? (y/n): ";
                    cin >> (view);

                    if (view[0] == 'y' || view[0] == 'Y') {
                        DBMgr->showAllCars();
                        cout << dottedred;
                    }

                    if (action[0] == 'a' || action[0] == 'A') {
                        // Add a car
                        Car* car;
                        std::string model, regNo, renterID;
                        Date rentDate;
                        float condition, dailyRent;
                        bool isRented;
                        int expectedDays;

                        cout << "Enter the car model: " << endl;

                        cin >> (model);

                        cout << "Enter the registration number: " << endl;
                        cin >> (regNo);

                        std::transform(regNo.begin(), regNo.end(), regNo.begin(), ::toupper);

                        if (DBMgr->findCar(regNo)) {
                            cout << acfr << "Car already exists!" << acr << "Please enter a unique Registration No." << endl;
                            break;
                        }

                        cout << "Enter the condition: (0 - 100) ";
                        while (!(cin >> condition) || condition < 0 || condition > 100) {
                            cout << acfr << "Invalid condition!" << acr << "Please enter a valid condition." << endl;
                            cin.clear();
                            cin.ignore(1000, '\n');
                        }

                        cout << "Enter the expected number of days for rent: ";
                        cin >> expectedDays;

                        cout << "Enter the daily rent: ";
                        cin >> dailyRent;

                        std::string isR;
                        cout << "Is it rented? (y/n): ";
                        cin >> (isR);

                        isRented = (isR[0] == 'y' || isR[0] == 'Y') ? true : false;

                        if (isRented) {
                            cout << "Enter the renter's ID: ";
                            cin >> renterID;

                            if (!DBMgr->findUser(renterID)) {
                                cout << acfr << "User not found!" << acr << "Please enter a valid User ID." << endl;
                                break;
                            }

                            int dd, mm, yyyy;
                            cout << "Enter the rent date in the format (dd mm yyyy):";
                            cin >> dd >> mm >> yyyy;

                            if (dd < 1 || dd > 31 || mm < 1 || mm > 12 || yyyy < 2020 || yyyy > 2026) {
                                cout << acfr << "Invalid date!" << acr << "Please recheck details." << endl;
                                break;
                            }

                            rentDate = Date(dd, mm, yyyy);

                            cout << "Enter the expected number of days for rent: ";
                            cin >> expectedDays;
                        } else {
                            isRented = false;
                            renterID = "";
                            rentDate = Date();
                            expectedDays = 0;
                        }

                        Car nC = Car(model, regNo, condition, isRented, renterID, rentDate, dailyRent, expectedDays);
                        car = &nC;

                        cout << "Following are the details of the car you want to add: \n";

                        cout << dottedgreen;
                        car->getDetails();
                        cout << dottedgreen;

                        cout << "Are you sure you want to add this car? (y/n): ";
                        std::string confirm;
                        cin >> (confirm);

                        if (confirm[0] == 'y' || confirm[0] == 'Y') {
                            DBMgr->addCar(car);

                            if (isRented) {
                                User* renter = DBMgr->getUser(renterID);

                                car->rentRequest(renter);

                                car->updateRentDate(rentDate);
                                car->updateExpectedDays(expectedDays);

                                // car->getDetails();

                                DBMgr->updateCar(car);

                                renter->rentCar(car);
                                renter->addRent(car);
                                DBMgr->updateUser(renter);
                            }
                        }

                    } else if (action[0] == 'u' || action[0] == 'U') {
                        // Update a car

                        Car* car;
                        std::string regNo, renterID;
                        Date rentDate;
                        float condition, dailyRent;
                        bool isRented;
                        std::string act;
                        int expectedDays;

                        cout << "Enter the registration number of the car you want to update: ";
                        cin >> (regNo);

                        std::transform(regNo.begin(), regNo.end(), regNo.begin(), ::toupper);

                        if (!DBMgr->findCar(regNo)) {
                            cout << acfr << "Car not found!" << acr << "Please enter corrrect Registration No." << endl;
                            break;
                        }

                        if (DBMgr->getCar(regNo)->getisRented() == true) {
                            cout << acfr << "Car is currently rented!" << acr << endl;
                            cout << "Are you sure you want to update this car? (y/n): ";
                            std::string confirm;
                            cin >> (confirm);

                            if (confirm[0] == 'y' || confirm[0] == 'Y') {
                                continue;
                            } else
                                break;
                        }

                        cout << "Do you want to update the daily rent? (y/n): ";
                        cin >> (act);

                        if (act[0] == 'y' || act[0] == 'Y') {
                            cout << "Enter the new daily rent: ";
                            cin >> dailyRent;
                        } else
                            dailyRent = DBMgr->getCar(regNo)->getDailyRent();

                        cout << "Do you want to update the condition? (y/n): ";
                        cin >> (act);

                        if (act[0] == 'y' || act[0] == 'Y') {
                            cout << "Enter the condition: (0 - 100) ";
                            while (!(cin >> condition) || condition < 0 || condition > 100) {
                                cout << acfr << "Invalid condition!" << acr << "Please enter a valid condition." << endl;
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }

                        } else
                            condition = DBMgr->getCar(regNo)->getCondition();

                        cout << "Do you want to update the renter's details? (y/n): ";
                        cin >> (act);

                        if (act[0] == 'y' || act[0] == 'Y') {
                            cout << "Is it still rented? (y/n): ";
                            std::string isR;
                            cin >> (isR);

                            if (isR[0] == 'y' || isR[0] == 'Y') {
                                isRented = true;

                                cout << "Enter the renter's ID: ";
                                cin >> renterID;

                                if (!DBMgr->findUser(renterID)) {
                                    cout << acfr << "User not found!" << acr << "Please enter a valid User ID." << endl;
                                    break;
                                }

                                int dd, mm, yyyy;
                                cout << "Enter the rent date in the format (dd mm yyyy):";
                                cin >> dd >> mm >> yyyy;
                                rentDate = Date(dd, mm, yyyy);

                                cout << "Enter the expected number of days for rent: ";
                                cin >> expectedDays;

                            } else {
                                isRented = false;
                                renterID = "";
                                rentDate = Date(1, 1, 2001);
                                expectedDays = 0;
                            }
                        } else {
                            isRented = DBMgr->getCar(regNo)->getisRented();
                            renterID = DBMgr->getCar(regNo)->getRenterID();
                            rentDate = DBMgr->getCar(regNo)->getRentDate();
                            expectedDays = DBMgr->getCar(regNo)->getExpectedDays();
                        }

                        *car = Car(DBMgr->getCar(regNo)->getModel(), regNo, condition, isRented, renterID, rentDate, dailyRent, expectedDays);

                        DBMgr->updateCar(car);

                        currentUser->rentCar(car);
                        currentUser->addRent(car);
                        DBMgr->updateUser(currentUser);

                    } else if (action[0] == 'd' || action[0] == 'D') {
                        // Delete a car
                        Car car;
                        std::string regNo;

                        cout << "Enter the registration number of the car you want to delete: ";
                        cin >> (regNo);

                        std::transform(regNo.begin(), regNo.end(), regNo.begin(), ::toupper);

                        if (!DBMgr->findCar(regNo)) {
                            cout << acfr << "Car not found!" << acr << "Please enter corrrect Registration No." << endl;
                            break;
                        }

                        cout << "Are you sure you want to delete this car? (y/n): ";
                        std::string confirm;
                        cin >> (confirm);

                        if (confirm[0] == 'y' || confirm[0] == 'Y') {
                            if (DBMgr->getCar(regNo)->getisRented()) {
                                cout << acfr << "Car is currently rented! Cannot delete." << acr << endl;
                                break;
                            }

                            DBMgr->removeCar(DBMgr->getCar(regNo));
                            cout << "Car deleted successfully." << endl;
                        }

                    } else {
                        clearScreen();
                        cout << acfr << "Invalid action. Please try again." << acr << endl;
                    }

                    pak2c();
                    break;
                }
                case 4: {
                    cout << "Do you want to view all the customers first? (y/n): ";
                    cin >> (view);

                    if (view[0] == 'y' || view[0] == 'Y') {
                        DBMgr->showAllUsers("Customer");
                        cout << dottedred;
                    }

                    cout << "Do you want to add, update or delete a customer? (or neither) (a/u/d/n): ";
                    cin >> (action);

                    if (action[0] == 'a' || action[0] == 'A') {
                        // Add a customer
                        Customer* customer;
                        std::string CName, CID, CPassword;

                        cout << "Enter the customer's Name: " << endl;
                        cin >> (CName);

                        bool unique_ID = false;
                        while (unique_ID == false) {
                            cout << "Enter a ID: ";
                            cin >> (CID);

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << acfr << "Invalid input. Please try again." << acr << endl;
                                continue;
                            }

                            // check if ID already exists

                            if (DBMgr->findUser(CID) == true) {
                                cerr << "ID '" << CID << "' already exists. Please choose a different ID." << endl;
                            } else {
                                unique_ID = true;
                            }
                        }

                        cout << "Create a password: ";
                        CPassword = getPassword();

                        Customer nC = Customer(CName, CID, CPassword);
                        customer = &nC;

                        cout << "Following are the details of the customer you want to add: \n";
                        customer->getDetails();

                        cout << "Are you sure you want to add this customer? (y/n): ";
                        std::string confirm;
                        cin >> (confirm);

                        if (confirm[0] == 'y' || confirm[0] == 'Y') {
                            DBMgr->addCustomer(customer);
                            cout << "Customer added successfully." << endl;
                        }

                        pak2c();
                        break;

                    } else if (action[0] == 'u' || action[0] == 'U') {
                        // Update a customer

                        Customer* customer;
                        std::string Name, ID, password;
                        std::string act;

                        cout << "Enter the ID of the customer you want to update: ";
                        cin >> (ID);

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << acfr << "Invalid input. Please try again." << acr << endl;
                            continue;
                        }

                        if (!DBMgr->findUser(ID)) {
                            cout << acfr << "Customer not found!" << acr << "Please enter corrrect ID." << endl;
                            break;
                        }

                        cout << "Do you want to update the name? (y/n): ";
                        cin >> (act);

                        if (act[0] == 'y' || act[0] == 'Y') {
                            cout << "Enter the new name: ";
                            cin >> (Name);
                        }

                        cout << "Do you want to update the password? (y/n): ";
                        cin >> (act);

                        if (act[0] == 'y' || act[0] == 'Y') {
                            cout << "Enter the new password: ";
                            password = getPassword();
                        }

                        cout << "Are you sure you want to update this customer? (y/n): ";
                        std::string confirm;
                        cin >> (confirm);

                        if (confirm[0] == 'y' || confirm[0] == 'Y') {
                            Customer nC = Customer(Name, ID, password);
                            customer = &nC;

                            cout << dottedgreen;
                            customer->getDetails();
                            cout << dottedgreen;

                            DBMgr->updateCustomer(customer);
                        }

                        pak2c();
                        break;

                    } else if (action[0] == 'd' || action[0] == 'D') {
                        // Delete a customer
                        Customer* customer;

                        std::string ID;

                        cout << "Enter the ID of the customer you want to delete: ";
                        cin >> (ID);

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << acfr << "Invalid input. Please try again." << acr << endl;
                            continue;
                        }

                        if (ID == currentUser->getID()) {
                            cout << acfr << "Sorry! Please don't delete yourself! :/" << acr << endl;
                            break;
                        }

                        if (!DBMgr->findUser(ID)) {
                            cout << acfr << "Customer not found!" << acr << "Please enter corrrect ID." << endl;
                            break;
                        }

                        if (DBMgr->getUser(ID)->getRentedCars().size() > 0) {
                            cout << acfr << "Customer has rented cars! Cannot delete." << acr << endl;
                            break;
                        }

                        if (DBMgr->getUser(ID)->getDue() > 0) {
                            cout << acfr << "Customer has dues! Cannot delete." << acr << endl;
                            cout << "Do you want to clear the dues? (y/n): ";
                            std::string confirm;
                            cin >> (confirm);

                            if (confirm[0] == 'y' || confirm[0] == 'Y') {
                                DBMgr->getUser(ID)->clearDues();
                                cout << acfg << "Dues cleared successfully." << acr << endl;
                            } else
                                break;
                        }

                        pak2c();

                        customer = DBMgr->getCustomer(ID);

                        cout << dottedred;
                        customer->getDetails();
                        cout << dottedred;

                        cout << "Are you sure you want to delete this customer? (y/n): ";

                        std::string confirm;
                        cin >> (confirm);

                        if (confirm[0] == 'y' || confirm[0] == 'Y') {
                            DBMgr->removeCustomer(ID);
                            cout << "Customer deleted successfully." << endl;
                        }

                        pak2c();
                        break;

                    } else if (action[0] == 'n' || action[0] == 'N') {
                        break;
                    } else {
                        clearScreen();
                        cout << acfr << "Invalid action. Please try again." << acr << endl;
                    }

                    pak2c();
                    break;
                }
                case 5: {
                    cout << "Do you want to view all the employees first? (y/n): ";
                    cin >> (view);

                    if (view[0] == 'y' || view[0] == 'Y') {
                        DBMgr->showAllUsers("Employee");
                        cout << dottedred;
                    }

                    cout << "Do you want to add, update or delete an employee? (or neither) (a/u/d/n): ";
                    cin >> (action);

                    if (action[0] == 'a' || action[0] == 'A') {
                        // Add an employee
                        Employee* employee;
                        std::string EName, EID, EPassword;

                        cout << "Enter the employee's Name: " << endl;
                        cin >> (EName);

                        bool unique_ID = false;
                        while (unique_ID == false) {
                            cout << "Enter a ID: ";
                            cin >> EID;

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << acfr << "Invalid input. Please try again." << acr << endl;
                                continue;
                            }

                            // check if ID already exists

                            if (DBMgr->findUser(EID) == true) {
                                cerr << acfr << "ID '" << EID << "' already exists. Please choose a different ID." << acr << endl;
                            } else {
                                unique_ID = true;
                            }
                        }

                        cout << "Create a password: ";
                        EPassword = getPassword();

                        Employee nE = Employee(EName, EID, EPassword);
                        employee = &nE;

                        cout << "Following are the details of the employee you want to add: \n";

                        cout << dottedgreen;
                        employee->getDetails();
                        cout << dottedgreen;

                        cout << "Are you sure you want to add this employee? (y/n): ";
                        std::string confirm;
                        cin >> (confirm);

                        if (confirm[0] == 'y' || confirm[0] == 'Y') {
                            DBMgr->addEmployee(employee);
                            cout << "Employee added successfully." << endl;
                        }

                        pak2c();
                        break;

                    } else if (action[0] == 'u' || action[0] == 'U') {
                        // Update an employee

                        Employee* employee;
                        std::string Name, ID, password;
                        std::string act;

                        cout << "Enter the ID of the employee you want to update: ";
                        cin >> (ID);

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << acfr << "Invalid input. Please try again." << acr << endl;
                            continue;
                        }

                        if (!DBMgr->findUser(ID)) {
                            cout << acfr << "Employee not found!" << acr << "Please enter corrrect ID." << endl;
                            break;
                        }

                        cout << "Do you want to update the name? (y/n): ";
                        cin >> (act);

                        if (act[0] == 'y' || act[0] == 'Y') {
                            cout << "Enter the new name: ";
                            cin >> (Name);
                        }

                        cout << "Do you want to update the password? (y/n): ";
                        cin >> (act);

                        if (act[0] == 'y' || act[0] == 'Y') {
                            cout << "Enter the new password: ";
                            password = getPassword();
                        }

                        cout << "Are you sure you want to update this employee? (y/n): ";
                        std::string confirm;
                        cin >> (confirm);

                        if (confirm[0] == 'y' || confirm[0] == 'Y') {
                            Employee nE = Employee(Name, ID, password);
                            employee = &nE;

                            cout << dottedgreen;
                            employee->getDetails();
                            cout << dottedgreen;

                            DBMgr->updateEmployee(employee);

                            cout << acfg << "Employee updated successfully.\n"
                                 << acr << endl;
                        }

                        pak2c();
                        break;

                    } else if (action[0] == 'd' || action[0] == 'D') {
                        // Delete an employee
                        Employee* employee;
                        std::string ID;

                        cout << "Enter the ID of the employee you want to delete: ";
                        cin >> (ID);

                        if (ID == currentUser->getID()) {
                            cout << acfr << "Sorry! Please don't delete yourself! :/" << acr << endl;
                            break;
                        }

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << acfr << "Invalid input. Please try again." << acr << endl;
                            continue;
                        }

                        if (!DBMgr->findUser(ID)) {
                            cout << acfr << "Employee not found!" << acr << "Please enter corrrect ID." << endl;
                            break;
                        }

                        if (DBMgr->getUser(ID)->getRentedCars().size() > 0) {
                            cout << acfr << "Employee has rented cars! Cannot delete." << acr << endl;
                            break;
                        }

                        if (DBMgr->getEmployee(ID)->memberType == "Manager") {
                            cout << acfr << "Cannot delete the Manager!" << acr << endl;
                            break;
                        }

                        if (DBMgr->getUser(ID)->getDue() > 0) {
                            cout << acfr << "Employee has dues! Cannot delete." << acr << endl;
                            cout << "Do you want to clear the dues? (y/n): ";
                            std::string confirm;
                            cin >> (confirm);

                            if (confirm[0] == 'y' || confirm[0] == 'Y') {
                                DBMgr->getUser(ID)->clearDues();
                                cout << acfg << "Dues cleared successfully." << acr << endl;
                            } else
                                break;
                        }

                        pak2c();

                        employee = DBMgr->getEmployee(ID);
                        cout << dottedred;
                        employee->getDetails();
                        cout << dottedred;

                        cout << "Are you sure you want to delete this employee? (y/n): ";
                        std::string confirm;
                        cin >> (confirm);

                        if (confirm[0] == 'y' || confirm[0] == 'Y') {
                            DBMgr->removeEmployee(ID);

                            cout << acfr << "Employee deleted successfully." << acr << endl;
                        }

                    } else if (action[0] == 'n' || action[0] == 'N') {
                        break;
                    } else {
                        clearScreen();
                        cout << acfr << "Invalid action. Please try again." << acr << endl;
                    }

                    pak2c();
                    break;
                }
                case 6: {
                    cout << "Logging out...\n";
                    DBMgr->exportData();
                    Sleep(400);
                    return;
                }
                default: {
                    clearScreen();
                    cout << acfr << "Invalid choice. Please try again." << acr << endl;
                }
            }

            DBMgr->exportData();
            DBMgr->importData();

        } while (choice != 6);
    }

    DBMgr->exportData();
}

//// Storage for static members     //////////////////////////////////////

std::map<std::string, Customer*> DBMgr::Customers;
std::map<std::string, Employee*> DBMgr::Employees;
std::map<std::string, Car*> DBMgr::Cars;

//// Main Function                  //////////////////////////////////////

int main() {
    INIT_FUN();

    DBMgr dbmgr;
    DBMgr* DBMgr = &dbmgr;

    bool isRunning = true;

    DBMgr->importData();

    User currentUser;
    User* LoggedInUser = &currentUser;

    do {
        Login(DBMgr, LoggedInUser, isRunning);
    } while (isRunning);

    DBMgr->exportData();

    EXIT_FUN();

    return 0;
}