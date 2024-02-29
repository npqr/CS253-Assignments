#ifndef CLASSES_H
#define CLASSES_H

#include "global.hpp"
#include <iomanip>                  // for std::setw

//// Class Declarations             //////////////////////////////////////

class God;
class User;
class Customer;
class Employee;
class Manager;
class Car;
class Date;

//// Date Class                   //////////////////////////////////////

class Date {
protected:
    int day;
    int month;
    int year;

public:
    Date() : day(1), month(1), year(2001) {}

    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    int getDay() const { return day; }
    int getYear() const { return year; }
    int getMonth() const { return month; }

    void addDays(int daysToAdd) {
        // Perform addition of days
        day += daysToAdd;

        // Handle overflow in days
        while (day > daysInMonth()) {
            day -= daysInMonth();
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }

    int daysInMonth() const {
        static const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int daysOfMonth = days[month];
        if (month == 2 && isLeapYear()) {
            daysOfMonth = 29;
        }
        return daysOfMonth;
    }

    bool isLeapYear() const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    std::string getMonthName() const {
        static const std::string monthNames[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        return monthNames[month];
    }

    void display() const {
        cout << day << " " << getMonthName() << " " << year << endl;
    }
};

//// User Class                     //////////////////////////////////////

class User {
protected:
    std::string name = "";    
    std::string ID = "";
    std::string password = "";
    double record = 75.0;
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

//// Customer Class                 //////////////////////////////////////

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

//// Employee Class                 //////////////////////////////////////

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

//// Car Class                      //////////////////////////////////////

class Car {
protected:
    std::string model = "";
    std::string regNo = "";
    float condition = 60.0;
    bool isRented = false;
    std::string renterID = "";
    Date rentDate = Date(1, 1, 2001);
    float dailyRent = 1000.0;
    int expectedDays = 5;

public:
    Car() {};

    Car(std::string model, std::string regNo, float condition, bool isRented, std::string renterID, Date rentDate, float dailyRent, int expectedDays)
        : model(model), regNo(regNo), condition(condition), isRented(isRented), renterID(renterID), rentDate(rentDate), dailyRent(dailyRent), expectedDays(expectedDays) {}

    std::string getModel() const { return model; }
    std::string getRegNo() const { return regNo; }
    float getCondition() const { return condition; }
    bool getisRented() const { return isRented; }
    std::string getRenterID() const { return renterID; }
    Date getRentDate() const {
        return rentDate;
    }
    std::string getDueDate() const { 
        Date rD = Date(rentDate.getDay(), rentDate.getMonth(), rentDate.getYear());
        rD.addDays(expectedDays);

        // cout << rD.getDay() << " " << rD.getMonthName() << ", " << rD.getYear() << endl;

        return std::to_string(rD.getDay()) + " " + rD.getMonthName() + ", " + std::to_string(rD.getYear());
    }

    std::string getRentDateString() const {
        return std::to_string(rentDate.getDay()) + "/" + std::to_string(rentDate.getMonth()) + "/" + std::to_string(rentDate.getYear());
    }

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
    bool findUserbyName(std::string name);
    User& getUserbyName(std::string name);
    bool findCar(std::string regNo);

    void addUser(User &user);
    void updateUser(User &user);
    void removeUser(User &user);

    bool findCarbyModel(std::string model);
    Car& getCarbyModel(std::string model);

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

    std::map<std::string, User> getUsers();
    std::map<std::string, Car> getCars();

    static void importData();
    static void exportData();
    static void sanitizeData();
    
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