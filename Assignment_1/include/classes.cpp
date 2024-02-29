#include "classes.hpp"
#include "global.hpp"

//// God Class Functions          //////////////////////////////////////

void God::addUser(User *user) {
    *Users[user->getID()] = *user;
}

void God::updateUser(User *user) {
    *Users[user->getID()] = *user;
}

void God::removeUser(User *user) {
    Users.erase(user->getID());
}

void God::addCar(Car *car) {
    *Cars[car->getRegNo()] = *car;
}

void God::updateCar(Car *car) {
    *Cars[car->getRegNo()] = *car;
}

void God::removeCar(Car *car) {
    Cars.erase(car->getRegNo());
}

void God::showAllUsers(std::string memberType) {
    for (auto user : Users) {
        if (user.se->memberType == memberType) {
            cout << dottedred;
            cout << "Name          : " << acfy << std::left << std::setw(30) << user.se->getName() << "\t"
                 << acr << std::right << std::setw(20) << "ID : " << std::left << acfy << std::right << std::setw(10) << user.se->getID() << acr << endl;

            cout << "# Rented Cars : " << acfg << std::left << std::setw(30) << user.se->rentedCars.size() << "\t"
                 << acr << std::right << std::setw(20) << "Payment Due : " << std::left << acfr << std::right << std::setw(10) << std::fixed << std::setprecision(2) << user.se->due << acr << endl;

            if (user.se->rentedCars.size() > 0) cout << "\nCars Rented ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n";
                                                          
            for (auto car : user.se->rentedCars) {
                cout << "Model : " << acfy << std::left << std::setw(22) << car->getModel()
                     << std::right << std::setw(21) << acr << "Registration No. : " << acfy << std::setw(12) << car->getRegNo() << acr << endl;
                cout << "Condition : " << acfg << std::left << std::setw(5);

                float cond = car->getCondition();

                if (cond < 30)
                    cout << acfr;
                else if (cond < 60)
                    cout << acfy;
                else
                    cout << acfg;

                cout << std::setprecision(2) << car->getCondition() << acr << "\t"
                     << std::right << std::setw(27) << acr << "Due Date : " << acfg << std::setw(20) << car->getDueDate() << acr << endl;
                cout << endl;
            }
        }
    }
    cout << dottedred;
}

void God::showAllCars() {
    for (auto car : Cars) {
        cout << dottedred;
        cout << "Registration No. : " << car.se->getRegNo() << "\n";
        cout << "Model : " << car.se->getModel() << "\n";

        float cond = car.se->getCondition();

        cout << "Condition : " << std::setprecision(2);
        if (cond < 30)
            cout << acfr;
        else if (cond < 60)
            cout << acfy;
        else
            cout << acfg;

        cout << car.se->getCondition() << acr << "\n";

        cout << "Rented : " << (car.se->getisRented() ? "YES" : "NO") << "\n";
        if (car.se->getisRented() == 1) {
            cout << "Renter ID : " << car.se->getRenterID() << "\n";
            cout << "Renter Name : " << Users[car.se->getRenterID()]->getName() << "\n";
            cout << "Due Date : " << car.se->getDueDate() << "\n";
        }
    }
}

void God::showAllCarsSecure() {
    for (auto car : Cars) {
        cout << dottedred;
        cout << "Model : " << acfy << std::setw(30) << car.se->getModel() << acr << "\t\tRegistration No. : " << acfy << car.se->getRegNo() << acr << "\n";
        float cond = car.se->getCondition();

        cout << "Condition : " << std::setprecision(2);
        if (cond < 30)
            cout << acfr;
        else if (cond < 60)
            cout << acfy;
        else
            cout << acfg;

        cout << std::setw(26) << car.se->getCondition() << acr << "\t\tAvailable : ";
        if(car.se->getisRented() == 1) {
            cout << acfr << "NO\n" << acr;
        } else {
            cout << acfg << "YES\n" << acr;
        }

        if (car.se->getisRented() == 1) {
            cout << "Expected Availability by : " << acfg << car.se->getDueDate() << acr << "\n";
        }
    }
}

bool God::findUser(std::string ID) {
    return Users.find(ID) != Users.end();
}

bool God::findUserbyName(std::string name) {
    for (auto user : Users) {
        std::string s = user.se->getName();

        transform(s.begin(), s.end(), s.begin(), ::toupper);
        transform(name.begin(), name.end(), name.begin(), ::toupper);

        if (s == name) {
            return true;
        }
    }
    return false;
}

User *God::getUserbyName(std::string name) {
    for (auto user : Users) {
        std::string s = user.se->getName();

        transform(s.begin(), s.end(), s.begin(), ::toupper);
        transform(name.begin(), name.end(), name.begin(), ::toupper);

        if (s == name) {
            return Users[user.se->getID()];
        }
    }
}

bool God::findCarbyModel(std::string model) {
    for (auto car : Cars) {
        std::string s = car.se->getModel();

        transform(s.begin(), s.end(), s.begin(), ::toupper);
        transform(model.begin(), model.end(), model.begin(), ::toupper);

        if (s == model) {
            return true;
        }
    }
    return false;
}

Car *God::getCarbyModel(std::string model) {
    for (auto car : Cars) {
        std::string s = car.se->getModel();

        transform(s.begin(), s.end(), s.begin(), ::toupper);
        transform(model.begin(), model.end(), model.begin(), ::toupper);

        if (car.se->getModel() == model) {
            return Cars[car.se->getRegNo()];
        }
    }
}

bool God::findCar(std::string regNo) {
    return Cars.find(regNo) != Cars.end();
}

bool God::login(std::string ID, std::string password) {
    if (findUser(ID)) {
        // cout << Users[ID]->name << " ";
        // cout << Users[ID]->ID << " " << password << endl;
        // cout << Users[ID]->getPassword() << " " << password << endl;
        return Users[ID]->getPassword() == password;
        // return true;
    } else {
        return false;
    }
}

User *God::getUser(std::string ID) {
    return Users[ID];
}

Car *God::getCar(std::string regNo) {
    return Cars[regNo];
}

std::map<std::string, User*> God::getUsers() {
    return Users;
}

std::map<std::string, Car*> God::getCars() {
    return Cars;
}

//// Car Class Functions          //////////////////////////////////////

void Car::getDetails() {
    cout << "Model: " << model << endl;
    cout << "Condition: " << std::setprecision(2) << condition << endl;
    cout << "Rented: " << (isRented ? "YES" : "NO") << endl;
    if (isRented) {
        cout << "Renter ID: " << renterID << endl;
        cout << "Due Date: " << getDueDate() << endl;
    }
}

void Car::rentRequest(User *user) {
    isRented = true;
    renterID = user->getID();
    cout << acfg << "Car rented successfully!" << acr << endl;
    getDetails();
}

void Car::updateRentDate(Date date) {
    rentDate = date;
}

void Car::returnRequest(User *user) {
    if (isRented && renterID == user->getID()) {
        isRented = false;
        renterID = "";
        this->rentDate = Date(1, 1, 2001);
        this->expectedDays = 5;
        cout << "Car returned successfully." << endl;
    } else {
        cout << "You have not rented this car." << endl;
    }
}

// //// User Class Functions      //////////////////////////////////////

void User::rentCar(Car *car) {
    if (rentedCars.size() >= rentLimit) {
        cout << acfr << "You have reached your rent limit." << endl;
    } else {
        rentedCars.push_back(car);
    }
}

void User::returnCar(Car *car) {
    for (auto it = rentedCars.begin(); it != rentedCars.end(); it++) {
        if ((*it)->getRegNo() == car->getRegNo()) {
            rentedCars.erase(it);
            break;
        }
    }
}

void User::showMyCars() {
    if (rentedCars.size() == 0) {
        cout << acfr << "You have not rented any cars!" << endl;

    } else {
        cout << "You have rented the following cars:" << endl;
    }

    for (auto car : rentedCars) {
        cout << dottedred;
        cout << "Registration No. : " << car->getRegNo() << "\n";
        cout << "Model : " << car->getModel() << "\n";
        float cond = car->getCondition();

        cout << "Condition : " << std::setprecision(2);
        if (cond < 30)
            cout << acfr;
        else if (cond < 60)
            cout << acfy;
        else
            cout << acfg;

        cout << car->getCondition() << acr << "\n";
        // cout << "Due Date : " << car->getDueDate() << "\n";
    }

    cout << dottedred;
}

void User::addRent(Car *car) {
    if (memberType == "Employee")
        due += 0.85 * car->getDailyRent() * car->getExpectedDays();
    else
        due += car->getDailyRent() * car->getExpectedDays();
}

void User::getDetails() {
    cout << "Name          : " << acfy << std::left << std::setw(30) << name << "\t"
         << acr << std::right << std::setw(20) << "ID : " << std::left << acfy << std::right << std::setw(10) << ID << acr << endl;

    cout << "# Rented Cars : " << acfg << std::left << std::setw(30) << rentedCars.size() << "\t"
         << acr << std::right << std::setw(20) << "Payment Due : " << std::left << acfr << std::right << std::setw(10) << std::fixed << std::setprecision(2) << due << acr << endl;

    cout << acfy << memberType << acr << " Account" << std::left << std::setw(30) << "\t"
         << std::right << std::setw(15) << "Rent Limit : " << std::right << std::setw(14) << acfg << rentLimit << acr << endl;

    cout << "Record        : ";

    if (record < 0)
        cout << acfr;
    else
        cout << acfg;

    cout << std::fixed << std::setprecision(2) << record << acr << endl;
    cout << dottedred;
}
