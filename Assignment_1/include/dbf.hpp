#ifndef DBF_H
#define DBF_H

//// Database Functions             //////////////////////////////////////

#include "classes.hpp"
#include "global.hpp"
#include "jsoncpp/json/json-forwards.h"
#include "jsoncpp/json/json.h"

// Support for JSON from https://github.com/open-source-parsers/jsoncpp

void extractDate(const std::string& dateString, int& day, int& month, int& year) {
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

    for (auto user : root["users"]) {
        User newUser(
            (std::string)user["name"].asString(),
            (std::string)user["ID"].asString(),
            (std::string)user["password"].asString());
        newUser.rentLimit = user["rentLimit"].asInt();
        newUser.memberType = user["memberType"].asString();
        newUser.record = user["record"].asDouble();
        newUser.due = user["due"].asDouble();

        for (auto car : user["rentedCars"]) {
            int d, m, y;
            if (car["rentDate"].asString() == "") {
                d = 1;
                m = 1;
                y = 2001;
            }

            extractDate((std::string)car["rentDate"].asString(), d, m, y);

            Car newCar(
                (std::string)car["model"].asString(),
                (std::string)car["regNo"].asString(),
                (float)car["condition"].asFloat(),
                (bool)car["isRented"].asBool(),
                (std::string)car["renterID"].asString(),
                Date(d, m, y),
                (float)car["dailyRent"].asFloat(),
                (int)car["expectedDays"].asInt());
            newUser.rentedCars.push_back(newCar);
        }

        Users[newUser.getID()] = newUser;
    }

    for (auto car : root["cars"]) {
        int d, m, y;
        if (car["rentDate"].asString() == "") {
            d = 1;
            m = 1;
            y = 2001;
        }

        extractDate((std::string)car["rentDate"].asString(), d, m, y);

        Car newCar(
            (std::string)car["model"].asString(),
            (std::string)car["regNo"].asString(),
            (float)car["condition"].asFloat(),
            (bool)car["isRented"].asBool(),
            (std::string)car["renterID"].asString(),
            Date(d, m, y),
            (float)car["dailyRent"].asFloat(),
            (int)car["expectedDays"].asInt());

        Cars[newCar.getRegNo()] = newCar;
    }
}

void God::exportData() {
    Json::Value root;
    Json::Value users;
    Json::Value cars;

    for (auto user : Users) {
        Json::Value userNode;
        userNode["name"] = user.se.getName();
        userNode["ID"] = user.se.getID();
        userNode["password"] = user.se.getPassword();
        userNode["record"] = user.se.getRecord();
        userNode["due"] = user.se.getDue();
        userNode["rentLimit"] = user.se.rentLimit;
        userNode["memberType"] = user.se.memberType;

        Json::Value rc;
        userNode["rentedCars"] = Json::Value(Json::arrayValue);
        for (auto car : user.se.rentedCars) {
            rc["model"] = car.getModel();
            rc["regNo"] = car.getRegNo();
            rc["condition"] = car.getCondition();
            rc["isRented"] = car.getisRented();
            rc["renterID"] = car.getRenterID();
            rc["rentDate"] = car.getRentDateString();
            rc["dailyRent"] = car.getDailyRent();
            rc["expectedDays"] = car.getExpectedDays();

            userNode["rentedCars"].append(rc);
        }

        users.append(userNode);
    }

    for (auto car : Cars) {
        Json::Value carNode;

        carNode["model"] = car.se.getModel();
        carNode["regNo"] = car.se.getRegNo();
        carNode["condition"] = car.se.getCondition();
        carNode["isRented"] = car.se.getisRented();
        carNode["renterID"] = car.se.getRenterID();
        carNode["rentDate"] = car.se.getRentDateString();
        carNode["dailyRent"] = car.se.getDailyRent();
        carNode["expectedDays"] = car.se.getExpectedDays();

        cars.append(carNode);
    }

    root["users"] = users;
    root["cars"] = cars;

    ofstream file("db/data.json");

    file << root;
    file.close();
}

#endif  // DBF_H