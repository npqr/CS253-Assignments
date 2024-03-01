#ifndef DBF_H
#define DBF_H

//// Database Functions             //////////////////////////////////////

#include "classes.hpp"
#include "global.hpp"
#include "jsoncpp/json/json-forwards.h"
#include "jsoncpp/json/json.h"
#include "help.hpp"

// Support for JSON from https://github.com/open-source-parsers/jsoncpp

void extractDate(const std::string dateString, int& day, int& month, int& year) {
    size_t firstSlash = dateString.find_first_of('/');
    size_t secondSlash = dateString.find_first_of('/', firstSlash + 1);

    std::string dayStr = dateString.substr(0, firstSlash);
    std::string monthStr = dateString.substr(firstSlash + 1, secondSlash - firstSlash - 1);
    std::string yearStr = dateString.substr(secondSlash + 1);

    day = std::stoi(dayStr);
    month = std::stoi(monthStr);
    year = std::stoi(yearStr);
}

void God::importData() {
    Json::Value root;
    ifstream file("db/data.json");
    file >> root;
    file.close();

    for (auto customer : root["customers"]) {
        Customer* newUser = new Customer(
            (std::string) customer["name"].asString(),
            (std::string) customer["ID"].asString(),
            (std::string) customer["password"].asString());
        
        newUser->rentLimit = customer["rentLimit"].asInt();
        newUser->memberType = customer["memberType"].asString();
        newUser->record = customer["record"].asDouble();
        newUser->due = customer["due"].asDouble();


        for (auto car : customer["rentedCars"]) {
            int d, m, y;
            if ((std::string) car["rentDate"].asString() == "") {
                d = 1;
                m = 1;
                y = 2001;
            }

            extractDate((std::string)car["rentDate"].asString(), d, m, y);
            
            // cout << "DFDSFDSFFDSFDSFSFDSFSFSSF\n";
            // cout << d << " " << m << " " << y << endl;

            // pak2c();

            Car* newCar = new Car(
                (std::string) car["model"].asString(),
                (std::string) car["regNo"].asString(),
                (float) car["condition"].asFloat(),
                (bool) car["isRented"].asBool(),
                (std::string) car["renterID"].asString(),
                Date(1, 1, 2001),
                (float) car["dailyRent"].asFloat(),
                (int) car["expectedDays"].asInt());
            
            newUser->rentedCars.push_back(newCar);
        }

        Customers[newUser->getID()] = newUser;
    }

    for (auto employee : root["employees"]) {
        Employee* newUser = new Employee(
            (std::string) employee["name"].asString(),
            (std::string) employee["ID"].asString(),
            (std::string) employee["password"].asString());
        
        newUser->rentLimit = employee["rentLimit"].asInt();
        newUser->memberType = employee["memberType"].asString();
        newUser->record = employee["record"].asDouble();
        newUser->due = employee["due"].asDouble();


        for (auto car : employee["rentedCars"]) {
            int d, m, y;
            if ((std::string) car["rentDate"].asString() == "") {
                d = 1;
                m = 1;
                y = 2001;
            }

            extractDate((std::string)car["rentDate"].asString(), d, m, y);

            Car* newCar = new Car(
                (std::string) car["model"].asString(),
                (std::string) car["regNo"].asString(),
                (float) car["condition"].asFloat(),
                (bool) car["isRented"].asBool(),
                (std::string) car["renterID"].asString(),
                Date(1, 1, 2001),
                (float) car["dailyRent"].asFloat(),
                (int) car["expectedDays"].asInt());
            
            newUser->rentedCars.push_back(newCar);
        }

        Employees[newUser->getID()] = newUser;
    }

    for (auto car : root["cars"]) {
        int d, m, y;
        if ((std::string) car["rentDate"].asString() == "") {
            d = 1;
            m = 1;
            y = 2001;
        }
        // cout << "DOES THIS WORK??" << endl;

        // cout << "OG String : " << (std::string)car["rentDate"].asString() << endl;

        extractDate((std::string)car["rentDate"].asString(), d, m, y);

        // cout << d << " " << m << " " << y << endl;

        // Sleep(500);

        Car* newCar = new Car(
            (std::string) car["model"].asString(),
            (std::string) car["regNo"].asString(),
            (float) car["condition"].asFloat(),
            (bool) car["isRented"].asBool(),
            (std::string) car["renterID"].asString(),
            Date(d, m, y),
            (float) car["dailyRent"].asFloat(),
            (int) car["expectedDays"].asInt());

        Cars[newCar->getRegNo()] = newCar;
    }
}

void God::exportData() {
    Json::Value root;
    Json::Value customers;
    Json::Value employees;
    Json::Value cars;

    for (auto customer : Customers) {
        Json::Value customerNode;
        customerNode["name"] = customer.se->getName();
        customerNode["ID"] = customer.se->getID();
        customerNode["password"] = customer.se->getPassword();
        customerNode["record"] = customer.se->getRecord();
        customerNode["due"] = customer.se->getDue();
        customerNode["rentLimit"] = customer.se->rentLimit;
        customerNode["memberType"] = customer.se->memberType;

        Json::Value rc;
        customerNode["rentedCars"] = Json::Value(Json::arrayValue);
        for (auto car : customer.se->rentedCars) {
            rc["model"] = car->getModel();
            rc["regNo"] = car->getRegNo();
            rc["condition"] = car->getCondition();
            rc["isRented"] = car->getisRented();
            rc["renterID"] = car->getRenterID();
            rc["rentDate"] = car->getRentDateString();
            rc["dailyRent"] = car->getDailyRent();
            rc["expectedDays"] = car->getExpectedDays();

            customerNode["rentedCars"].append(rc);
        }

        customers.append(customerNode);
    }

    for (auto employee : Employees) {
        Json::Value employeeNode;
        employeeNode["name"] = employee.se->getName();
        employeeNode["ID"] = employee.se->getID();
        employeeNode["password"] = employee.se->getPassword();
        employeeNode["record"] = employee.se->getRecord();
        employeeNode["due"] = employee.se->getDue();
        employeeNode["rentLimit"] = employee.se->rentLimit;
        employeeNode["memberType"] = employee.se->memberType;

        Json::Value rc;
        employeeNode["rentedCars"] = Json::Value(Json::arrayValue);
        for (auto car : employee.se->rentedCars) {
            rc["model"] = car->getModel();
            rc["regNo"] = car->getRegNo();
            rc["condition"] = car->getCondition();
            rc["isRented"] = car->getisRented();
            rc["renterID"] = car->getRenterID();
            rc["rentDate"] = car->getRentDateString();
            rc["dailyRent"] = car->getDailyRent();
            rc["expectedDays"] = car->getExpectedDays();

            // cout << "Exporting: " << rc["model"] << endl;

            employeeNode["rentedCars"].append(rc);
        }

        employees.append(employeeNode);
    }

    for (auto car : Cars) {
        Json::Value carNode;

        carNode["model"] = car.se->getModel();
        carNode["regNo"] = car.se->getRegNo();
        carNode["condition"] = car.se->getCondition();
        carNode["isRented"] = car.se->getisRented();
        carNode["renterID"] = car.se->getRenterID();
        carNode["rentDate"] = car.se->getRentDateString();
        carNode["dailyRent"] = car.se->getDailyRent();
        carNode["expectedDays"] = car.se->getExpectedDays();

        cars.append(carNode);
    }

    root["customers"] = customers;
    root["employees"] = employees;
    root["cars"] = cars;

    ofstream file("db/data.json");

    file << root;
    file.close();
}

#endif  // DBF_H