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

void God::showAllUsers() {
    for (auto user : Users) {
        cout << user.se.getName() << " " << user.se.getID() << " " << user.se.memberType << endl;
    }
}

void God::showAllCars() {
    for (auto car : Cars) {
        cout << "--------------------------------------------------------\n";
        cout << "Registration No. : " << car.se.getRegNo() << "\n";
        cout << "Model : " << car.se.getModel() << "\n";
        cout << "Condition : " << car.se.getCondition() << "\n";
        cout << "Rented : " << car.se.getisRented() << "\n";
        cout << "Renter ID : " << car.se.getRenterID() << "\n";
        cout << "Due Date : " << car.se.getdueDate() << "\n";
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

// //// User Class Functions      //////////////////////////////////////

// void User::rentCar(Car &car) {
//     if (rentedCars.size() >= rentLimit) {
//         cout << "You have reached your rent limit." << endl;
//     } else {
//         car.rentRequest(*this);
//         rentedCars.push_back(car);
//     }
// }

// //// Manager Class Functions      //////////////////////////////////////

// void Manager::addCar(Car &car) {
    
// }

// void Manager::removeCar(Car &car) {

  
// }

// void Manager::updateCar(Car &car) {
//     car.updateDB();
// }

// void Manager::addUser(User &user) {
    
// }

// void Manager::removeUser(User &user) {
   
// }

// void Manager::updateUser(User &user) {
//     user.updateDB();
// }

// //// Car Class Functions         //////////////////////////////////////

// void Car::fetchDB({
   
// }

// void Car::updateDB({

    
// }
