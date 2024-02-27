#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string>
#include <vector>
#include "sqlite/sqlite3.h"
using namespace std;

//// Class Declarations           //////////////////////////////////////

class User;
class Customer;
class Employee;
class Manager;
class Car;

//// User Class                  //////////////////////////////////////

class User {
protected:
    string name = "";    
    string ID = "";
    string password = "";
    double record = 0.0;
    double fine = 0.0;
    vector<Car> rentedCars;

public:
    int rentLimit = 0;
    
    void getDues(int today);
    void clearDue() { fine = 0.0; }
    void rentCar(Car &car);
    void returnCar(Car &car);
    void showAllCars(sqlite3* db);
    void showMyCars();

    double getRecord() const { return record; }
    double getFine() const { return fine; }

    // void Logout();

    string memberType = "";

    User() {};

    User(const string& name, string ID, const string& password)
        : name(name), ID(ID), password(password) {}

    string getName() const { return name; }
    string getID() const { return ID; }
    string getPassword() const { return password; }
    
    void getDetails() const {
        cout << "Name: " << name << "\t\t ID : " << ID << endl;
        cout << "Member Type: " << memberType << "\tToday's Date : 01/01/2021\n";
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }
    
    friend Manager;

    void fetchDB(sqlite3* db, string ID);
    void updateDB(sqlite3* db, string ID);
};

// Also add Help function

//// Customer Class               //////////////////////////////////////

class Customer : public User {    
public:
    Customer(const string& name, string ID, const string& password)
        : User(name, ID, password) {
        memberType = "Customer";
    }

    void getRentedCars();
    void getCustomerRecord () const { cout << "Customer record: " << record << endl; }
};

//// Employee Class               //////////////////////////////////////

class Employee : public User {

public:
    Employee(const string& name, string ID, const string& password)
        : User(name, ID, password) {
        memberType = "Employee";
    }

    void getRentedCars();
    void getEmployeeRecord () const { cout << "Employee record: " << record << endl; }
};

//// Manager Class                //////////////////////////////////////

class Manager : public User {
public:
    Manager(const string& name, string ID, const string& password)
        : User(name, ID, password) {
        memberType = "Manager";
    }

    void addUser(sqlite3* db, User &user);
    void removeUser(sqlite3* db, User &user);
    void updateUser(sqlite3* db, User &user);

    void addCar(sqlite3* db, Car &car);
    void removeCar(sqlite3* db, Car &car);
    void updateCar(sqlite3* db, Car &car);

};

//// Car Class                    //////////////////////////////////////

class Car {
public:
    string model = "";
    string regNo = "";
    float condition = 0.0;
    bool isRented = false;
    string renterID = "";
    string renterName = "";
    string renterType = "";
    string dueDate = "";

    Car() {};

    Car(string model, string regNo, float condition)
        : model(model), regNo(regNo), condition(condition), isRented(false) {}

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
            renterName = user.getName();
            renterType = user.memberType;
            cout << "Car rented successfully." << endl;
            getDetails();
        }
    }

    void fetchDB(sqlite3* db);
    void updateDB(sqlite3* db);

    friend Manager;
};

#endif // CLASSES_H