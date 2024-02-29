#ifndef CLASSES_H
#define CLASSES_H

#include "global.h"
#include <iomanip>

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
    double due = 0.0;
    std::vector<Car> rentedCars;

public:
    int rentLimit = 5;
    
    void getDues(int today);
    void clearDues() { due = 0.0; }
    void rentCar(Car &car);
    void returnCar(Car &car);
    void setRecord(double newRecord) { record = newRecord; }

    void showMyCars();

    double getRecord() const { return record; }
    double getDue() const { return due; }
    std::vector<Car>& getRentedCars() { return rentedCars; }
    void addFine(double fine) { due += fine; }

    void addRent(Car &car);
    void calculateDue();

    std::string memberType = "";

    User() {};

    User(const std::string& name, std::string ID, const std::string& password)
        : name(name), ID(ID), password(password) {}

    std::string getName() const { return name; }
    std::string getID() const { return ID; }
    std::string getPassword() const { return password; }
    
    void getDetails();
    
    friend Manager;
    friend God;
};

// Also add Help function

//// Customer Class               //////////////////////////////////////

class Customer : public User {    
public:
    Customer(const std::string& name, std::string ID, const std::string& password)
        : User(name, ID, password) {
        memberType = "Customer";
    }

    Customer() {};

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

    Employee () {};

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
    float dailyRent = 0.0;
    int expectedDays = 0;

public:

    Car() {};

    Car(std::string model, std::string regNo, float condition, bool isRented, std::string renterID, std::string dueDate, float dailyRent, int expectedDays)
        : model(model), regNo(regNo), condition(condition), isRented(isRented), renterID(renterID), dueDate(dueDate), dailyRent(dailyRent), expectedDays(expectedDays) {}

    std::string getModel() const { return model; }
    std::string getRegNo() const { return regNo; }
    float getCondition() const { return condition; }
    bool getisRented() const { return isRented; }
    std::string getRenterID() const { return renterID; }
    std::string getdueDate() const { return dueDate; }

    float getDailyRent() const { return dailyRent; }
    int getExpectedDays() const { return expectedDays; }

    void getDetails();
    void rentRequest(User& user);
    void returnRequest(User& user);
    void updateCondition(float newCondition) { condition = newCondition; }

    friend Manager;
};

//// God Class                    //////////////////////////////////////

class God {
protected:
    static std::map<std::string, User> Users;
    static std::map<std::string, Car> Cars;

public:
    bool findUser(std::string ID);
    bool findCar(std::string regNo);

    void addUser(User &user);
    void updateUser(User &user);
    void removeUser(User &user);

    void addCar(Car &car);
    void updateCar(Car &car);
    void removeCar(Car &car);

    void showAllUsers(std::string memberType);
    void showAllCars();
    void showAllCarsSecure();

    bool login(std::string ID, std::string password);
    void logout();

    User& getUser(std::string ID);
    Car& getCar(std::string regNo);

    static void importData();
    static void exportData();
    
};

//// Manager Class                //////////////////////////////////////

class Manager : public User, public God {
protected:
public:
    Manager () {};

    Manager(const std::string& name, std::string ID, const std::string& password)
        : User(name, ID, password), God() {
        memberType = "Manager";
    }
};

#endif // CLASSES_H