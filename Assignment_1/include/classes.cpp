#include "classes.h"
#include "global.h"

//// God Class Functions          //////////////////////////////////////

void God::addUser(User &user) {
    Users[user.getID()] = user;
}

void God::updateUser(User &user) {
    Users[user.getID()] = user;
}

void God::removeUser(User &user) {
    Users.erase(user.getID());
}

void God::addCar(Car &car) {
    Cars[car.getRegNo()] = car; 
}

void God::updateCar(Car &car) {
    Cars[car.getRegNo()] = car;
}

void God::removeCar(Car &car) {
    Cars.erase(car.getRegNo());
}

void God::showAllUsers(std::string memberType) {
    for (auto user : Users) {
        cout << dottedred;
        if(user.se.memberType == memberType ) {
            cout << "Name  : " << user.se.getName() << "\t" << std::setw(29) << std::right << "ID : " << user.se.getID() << endl;
            cout << "# Rented Cars : " << ANSI_COLOR_FG_GREEN << user.se.rentedCars.size() << ANSI_COLOR_RESET << "\t" << std::setw(29) << std::right << "Payment Due : " << ANSI_COLOR_FG_RED << user.se.due << ANSI_COLOR_RESET << endl;
            cout << "Cars Rented : \n";
            for(auto car : user.se.rentedCars) {
                cout << "Model : " << car.getModel() << "\t" << std::setw(29) << std::right << "Registration No. : " << car.getRegNo() << endl;
            }
        }
    }
    cout << dottedred;
}

void God::showAllCars() {
    for (auto car : Cars) {
        cout << dottedred;
        cout << "Registration No. : " << car.se.getRegNo() << "\n";
        cout << "Model : " << car.se.getModel() << "\n";
        cout << "Condition : " << std::setprecision(2) << car.se.getCondition() << "\n";
        cout << "Rented : " << (car.se.getisRented() ? "YES" : "NO") << "\n";
        if(car.se.getisRented() == 1) {
        cout << "Renter ID : " << car.se.getRenterID() << "\n";
        cout << "Renter Name : " << Users[car.se.getRenterID()].getName() << "\n";
        cout << "Due Date : " << car.se.getdueDate() << "\n";
        }
    }
}

void God::showAllCarsSecure() {
    for (auto car : Cars) {
        cout << dottedred;
        cout << "Registration No. : " << car.se.getRegNo() << "\n";
        cout << "Model : " << car.se.getModel() << "\n";
        cout << "Condition : " << std::setprecision(2) << car.se.getCondition() << "\n";
        cout << "Available : " << ((car.se.getisRented() == 1)? "NO" : "YES") << "\n";
        if(car.se.getisRented() == 1) {
            cout << "Expected Availability by : " << car.se.getdueDate() << "\n";
        }
    }
}

bool God::findUser(std::string ID) {
    return Users.find(ID) != Users.end();
}

bool God::findCar(std::string regNo) {
    return Cars.find(regNo) != Cars.end();
}

bool God::login(std::string ID, std::string password) {
    if (findUser(ID)) {
        return Users[ID].getPassword() == password;
    } else {
        return false;
    }
}

User& God::getUser(std::string ID) {
    return Users[ID];
}

Car& God::getCar(std::string regNo) {
    return Cars[regNo];
}

//// Car Class Functions          //////////////////////////////////////

void Car::getDetails()  {
    cout << "Model: " << model << endl;
    cout << "Condition: " << std::setprecision(2) << condition << endl;
    cout << "Rented: " << (isRented ? "YES" : "NO") << endl;
    if(isRented) {
        cout << "Renter ID: " << renterID << endl;
        cout << "Due Date: " << dueDate << endl;
    }
}

void Car::rentRequest(User& user) {
    isRented = true;
    renterID = user.getID();
    cout << ANSI_COLOR_FG_GREEN << "Car rented successfully!" << endl;
    getDetails();
}

void Car::returnRequest(User& user) {
    if (isRented && renterID == user.getID()) {
        isRented = false;
        renterID = "";
        cout << "Car returned successfully." << endl;
    } else {
        cout << "You have not rented this car." << endl;
    }
}

// //// User Class Functions      //////////////////////////////////////

void User::rentCar(Car &car) {
    if (rentedCars.size() >= rentLimit) {
        cout << ANSI_COLOR_FG_RED << "You have reached your rent limit." << endl;
    } else {
        rentedCars.push_back(car);
    }
}

void User::returnCar(Car &car) {
    for (auto it = rentedCars.begin(); it != rentedCars.end(); it++) {
        if (it->getRegNo() == car.getRegNo()) {
            rentedCars.erase(it);
            break;
        }
    }
}

void User::showMyCars() {
    if(rentedCars.size() == 0) {
        cout << ANSI_COLOR_FG_RED << "You have not rented any cars!" << endl;
        
    } else {
        cout << "You have rented the following cars:" << endl;
    }

    for (auto car : rentedCars) {
        cout << dottedred;
        cout << "Registration No. : " << car.getRegNo() << "\n";
        cout << "Model : " << car.getModel() << "\n";
        cout << "Condition : " << std::setprecision(2) << car.getCondition() << "\n";
        cout << "Due Date : " << car.getdueDate() << "\n";
    }

    cout << dottedred;

}

void User::calculateDue () {
    
}

void User::addRent(Car &car) {
    if(memberType == "Employee")
        due += 0.85 * car.getDailyRent() * car.getExpectedDays();
    else
        due += car.getDailyRent() * car.getExpectedDays();
    
}

void User::getDetails() {
    cout << "Name  : " << name << "\t" << std::setw(29) << std::right << "ID : " << ID << endl;
    cout << "# Rented Cars : " << ANSI_COLOR_FG_GREEN << rentedCars.size() << ANSI_COLOR_RESET << "\t" << std::setw(29) << std::right << "Payment Due : " << ANSI_COLOR_FG_RED << due << ANSI_COLOR_RESET << endl;
    cout << ANSI_COLOR_FG_YELLOW << memberType << ANSI_COLOR_RESET << " Account" << "\t" << std::setw(29) << std::right << "Rent Limit : " << ANSI_COLOR_FG_GREEN << rentLimit << ANSI_COLOR_RESET << endl;
    cout << dottedred;
}


