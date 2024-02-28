#ifndef CLASSES_H
#define CLASSES_H

#include "global.h"

//// Class Declarations           //////////////////////////////////////

class God;
class User;
class Customer;
class Employee;
class Manager;
class Car;

//// User Class                  //////////////////////////////////////

class User {
protected:
    std::string name = "";    
    std::string ID = "";
    std::string password = "";
    double record = 0.0;
    double fine = 0.0;
    std::vector<Car> rentedCars;

public:
    int rentLimit = 0;
    
    void getDues(int today);
    void clearDue() { fine = 0.0; }
    void rentCar(Car &car);
    void returnCar(Car &car);

    void showMyCars();

    double getRecord() const { return record; }
    double getFine() const { return fine; }

    // void Logout();

    std::string memberType = "";

    User() {};

    User(const std::string& name, std::string ID, const std::string& password)
        : name(name), ID(ID), password(password) {}

    std::string getName() const { return name; }
    std::string getID() const { return ID; }
    std::string getPassword() const { return password; }
    
    void getDetails() const {
        cout << "Name: " << name << "\t\t ID : " << ID << endl;
        cout << "Member Type: " << memberType << "\tToday's Date : 01/01/2021\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }
    
    friend Manager;
    friend God;

    void fetchDB(std::string ID);
    void updateDB(std::string ID);
};

// Also add Help function

//// Customer Class               //////////////////////////////////////

class Customer : public User {    
public:
    Customer(const std::string& name, std::string ID, const std::string& password)
        : User(name, ID, password) {
        memberType = "Customer";
    }

    void getRentedCars();
    void getCustomerRecord () const { cout << "Customer record: " << record << endl; }
};

//// Employee Class               //////////////////////////////////////

class Employee : public User {

public:
    Employee(const std::string& name, std::string ID, const std::string& password)
        : User(name, ID, password) {
        memberType = "Employee";
    }

    void getRentedCars();
    void getEmployeeRecord () const { cout << "Employee record: " << record << endl; }
};

//// Car Class                    //////////////////////////////////////

class Car {
protected:
    std::string model = "";
    std::string regNo = "";
    float condition = 0.0;
    bool isRented = false;
    std::string renterID = "";
    std::string dueDate = "";
public:

    Car() {};

    Car(std::string model, std::string regNo, float condition, bool isRented, std::string renterID, std::string dueDate)
        : model(model), regNo(regNo), condition(condition), isRented(isRented), renterID(renterID), dueDate(dueDate) {}


    std::string getModel() const { return model; }
    std::string getRegNo() const { return regNo; }
    float getCondition() const { return condition; }
    bool getisRented() const { return isRented; }
    std::string getRenterID() const { return renterID; }
    std::string getdueDate() const { return dueDate; }

    void showDueDate() const {
        cout << "Due date: " << dueDate << endl;
    }

    void getDetails() const {
        cout << "Model: " << model << endl;
        cout << "Condition: " << condition << endl;
        cout << "Rented: " << (isRented ? "Yes" : "No") << endl;
    }

    void rentRequest(const User& user) {
        if (isRented) {
            cout << "Car is already rented." << endl;
        } else {
            isRented = true;
            renterID = user.getID();
            cout << "Car rented successfully." << endl;
            getDetails();
        }
    }

    void fetchDB();
    void updateDB();

    friend Manager;
};

//// God Class                    //////////////////////////////////////

class God {
protected:
    std::map<std::string, User> Users;
    std::map<std::string, Car> Cars;

public:
    bool findUser(std::string ID);
    bool findCar(std::string regNo);

    void addUser(User &user);
    void updateUser(User &user);
    void removeUser(User &user);

    void addCar(Car &car);
    void updateCar(Car &car);
    void removeCar(Car &car);

    void showAllUsers();
    void showAllCars();

    bool login(std::string ID, std::string password);
    void logout();

    User& getUser(std::string ID);
    Car& getCar(std::string regNo);

    void importData();
    void exportData();
    
};

//// Manager Class                //////////////////////////////////////

class Manager : public User {
protected:
public:
    Manager () {};

    Manager(const std::string& name, std::string ID, const std::string& password)
        : User(name, ID, password) {
        memberType = "Manager";
    }
};

#endif // CLASSES_H