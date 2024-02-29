//// Includes                     //////////////////////////////////////

#include "include/global.h"     // Include the global header file
#include "include/dbf.h"        // Include the database functions header file
#include "include/auth.h"       // Include the authentication header file
#include "include/help.h"       // Include the helper functions header file
#include "include/classes.h"    // Include the classes header file
#include "include/classes.cpp"  // Include the classes implementation file

void Login(God& God, User& currentUser, bool& isRunning)
{
    clearScreen();

    God.importData();

    cout << "Welcome to " << ANSI_COLOR_FG_GREEN << "CaR-e-MaSyS!\n" << ANSI_COLOR_RESET;
    cout << "Do you wish to \n" << ANSI_COLOR_FG_GREEN << "register (r)" << ANSI_COLOR_RESET << " or " << ANSI_COLOR_FG_YELLOW << "login (l)" << ANSI_COLOR_RESET << " or " << ANSI_COLOR_FG_RED << "quit (q)? : " << ANSI_COLOR_RESET;

    std::string action, role;

    while((action != "r") || (action != "l") || (action != "q")) {
        cin >> action;
        if(action == "q") {
            isRunning = false;
            return;
        }
        else if (action == "r") {
            while((role != "c") || (role != "e"))
            {
                cout << "Please select your role: \n Customer (c) or Employee (e) : ";
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
                cout << "Enter an ID: ";
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

                if(auth != true) cout << ANSI_COLOR_FG_RED << "Invalid ID or password! Please try again.\n" << ANSI_COLOR_RESET;
            }

            currentUser = God.getUser(ID);
            std::string rolee = currentUser.memberType;
            if(rolee == "Customer")
                role = "c";
            else if(rolee == "Employee")
                role = "e";
            else if(rolee == "Manager") 
                role = "m";

            cout << "You have successfully logged in as " << ((rolee == "Employee")? "an " : "a ") << rolee << "!\n";

            break;
        } 
        else {
            clearScreen();
            cerr << ANSI_COLOR_FG_RED << "Invalid action!\n" << ANSI_COLOR_RESET << "Please choose 'register' or 'login' (or 'quit') (type 'r' or 'l' or 'q'). : ";
        }
    }

    God.exportData();
    God.importData();
    
    // Main menu

    if(role == "c" || role == "e") {
        int choice;
        do {
            // Display menu
            Sleep(1000);
            clearScreen();

            currentUser.getDetails();

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

            if(cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');

                clearScreen();
                cout << ANSI_COLOR_FG_RED << "Invalid input. Please try again." << ANSI_COLOR_RESET << endl;
                continue;
            }

            // Process user's choice
            std::string rent, regNo;
            switch (choice) {
                case 1:
                    // Browse & Rent
                    
                    cout << "All cars available : " << endl;
                    God.showAllCarsSecure();

                    cout << dottedred;
                    
                    pak2c();

                    cout << "Do you want to rent a car? (y/n): ";
                    cin >> rent;

                    if(rent == "y" || rent == "Y") {
                        cout << "Enter the registration number of the car you want to rent: ";
                        cin >> regNo;

                        std::transform(regNo.begin(), regNo.end(), regNo.begin(), ::toupper);

                        if(God.findCar(regNo)) {
                            Car car = God.getCar(regNo);

                            if(currentUser.getRecord() < 0) {
                                cout << ANSI_COLOR_FG_RED << "You have a negative record. You cannot rent a car." << endl;
                                pak2c();
                                break;
                            }
                            else if(car.getisRented()) {
                                cout << ANSI_COLOR_FG_RED << "Car is already rented!" << endl;
                                pak2c();
                                break;
                            }
            
                            car.rentRequest(currentUser);
                            currentUser.rentCar(car);
                            currentUser.addRent(car);

                            God.updateCar(car);
                            God.updateUser(currentUser);
                        }
                        else {
                            cout << ANSI_COLOR_FG_RED "Car not found!" << ANSI_COLOR_RESET << "Please recheck details." << endl;
                        }
                    }

                    pak2c();
                    break;
                case 2:

                    cout << "Rented cars: " << endl;
                    currentUser.showMyCars();

                    pak2c();
                    break;
                case 3:

                    if(currentUser.getRentedCars().size() == 0) {
                        cout << ANSI_COLOR_FG_RED << "You have not rented any cars!" << endl;
                        pak2c();
                        break;
                    }

                    cout << "Do you want to view the cars you have rented? (y/n): ";
                    cin >> rent;
                    
                    if(rent == "y" || rent == "Y") {
                        currentUser.showMyCars();
                        pak2c();
                    }

                    cout << "Enter the registration number of the car you want to return: ";
                    cin >> regNo;

                    cout << "How many days did you (actually) rent the car for? ";
                    int days;
                    cin >> days;

                    cout << "Enter the condition of the car (0 - 100): ";
                    float condition;
                    cin >> condition;

                    std::transform(regNo.begin(), regNo.end(), regNo.begin(), ::toupper);

                    if(God.findCar(regNo)) {
                        Car car = God.getCar(regNo);

                        if(!car.getisRented()) {
                            cout << ANSI_COLOR_FG_RED << "Car is not rented!" << endl;
                            pak2c();
                            break;
                        }

                        if(currentUser.getRentedCars().size() == 0) {
                            cout << ANSI_COLOR_FG_RED << "You have not rented any cars!" << endl;
                            pak2c();
                            break;
                        }

                        car.updateCondition(condition);
                        car.returnRequest(currentUser);
                        currentUser.returnCar(car);

                        double fine = 0.0;
                        fine = (40 * (1 - currentUser.getRecord()) * (days - car.getExpectedDays()));
                        if(fine < 0) fine = 0.0;

                        double newRecord = currentUser.getRecord() - fine/100.0;

                        cout << dottedgreen;

                        if(days > car.getExpectedDays())
                        {
                            cout << "You have returned the car " << ANSI_COLOR_FG_RED << days - car.getExpectedDays() << ANSI_COLOR_RESET << " days late." << endl;
                        }
                        if(condition < 50)
                            {
                                cout << "The car is in " << ANSI_COLOR_FG_RED << "poor" << ANSI_COLOR_RESET << "condition." << endl;
                                fine *= (1 + 1 - condition/100.0);
                            }
                        else if(condition >= 80)
                        {
                            cout << "The car is in " << ANSI_COLOR_FG_GREEN << "good" << ANSI_COLOR_RESET << " condition." << endl;
                            int random = rand() % 10 + 1;
                            cout << "Thank you for taking care of the car. You will receive an additional discount of " << random << "%!" << endl;
                            fine += (-1 * car.getDailyRent() * car.getExpectedDays() * random / 100.0);
                        }
                        else
                        {
                            cout << "The car is in " << ANSI_COLOR_FG_YELLOW << "average" << ANSI_COLOR_RESET << " condition." << endl;
                        }

                        if(fine > 0.0)
                            cout << "Your fine is: Rs. " << ANSI_COLOR_FG_RED << fine << ANSI_COLOR_RESET << endl;
                        else
                            cout << "You have no fines." << endl;

                        currentUser.addFine(fine);

                        cout << "You have to pay: Rs. " << currentUser.getDue() << ANSI_COLOR_RESET << endl;

                        cout << dottedgreen;

                        God.updateCar(car);
                        God.updateUser(currentUser);
                    }
                    else {
                        cout << ANSI_COLOR_FG_RED "Car not found!" << ANSI_COLOR_RESET << "Please recheck details." << endl;
                    }

                    pak2c();
                    break;
                case 4:

                    for(auto car : currentUser.getRentedCars()) {
                        if(car.getisRented()) {
                            cout << "Dues for car " << car.getRegNo() << ": Rs. " << ANSI_COLOR_FG_RED << car.getDailyRent() * car.getExpectedDays() << ANSI_COLOR_RESET << endl;
                        }
                    }
                    
                    if(currentUser.getDue() > 0) {
                        cout << "After applying fines (if any), your total dues: Rs. " << ANSI_COLOR_FG_RED << currentUser.getDue() << ANSI_COLOR_RESET << endl;
                    }
                    else {
                        cout << "You have no dues." << endl;
                    }

                    pak2c();

                    cout << "Do you wish to clear your dues? (y/n): ";
                    cin >> rent;

                    if(rent == "y" || rent == "Y") {
                        currentUser.clearDues();
                        cout << ANSI_COLOR_FG_GREEN << "Dues cleared successfully." << endl;
                    }
                    
                    pak2c();
                    break;
                case 5:
                    cout << "Logging out...\n";
                    God.exportData();
                    Sleep(400);
                    return;
                default:

                    clearScreen();
                    cout << ANSI_COLOR_FG_RED << "Invalid choice. Please try again." << ANSI_COLOR_RESET << endl;
            }
        } while (choice != 5);
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

            cout << dottedyellow;

            cout << "\t 1. View All Cars" << endl;
            cout << "\t 2. Modify Cars (add/update/delete)" << endl;
            cout << "\t 3. View and Modify Customers (add/update/delete)" << endl;
            cout << "\t 4. View and Modify Employees (add/update/delete)" << endl;
            cout << "\t 5. Logout" << endl;

            cout << dottedyellow;

            cout << "Enter your choice: ";
            cin >> choice;

            if(cin.fail()) {
                cin.clear();
                
                cin.ignore(1000, '\n');

                clearScreen();
                cout << ANSI_COLOR_FG_RED << "Invalid input. Please try again." << ANSI_COLOR_RESET << endl;
                continue;
            }

            // Process user's choice
            std::string action, view;
            switch (choice) {
                case 1:
                    // View All Cars
                    God.showAllCars();
                    cout << dottedred;
  
                    pak2c();
                    break;
                case 2:
                    // Modify Cars
                    cout << "Do you want to add, update or delete a car? (a/u/d): ";
                    cin >> action;

                    cout << "Do you want to view all the cars first? (y/n): ";
                    cin >> view;

                    if(view == "y" || view == "Y") {
                        God.showAllCars();
                        cout << dottedred;
                    }

                    if (action == "a") {
                        // Add a car
                        Car car;
                        std::string model, regNo, renterID, dueDate;
                        float condition, dailyRent;
                        bool isRented;
                        int expectedDays;
                        
                        cout << "Enter the car model: ";
                        cin >> model;

                        cout << "Enter the registration number: ";
                        cin >> regNo;

                        std::transform(regNo.begin(), regNo.end(), regNo.begin(), ::toupper);

                        if(God.findCar(regNo)) {
                            cout << ANSI_COLOR_FG_RED << "Car already exists!" << ANSI_COLOR_RESET << "Please enter a unique Registration No." << endl;
                            break;
                        }

                        cout << "Enter the condition: ";
                        cin >> condition;

                        std::string isR;
                        cout << "Is it rented? (y/n): ";
                        cin >> isR;

                        isRented = (isR == "y" || isR == "Y") ? true : false;

                        if(isRented) {

                            cout << "Enter the renter's ID: ";
                            cin >> renterID;

                            cout << "Enter the due date: ";
                            cin >> dueDate;

                            cout << "Enter the expected number of days for rent: ";
                            cin >> expectedDays;
                        }
                        else {
                            isRented = false;
                            renterID = "";
                            dueDate = "";
                            expectedDays = 0;
                        }

                        car = Car(model, regNo, condition, isRented, renterID, dueDate, dailyRent, expectedDays);

                        cout << "Following are the details of the car you want to add: \n";
                        car.getDetails();

                        cout << "Are you sure you want to add this car? (y/n): ";
                        char confirm;
                        cin >> confirm;

                        if(confirm == 'y') {
                            God.addCar(car);
                        }
                        

                    } else if (action == "u" || action == "U") {
                        // Update a car
                        
                        Car car;
                        std::string regNo, renterID, dueDate;
                        float condition, dailyRent;
                        bool isRented;
                        std::string act;
                        int expectedDays;

                        cout << "Enter the registration number of the car you want to update: ";
                        cin >> regNo;

                        std::transform(regNo.begin(), regNo.end(), regNo.begin(), ::toupper);

                        if(!God.findCar(regNo)) {
                            cout << ANSI_COLOR_FG_RED << "Car not found!" << ANSI_COLOR_RESET << "Please enter corrrect Registration No." << endl;
                            break;
                        }

                        if(God.getCar(regNo).getisRented() == true) {
                            cout << ANSI_COLOR_FG_RED << "Car is currently rented!" << ANSI_COLOR_RESET << endl;
                            cout << "Are you sure you want to update this car? (y/n): ";
                            std::string confirm;
                            cin >> confirm;

                            if(confirm == "y" || confirm == "Y") {
                                continue;
                            }
                        }

                        cout << "Do you want to update the daily rent? (y/n): ";
                        cin >> act;

                        if(act == "y" || act == "Y") {
                            cout << "Enter the new daily rent: ";
                            cin >> dailyRent;
                        }
                        else
                            dailyRent = God.getCar(regNo).getDailyRent();

                        cout << "Do you want to update the condition? (y/n): ";
                        cin >> act;

                        if(act == "y" || act == "Y") {
                            cout << "Enter the new condition: ";
                            cin >> condition;
                        }
                        else
                            condition = God.getCar(regNo).getCondition();

                        cout << "Do you want to update the renter's details? (y/n): ";
                        cin >> act;

                        if(act == "y" || act == "Y") {
                            cout << "Is it still rented? (y/n): ";
                            std::string isR;
                            cin >> isR;

                            if(isR == "y" || isR == "Y") {
                                isRented = true;

                            cout << "Enter the renter's ID: ";
                            cin >> renterID;

                            cout << "Enter the due date: ";
                            cin >> dueDate;

                            cout << "Enter the expected number of days for rent: ";
                            cin >> expectedDays;

                            }
                            else {
                                isRented = false;
                                renterID = "";
                                dueDate = "";
                                expectedDays = 0;
                            }
                        }
                        else
                        {
                            isRented = God.getCar(regNo).getisRented();
                            renterID = God.getCar(regNo).getRenterID();
                            dueDate = God.getCar(regNo).getdueDate();
                            expectedDays = God.getCar(regNo).getExpectedDays();
                        }


                        car = Car(God.getCar(regNo).getModel(), regNo, condition, isRented, renterID, dueDate, dailyRent, expectedDays);
                        
                        God.updateCar(car);

                        if(isRented) {
                            User user = God.getUser(renterID);
                            user.addRent(car);
                            God.updateUser(user);
                        }

                    } else if (action == "d" || action == "D") {
                        // Delete a car
                        Car car;
                        std::string regNo;

                        cout << "Enter the registration number of the car you want to delete: ";
                        cin >> regNo;

                        std::transform(regNo.begin(), regNo.end(), regNo.begin(), ::toupper);

                        if(!God.findCar(regNo)) {
                            cout << ANSI_COLOR_FG_RED << "Car not found!" << ANSI_COLOR_RESET << "Please enter corrrect Registration No." << endl;
                            break;
                        }

                        cout << "Are you sure you want to delete this car? (y/n): ";
                        std::string confirm;
                        cin >> confirm;

                        if(confirm == "y" || confirm == "Y") {
                            if(God.getCar(regNo).getisRented()) {
                                cout << ANSI_COLOR_FG_RED << "Car is currently rented! Cannot delete." << ANSI_COLOR_RESET << endl;
                                break;
                            }
                            
                            God.removeCar(God.getCar(regNo));
                            cout << "Car deleted successfully." << endl;
                        }
                        
                    } else {
                        clearScreen();
                        cout << ANSI_COLOR_FG_RED << "Invalid action. Please try again." << ANSI_COLOR_RESET << endl;
                    }

                    pak2c();
                    break;
                case 3:

                    cout << "Do you want to view all the customers first? (y/n): ";
                    cin >> view;

                    if(view == "y" || view == "Y") {
                        God.showAllUsers("Customer");
                        cout << dottedred;
                    }

                    cout << "Do you want to add, update or delete a customer? (or neither) (a/u/d/n): ";
                    cin >> action;

                    if (action == "a") {
                        // Add a customer
                        Customer customer;
                        std::string CName, CID, CPassword;
                        
                        cout << "Enter the customer's Name: ";
                        cin >> CName;

                        bool unique_ID = false;
                        while(unique_ID == false) {
                            cout << "Enter a ID: ";
                            cin >> CID;
                            
                            //check if ID already exists

                            if (God.findUser(CID) == true){
                                cerr << "ID '" << CID << "' already exists. Please choose a different ID." << endl;
                            }
                            else {
                                unique_ID = true;
                            }
                        }

                        cout << "Create a password: ";
                        CPassword = getPassword();

                        customer = Customer(CName, CID, CPassword);

                        cout << "Following are the details of the customer you want to add: \n";
                        customer.getDetails();

                        cout << "Are you sure you want to add this customer? (y/n): ";
                        char confirm;
                        cin >> confirm;

                        if(confirm == 'y') {
                            God.addUser(customer);
                            cout << "Customer added successfully." << endl;
                        }
                        
                    } else if (action == "u" || action == "U") {
                        // Update a customer
                        
                        Customer customer;
                        std::string ID, password;
                        std::string act;

                        cout << "Enter the ID of the customer you want to update: ";
                        cin >> ID;

                        if(!God.findUser(ID)) {
                            cout << ANSI_COLOR_FG_RED << "Customer not found!" << ANSI_COLOR_RESET << "Please enter corrrect ID." << endl;
                            break;
                        }

                        cout << "Do you want to update the password? (y/n): ";
                        cin >> act;

                        if(act == "y" || act == "Y") {
                            cout << "Enter the new password: ";
                            password = getPassword();
                        }

                        customer = Customer(God.getUser(ID).getName(), ID, password);
                        God.updateUser(customer);

                    } else if (action == "d" || action == "D") {
                        // Delete a customer
                        Customer customer;
                        std::string ID;

                        cout << "Enter the ID of the customer you want to delete: ";
                        cin >> ID;

                        if(!God.findUser(ID)) {
                            cout << ANSI_COLOR_FG_RED << "Customer not found!" << ANSI_COLOR_RESET << "Please enter corrrect ID." << endl;
                            break;
                        }

                        if(God.getUser(ID).getRentedCars().size() > 0) {
                            cout << ANSI_COLOR_FG_RED << "Customer has rented cars! Cannot delete." << ANSI_COLOR_RESET << endl;
                            break;
                        }

                        cout << "Are you sure you want to delete this customer? (y/n): ";
                        customer.getDetails();
                        char confirm;
                        cin >> confirm;

                        if(confirm == 'y') {
                            God.removeUser(God.getUser(ID));
                            cout << "Customer deleted successfully." << endl;
                        }
                        
                    } 
                    else if(action == "n" || action == "N") {
                        break;
                    }
                    else {
                        clearScreen();
                        cout << ANSI_COLOR_FG_RED << "Invalid action. Please try again." << ANSI_COLOR_RESET << endl;
                    }

                    pak2c();
                    break;
                case 4:

                    cout << "Do you want to view all the employees first? (y/n): ";
                    cin >> view;

                    if(view == "y" || view == "Y") {
                        God.showAllUsers("Employee");
                        cout << dottedred;
                    }

                    cout << "Do you want to add, update or delete an employee? (or neither) (a/u/d/n): ";
                    cin >> action;

                    if (action == "a") {
                        // Add an employee
                        Employee employee;
                        std::string EName, EID, EPassword;
                        
                        cout << "Enter the employee's Name: ";
                        cin >> EName;

                        bool unique_ID = false;
                        while(unique_ID == false) {
                            cout << "Enter a ID: ";
                            cin >> EID;
                            
                            //check if ID already exists

                            if (God.findUser(EID) == true){
                                cerr << "ID '" << EID << "' already exists. Please choose a different ID." << endl;
                            }
                            else {
                                unique_ID = true;
                            }
                        }

                        cout << "Create a password: ";
                        EPassword = getPassword();

                        employee = Employee(EName, EID, EPassword);

                        cout << "Following are the details of the employee you want to add: \n";
                        employee.getDetails();

                        cout << "Are you sure you want to add this employee? (y/n): ";
                        char confirm;
                        cin >> confirm;

                        if(confirm == 'y') {
                            God.addUser(employee);
                            cout << "Employee added successfully." << endl;
                        }
                        
                    } else if (action == "u" || action == "U") {
                        // Update an employee
                        
                        Employee employee;
                        std::string ID, password;
                        std::string act;

                        cout << "Enter the ID of the employee you want to update: ";
                        cin >> ID;

                        if(!God.findUser(ID)) {
                            cout << ANSI_COLOR_FG_RED << "Employee not found!" << ANSI_COLOR_RESET << "Please enter corrrect ID." << endl;
                            break;
                        }

                        cout << "Do you want to update the password? (y/n): ";
                        cin >> act;

                        if(act == "y" || act == "Y") {
                            cout << "Enter the new password: ";
                            password = getPassword();
                        }

                        employee = Employee(God.getUser(ID).getName(), ID, password);
                        God.updateUser(employee);

                    } else if (action == "d" || action == "D") {
                        // Delete an employee
                        Employee employee;
                        std::string ID;

                        cout << "Enter the ID of the employee you want to delete: ";
                        cin >> ID;

                        if(!God.findUser(ID)) {
                            cout << ANSI_COLOR_FG_RED << "Employee not found!" << ANSI_COLOR_RESET << "Please enter corrrect ID." << endl;
                            break;
                        }

                        if(God.getUser(ID).getRentedCars().size() > 0) {
                            cout << ANSI_COLOR_FG_RED << "Employee has rented cars! Cannot delete." << ANSI_COLOR_RESET << endl;
                            break;
                        }

                        cout << "Are you sure you want to delete this employee? (y/n): ";
                        employee.getDetails();
                        char confirm;
                        cin >> confirm;

                        if(confirm == 'y') {
                            God.removeUser(God.getUser(ID));
                            cout << "Employee deleted successfully." << endl;
                        }
                        
                    } 
                    else if(action == "n" || action == "N") {
                        break;
                    }
                    else {
                        clearScreen();
                        cout << ANSI_COLOR_FG_RED << "Invalid action. Please try again." << ANSI_COLOR_RESET << endl;
                    }

                    pak2c();
                    break;
                case 5:
                    cout << "Logging out...\n";
                    God.exportData();
                    Sleep(400);
                    return;
                default:

                    clearScreen();
                    cout << ANSI_COLOR_FG_RED << "Invalid choice. Please try again." << ANSI_COLOR_RESET << endl;
            }
        } while (choice != 5);
    }

    God.exportData();
}

//// Storage for static members  //////////////////////////////////////

std::map<std::string, User> God::Users;
std::map<std::string, Car> God::Cars;

//// Main Function                //////////////////////////////////////

int main() {

    Sleep(300);
    cout << "Welcome to Car Rental System!!. Working on " << get_platform_name() << " platform." << endl;

    Sleep(1000);
    
    God God;

    bool isRunning = true;

    God.importData();

    do {
    User currentUser;
    Login(God, currentUser, isRunning);
    } while (isRunning);

    God.exportData();

    clearScreen();
    cout << ANSI_COLOR_FG_YELLOW << "##########      Thank you for using CaR-e-MaSyS!      ##########" << ANSI_COLOR_RESET << endl;
    cout << ANSI_COLOR_FG_GREEN << "##########                  Goodbye!                  ##########" << ANSI_COLOR_RESET << endl;
    Sleep(400);

    return 0;
}